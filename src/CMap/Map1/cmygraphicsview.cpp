#include "cmygraphicsview.h"

CMyGraphicsView::CMyGraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{
    this->setMouseTracking(true);

    scene = new QGraphicsScene(this);
    this->setScene(scene);

    QBrush greenBrush (Qt::green);//зеленая заливка
    QBrush blueBrush (Qt::blue);//голубая заливка
    QPen blpen (Qt::black);//черная ручка
    QPen whitepen (Qt::white);//белая ручка
    whitepen.setWidth(1);
    blpen.setWidth(1.5);//задание толщины линии ручки белой и черной соответственно


    QPolygonF polygon,polyg;
    polygon << QPointF(0, 0) << QPointF(100, 0) << QPointF(50, 50) ;
    polyg << QPointF(0,10)<<QPointF(100,10)<< QPointF(50,-50);// создание 2 шаблонов полигонов с именами polygon, polyg


    poly1 = scene->addPolygon (polygon,whitepen,greenBrush);//добавление полигона на сцену
    poly2 = scene-> addPolygon (polyg,blpen,blueBrush);//--||--
    //poly1->setFlag(QGraphicsItem::ItemIsMovable);
    poly1->setToolTip("forest");//всплывающая подсказка, которая выводит надпись forest при наведении курсора на объект poly1

}

void CMyGraphicsView::mouseMoveEvent(QMouseEvent *event){
    QString s_pos = QString::number(event->x()) +
                    " " +
                    QString::number(event->y());

    this->setToolTip(s_pos);// при движении по сцене вне полигона poly1 отображает координаты курсора на сцене
}

