/// \file Демонстрация работы с OpenGIS

#include "stdspm.h"
#include "OpenGISDemo.h"
#include "GLWidget.h"

// Большая полуось	(метры)
#define SEMI_A	(6378245.)
// Малая полуось	(метры)
#define SEMI_B	(6356863.)

#pragma warning(disable: 4100)	// Скрываем предупреждение о неиспользуемых параметрах

Q_EXPORT_PLUGIN(COpenGISDemo)

COpenGISDemo::COpenGISDemo() : ISpmTask(this)
{
	m_pShell		= 0;
	m_pTaskNode		= 0;
	m_pPanel		= 0;
	m_pShellToolBar	= 0;
	m_pTestAction	= 0;
	m_pPGConnection	= 0;
	m_pQueryEditor	= 0;
	m_pQueryRes		= 0;
	m_pTimeLabel	= 0;
	m_pOpenGL		= 0;
	m_dLeft			= 0;
	m_dBottom		= 0;
	m_dWidth		= 0;
	m_dHeight		= 0;
	m_pPoligon		= 0;

	background = QBrush(Qt::lightGray);
	penBorder = QPen(Qt::red);
}

COpenGISDemo::~COpenGISDemo()
{
}

// Инициализация
void COpenGISDemo::Start(const QString& strTaskGUID, const QString& strTaskName, xmlNodePtr pTaskNode, ISpmShell* pShell)
{
	Q_INIT_RESOURCE(resource);

	// Сохраняем уникальный идентификатор задачи и интерфейс оболочки приложения
    m_strTaskGUID		= strTaskGUID;
	m_strTaskName		= strTaskName;
	m_pShell			= pShell;
	m_pTaskNode			= pTaskNode;

	// Здесь реализуются дополнительные действия по инициализации задачи.

	// Создание действий
	if (!CreateActions())
		return;

	// Создание графического интерфейса задачи
	if (!CreatePanel())
		return;

	// Создание системной панели инструментов
	if (!CreateToolBar())
		return;

	if (!CreateDBConnection())
		return;

	QWidget* pCentralWidget = qobject_cast<QWidget*>(m_pShell->GetRsc(SPM_WND_CENTRAL));
	if (0 == pCentralWidget)
	{
		emit OnStartTask(m_strTaskGUID, false);
		return;
	}

	m_pOpenGL = new GLWidget(this, 0);
	QGridLayout* pLayout = new QGridLayout;
	pLayout->setMargin(1);
	pLayout->setColumnStretch(0, 1);
	pLayout->addWidget(m_pOpenGL, 0, 0);

	pCentralWidget->setLayout(pLayout);

	// Сообщаем об удачном запуске задачи
	emit OnStartTask(m_strTaskGUID, true);
}

// Проверка возможности остановки задачи.
bool COpenGISDemo::CanStop()
{
	return true;
}

void COpenGISDemo::paint(QPainter *painter, QPaintEvent *event)
{
	QTime timer;
	timer.start();

	if ((0 == m_dWidth) || (0 == m_dHeight) || (0 == m_pPoligon))
		return;

	double dWidth = double(event->rect().width()) ;
	double dHeight = double(event->rect().height());

	double d = 0;
	if (m_dWidth > m_dHeight)
		d = dWidth / m_dWidth;
	else
		d = dHeight / m_dHeight;
	
	QRect region(0, 0, m_dWidth * d, m_dHeight * d);
	painter->fillRect(region, background);

	painter->setPen(penBorder);
	int nSize = PQntuples(m_pPoligon);
	if (nSize > 0)
	{
		BYTE *pData = (BYTE*)PQgetvalue(m_pPoligon, 0, 0);
		pData += 9;

		DWORD dwNumPoints = *(DWORD*)(pData);
		pData += 4;

		double px = 0;
		double py = 0;
		for (DWORD j = 0; j < dwNumPoints; j++)
		{
			double cx = (*(double*)pData - m_dLeft) * d;
			pData += 8;

			double cy = (m_dBottom - *(double*)pData) * d;
			pData += 8;

			if (j > 0)
				painter->drawLine(px, py, cx, cy);

			px = cx;
			py = cy;
		}
	}	

	m_pTimeLabel->setText(tr("Время перерисовки: %1").arg(timer.elapsed()));
}

// Запуск процесса остановки. Возвращает true, если остановка возможна
void COpenGISDemo::Stop()
{
	// Освобождаем ресуры
	Q_CLEANUP_RESOURCE(resource);

	if (m_pPoligon)
	{
		PQclear(m_pPoligon);
		m_pPoligon = 0;
	}

	// Уничтожаем окно
	m_pShell->RemoveRsc("OpenGISDemo_WND");

	// Уничтожаем системную панель инструментов
	m_pShell->RemoveRsc("OpenGISDemo_TOOLBAR");

	// Сообщаем всем заинтересованным сторонам о завершении процесса остановки
	emit OnStopTask(m_strTaskGUID);
}

// Создание панели задачи
bool COpenGISDemo::CreatePanel()
{
	m_pPanel = m_pShell->CreatePanel("OpenGISDemo_WND", m_strTaskName);
	if (0 == m_pPanel)
	{
		// Сообщаем о неудачном запуске задачи
		emit OnStartTask(m_strTaskGUID, false);
		return false;
	}

	QWidget* pMainWidget = new QWidget(m_pPanel);
	m_pPanel->setWidget(pMainWidget);

	QGridLayout* pMainLayout = new QGridLayout(m_pPanel);
	pMainWidget->setLayout(pMainLayout);
	pMainLayout->setMargin(1);

	// Добавление элементов на форму
	m_pQueryRes = new QTextEdit;
	m_pQueryRes->setReadOnly(true);

	m_pQueryEditor = new QLineEdit();
	m_pQueryEditor->setFocus(Qt::ActiveWindowFocusReason);
	m_pQueryEditor->setText("1");

	QLabel* pLabel = new QLabel(tr("Полигон:"));
	pLabel->setBuddy(m_pQueryEditor);

	QPushButton* pButton = new QPushButton(tr("Выполнить"));
	pButton->setGeometry(QRect(235, 40, 75, 25));
	connect(pButton, SIGNAL(clicked()), this, SLOT(OnExecuteQuery()));

	QHBoxLayout *pQueryLayout = new QHBoxLayout;
	pQueryLayout->addWidget(pLabel);
	pQueryLayout->addWidget(m_pQueryEditor, 1);
	pQueryLayout->addWidget(pButton);

	m_pTimeLabel = new QLabel(tr("Время перерисовки:"));

	pMainLayout->addWidget(m_pTimeLabel, 0, 0);
	pMainLayout->addLayout(pQueryLayout, 1, 0);
	pMainLayout->addWidget(m_pQueryRes, 2, 0);

	return true;
}

// Создание системной панели инструментов
bool COpenGISDemo::CreateToolBar()
{
	m_pShellToolBar = m_pShell->CreateToolBar("OpenGISDemo_TOOLBAR", m_strTaskName);
	if (0 == m_pShellToolBar)
	{
		// Сообщаем о неудачном запуске задачи
		emit OnStartTask(m_strTaskGUID, false);
		return false;
	}

	// Добавление действий на системную панель инструментов
	m_pShellToolBar->addAction(m_pTestAction);

	return true;
}

bool COpenGISDemo::CreateDBConnection()
{
	CSpmXml xml(m_pTaskNode);
	QString strConnectionString = "dbname=postgis";
	if (xml.MoveFirst("/param[@name='connection']"))
	{
		QVariant vtTemp = xml.GetAttr("value");
		if (vtTemp.isValid())
			strConnectionString = vtTemp.toString();
	}

	m_pPGConnection = PQconnectdb(strConnectionString.toAscii().data());
	if (PQstatus(m_pPGConnection) == CONNECTION_BAD)     
	{ 
		QMessageBox::critical(0, tr("Ошибка"), tr(PQerrorMessage(m_pPGConnection)), QMessageBox::Ok);

		// Сообщаем о неудачном запуске задачи
		emit OnStartTask(m_strTaskGUID, false);
		return false;
	} 

	return true;
}

void COpenGISDemo::OnExecuteQuery()
{
	QApplication::setOverrideCursor(Qt::WaitCursor);

	QTextCharFormat textFormat;
	QTextCharFormat boldFormat;
	boldFormat.setFontWeight(QFont::Bold);
	boldFormat.setForeground(QBrush(Qt::red));

	m_pQueryRes->clear();
	QTextCursor cursor(m_pQueryRes->textCursor());
	cursor.movePosition(QTextCursor::Start);

	cursor.insertText(tr("Запрос геометрии: "), boldFormat);

	QString strQuery = tr("SELECT geom FROM opengis WHERE idgeom=%1").arg(m_pQueryEditor->text());
	cursor.insertText(strQuery, textFormat);
	cursor.insertBlock();

	QTime timer;
	timer.start();

	m_pPoligon = PQexecParams(m_pPGConnection, strQuery.toAscii().data(), 0, 0, 0, 0, 0, 1);

	ExecStatusType status = PQresultStatus(m_pPoligon);
	if((PGRES_COMMAND_OK == status) || (PGRES_TUPLES_OK == status))
	{		
		int nSize = PQntuples(m_pPoligon);
		if (nSize > 0)
		{
			DWORD nTotal = 0;
			BYTE *pData = (BYTE*)PQgetvalue(m_pPoligon, 0, 0);

			cursor.insertText(tr("Byte order: "), boldFormat);
			cursor.insertText(tr("%1").arg(*pData), textFormat);
			cursor.insertBlock();
			pData += 1;

			DWORD* pdwWKBType = (DWORD*)(pData);
			cursor.insertText(tr("WKB type: "), boldFormat);
			cursor.insertText(tr("%1").arg(*pdwWKBType), textFormat);
			cursor.insertBlock();
			pData += 4;

			DWORD dwSegmentCount = *(DWORD*)(pData);
			cursor.insertText(tr("Количество кусков: "), boldFormat);
			cursor.insertText(tr("%1").arg(dwSegmentCount), textFormat);
			cursor.insertBlock();
			pData += 4;

			for (DWORD i = 0; i < dwSegmentCount; i++)
			{
				DWORD dwNumPoints = *(DWORD*)(pData);
				cursor.insertText(tr("Количество точек: "), boldFormat);
				cursor.insertText(tr("%1").arg(dwNumPoints), textFormat);
				cursor.insertBlock();
				pData += 4;

				nTotal += dwNumPoints;

				pData += 16 * dwNumPoints;
			}

			cursor.insertText(tr("Общее количество точек: "), boldFormat);
			cursor.insertText(tr("%1").arg(nTotal), textFormat);
			cursor.insertBlock();
		}				
	}

	cursor.insertText(tr("Время выполнения: "), boldFormat);
	cursor.insertText(tr("%1").arg(timer.elapsed()), textFormat);
	cursor.insertBlock();
	cursor.insertBlock();

	cursor.insertText(tr("Запрос охватывающего прямоугольника: "), boldFormat);

	strQuery = tr("SELECT Envelope(geom) FROM opengis WHERE idgeom=%1").arg(m_pQueryEditor->text());
	cursor.insertText(strQuery, textFormat);
	cursor.insertBlock();

	QTime timer2;
	timer2.start();

	PGresult* pRes = PQexecParams(m_pPGConnection, strQuery.toAscii().data(), 0, 0, 0, 0, 0, 1);

	status = PQresultStatus(pRes);
	if((PGRES_COMMAND_OK == status) || (PGRES_TUPLES_OK == status))
	{		
		int nSize = PQntuples(pRes);
		if (nSize > 0)
		{
			BYTE *pData = (BYTE*)PQgetvalue(pRes, 0, 0);

			cursor.insertText(tr("Byte order: "), boldFormat);
			cursor.insertText(tr("%1").arg(*pData), textFormat);
			cursor.insertBlock();

			pData += 1;
			DWORD* pdwWKBType = (DWORD*)(pData);
			cursor.insertText(tr("WKB type: "), boldFormat);
			cursor.insertText(tr("%1").arg(*pdwWKBType), textFormat);
			cursor.insertBlock();

			pData += 8;

			DWORD dwNumPoints = *(DWORD*)(pData);
			cursor.insertText(tr("Количество точек: "), boldFormat);
			cursor.insertText(tr("%1").arg(dwNumPoints), textFormat);
			cursor.insertBlock();

			pData += 4;

			double dLeft = DBL_MAX;
			double dRight = DBL_MIN;
			double dTop = DBL_MAX;
			double dBottom = DBL_MIN;

			for (DWORD j = 0; j < dwNumPoints; j++)
			{
				double dx = *(double*)pData;
				pData += 8;

				if (dx > dRight)
					dRight = dx;

				if (dx < dLeft)
					dLeft = dx;

				double dy = *(double*)pData;
				pData += 8;

				if (dy > dBottom)
					dBottom = dy;

				if (dy < dTop)
					dTop = dy;
			}

			m_dLeft = dLeft;
			m_dBottom = dBottom;
			m_dWidth = dRight - dLeft;
			m_dHeight = dBottom - dTop;

			cursor.insertText(tr("Ширина: "), boldFormat);
			cursor.insertText(tr("%1").arg(m_dWidth, 0, 'f', 3), textFormat);
			cursor.insertBlock();

			cursor.insertText(tr("Высота: "), boldFormat);
			cursor.insertText(tr("%1").arg(m_dHeight, 0, 'f', 3), textFormat);
			cursor.insertBlock();

			cursor.insertBlock();
		}				
	}

	PQclear(pRes);
	pRes = 0;

	cursor.insertText(tr("Время выполнения: "), boldFormat);
	cursor.insertText(tr("%1").arg(timer2.elapsed()), textFormat);
	cursor.insertBlock();
	cursor.insertBlock();

	cursor.insertText(tr("Общее время выполнения: "), boldFormat);
	cursor.insertText(tr("%1").arg(timer.elapsed()), textFormat);

	m_pOpenGL->repaint();

	QApplication::restoreOverrideCursor();
}

bool COpenGISDemo::CreateActions()
{
	// Создание события
	m_pTestAction = new QAction(QIcon(":/open.png"), tr("Импорт"), this);
	if (0 == m_pTestAction)
	{
		// Сообщаем о неудачном запуске задачи
		emit OnStartTask(m_strTaskGUID, false);
		return false;
	}

	m_pTestAction->setStatusTip(tr("Импорт государственной границы"));

	// Подключение сигнала активации события на обработчик
	connect(m_pTestAction, SIGNAL(triggered()), this, SLOT(OnImport()));
	return true;
}

void COpenGISDemo::OnImport()
{
	QString strFileName = QFileDialog::getOpenFileName(0, tr("Открытие файла"), m_pShell->BuildAbsolutePath("../options/Border.dat"), tr("Списки координат (*.dat)"));
	if (strFileName.isEmpty())
		return;

	QFile input(strFileName);
	if(!input.open(QFile::ReadOnly))
		return;

	QTextStream	si(&input);

	QString strSQLFileName = strFileName + ".sql";
	QFile output(strSQLFileName);
	if(!output.open(QFile::WriteOnly))
		return;

	QTextStream	so(&output);

	QApplication::setOverrideCursor(Qt::WaitCursor);
	so << "insert into opengis values (3, geomfromewkt('POLYGON (";

	bool bStart = true;
	
	while(!si.atEnd())
	{
		QStringList polygon = si.readLine().split(" ", QString::SkipEmptyParts);
		if (polygon.size() != 3)
			break;

		if (bStart)
			bStart = false;
		else
			so << ",";

		so << "(";

		int count = polygon[2].toInt();
		for (int i = 0; (!si.atEnd()) && (i < count); i++)
		{
			if (i > 0)
			{
				so << ", ";
			}

			QStringList points = si.readLine().split(" ", QString::SkipEmptyParts);
			double dFi = points[0].toDouble();
			double dY = dFi * SEMI_A;

			double dLambda = points[1].toDouble();
			double dX = dLambda * SEMI_B;

			so << tr("%1 %2").arg(dX, 0, 'f', 3).arg(dY, 0, 'f', 3);
		}

		so << ")";
	}
	input.close();

	so << ")'))";
	output.close();

	QApplication::restoreOverrideCursor();
}
