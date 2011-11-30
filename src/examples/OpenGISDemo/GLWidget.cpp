#include "GLWidget.h"
    
#pragma warning(disable: 4100) // Скрываем предупреждение о неиспользуемых параметрах

GLWidget::GLWidget(COpenGISDemo *helper, QWidget *parent)
//:  QGLWidget(QGLFormat(QGL::SampleBuffers), parent), helper(helper)
:  QWidget(parent), helper(helper)
{
}

void GLWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter;
	painter.begin(this);
	//painter.setRenderHint(QPainter::Antialiasing);
	helper->paint(&painter, event);
	painter.end();
}

void GLWidget::resizeEvent(QResizeEvent *event)
{
	repaint();
}