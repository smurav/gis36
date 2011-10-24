#ifndef CMYGRAPHICSVIEW_H
#define CMYGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QtGui>

class CMyGraphicsView : public QGraphicsView
{
    Q_OBJECT

private:
    QGraphicsScene *scene;
    QGraphicsPolygonItem *poly1;
    QGraphicsPolygonItem *poly2;

public:
    explicit CMyGraphicsView(QWidget *parent = 0);

protected:
    virtual void mouseMoveEvent(QMouseEvent *event);

signals:

public slots:

};

#endif // CMYGRAPHICSVIEW_H
