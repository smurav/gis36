/// \file Класс для отрисовки через OpenGL

#ifndef _SYSTEMPROM_GLWIDGET_H
#define _SYSTEMPROM_GLWIDGET_H

#include "stdspm.h"
#include "OpenGISDemo.h"

//class GLWidget : public  QGLWidget
class GLWidget : public  QWidget
{
    Q_OBJECT

public:
	GLWidget(COpenGISDemo *helper, QWidget *parent);

protected:
	void paintEvent(QPaintEvent *event);
	void resizeEvent(QResizeEvent *event);

private:
	COpenGISDemo* helper;
};

#endif
    
