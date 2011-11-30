/// \file Демонстрация работы с OpenGIS

#ifndef _SYSTEMPROM_OpenGISDemo_H
#define _SYSTEMPROM_OpenGISDemo_H

#include "stdspm.h"

class GLWidget;

class COpenGISDemo : public QObject, public ISpmTask
{
	Q_OBJECT
	Q_INTERFACES(ISpmTask)
public:
	COpenGISDemo();
	virtual	~COpenGISDemo();

// ISpmTask

public:
	/// Инициализация задачи
	void Start(
						const QString& strTaskGUID,		///< Уникальный идентификатор задачи.
						const QString& strTaskName,		///< Наименование задачи.
						xmlNodePtr pTaskNode,			///< Указатель на узел задачи в конфигурационном файле.
						ISpmShell* pShell				///< Указатель на интерфейс ISpmShell оболочки приложения.
				);

	/// Проверка возможности остановки задачи.
	bool CanStop();

	/// Запуск процесса остановки. Возвращает true, если остановка возможна
    void Stop();

	void paint(QPainter *painter, QPaintEvent *event);
signals:
	/// Сигнал о завершении процесса запуска.
	void OnStartTask(
						const QString& strTaskGUID,		///< Уникальный идентификатор задачи.
						bool bSucceeded					///< Признак успешности запуска задачи.
					);

	/// Сигнал о завершении процесса остановки.
	void OnStopTask(
						const QString& strTaskGUID		///< Уникальный идентификатор задачи.
					);

	/// Сигнал изменения состояния
	void OnChangeState(); 

private:

	/// Функция создания панели задачи
	/// \return Возвращает признак успешного создания интерфейса задачи
	bool CreatePanel();

	/// Функция создания системной панели инструментов
	/// \return Возвращает признак успешного создания системной панели инструментов
	bool CreateToolBar();

	/// Функция создания действий
	/// \return Возвращает признак успешного создания действий
	bool CreateActions();

	bool CreateDBConnection();

private slots:
	void OnImport();
	void OnExecuteQuery();

private:
	QString			m_strTaskGUID;						///< Уникальный идентификатор задачи.
	QString			m_strTaskName;						///< Название задачи.
	ISpmShell*		m_pShell;							///< Указатель на интерфейс оболочки приложения.
	xmlNodePtr		m_pTaskNode;						///< Указатель на XML узел задачи.
	QAction*		m_pTestAction;						///< Тестовое событие.
	QDockWidget*	m_pPanel;							///< Указатель на окно задачи.
	QToolBar*		m_pShellToolBar;					///< Указатель на системную панель инструментов.
	PGconn*			m_pPGConnection;
	QTextEdit*		m_pQueryRes;	// результат выполнения запроса
	QLineEdit*		m_pQueryEditor; // Запрос
	QLabel*			m_pTimeLabel;	// Время выполнения запроса
	GLWidget*		m_pOpenGL;

private:
	QBrush background;
	QPen   penBorder;

	PGresult*	m_pPoligon;

	double	m_dLeft;
	double	m_dBottom;
	double	m_dWidth;
	double  m_dHeight;
};

#endif