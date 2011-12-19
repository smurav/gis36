#include <QtCore/QDebug>
#include <QtCore/QXmlStreamReader>
#include <QtCore/QString>
#include <QtCore/QFile>
#include <QtGui>
#include <QtXmlPatterns/QXmlQuery>
#include <QXmlStreamAttributes>
#include <QDomAttr>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QTableView>
#include <qlayout.h>

#include "ConverterLibrary.h"

ConverterLibrary::ConverterLibrary() {

}

QString ConverterLibrary::ConverterParser(const QString &file){

    QXmlQuery xml_query;
    QString file_path(file);
    QFile input_file(file_path);

    QString node_id_st,
            way_id_st,
            relation_id_st,
            node_name,
            node_lat,
            node_lon,
            way_name_st,
            way_node_id_st,
            way_lat,
            way_lon,
            relation_name,
            relation_node_st,
            relation_way_st,
            poly,
            rezalt;

    QStringList node_id,
                way_id,
                relation_id,
                way_node_id,
                relation_way,
                relation_node;

//    QWidget* pWidget = new QWidget;
//    QGraphicsScene* pScene = new QGraphicsScene (QRectF (0,0,800,600));
//    graphicsView = new QGraphicsView(pScene, pWidget);
//    QVBoxLayout* pLayout = new QVBoxLayout;
//    pLayout->addWidget(graphicsView);

    bool is_open = input_file.open(QIODevice::ReadOnly | QIODevice::Text);
    xml_query.setFocus(&input_file);

    if (is_open){
        QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
        db.setHostName("127.0.0.1");
        db.setDatabaseName("GIS");
        db.setPort(5432);
        db.setUserName("postgres");
        db.setPassword("1234");

        bool is_connected = db.open();

        if (is_connected){

            QSqlQuery sql_query;
            int obj_id = 1, tag_id = 1;

            sql_query.exec("SELECT id_obj FROM objects");
            while (sql_query.next()){
                obj_id = sql_query.value(0).toInt();
            }

            sql_query.exec("SELECT id_tag FROM tags");
            while (sql_query.next()){
                tag_id = sql_query.value(0).toInt();
            }

            xml_query.setQuery("osm/node[*/@k='name']/@id/string()");
            xml_query.evaluateTo(&node_id_st);
            node_id_st.remove(QChar('\n'), Qt::CaseInsensitive);
            node_id = node_id_st.split(QRegExp("\\s+")); //получили массив id всех точек

            //xml_query.setQuery("osm/node/tag[@k='name']/@id/string()");

            //вынимаем широту и долготу в базу для объектов типа ТОЧКА
            for (int i=0; i<node_id.count(); i++){
                xml_query.setQuery("/osm/node[@id='"+node_id[i]+"']/@lat/string()"); //широта точки
                xml_query.evaluateTo(&node_lat);
                node_lat.remove(QChar('\n'), Qt::CaseInsensitive);

                xml_query.setQuery("/osm/node[@id='"+node_id[i]+"']/@lon/string()"); //долгота точки
                xml_query.evaluateTo(&node_lon);
                node_lon.remove(QChar('\n'), Qt::CaseInsensitive);

                xml_query.setQuery("/osm/node[@id='"+ node_id[i] + "']/tag[@k='name']/@v/string()"); //название точки
                xml_query.evaluateTo(&node_name);
                node_name.remove(QChar('\n'), Qt::CaseInsensitive);

                if (node_name != ""){
                    rezalt += node_name + "\n" + "lat = " + node_lat + " lon = " + node_lon + "\n";
                    sql_query.prepare("INSERT INTO tags (id_tag, key_tag, value_tag, id_obj)"
                                      "VALUES(:id, '---', :val, :obj);");
                    sql_query.bindValue(":id", tag_id++);
                    sql_query.bindValue(":val", node_name);
                    sql_query.bindValue(":obj", obj_id);
                    sql_query.exec();
                }
                node_name = "";

                QString for_db = "POINT(" + node_lat + " " + node_lon + ")";
                sql_query.prepare("INSERT INTO objects (id_obj, geometry_obj)"
                                  "VALUES (:id, :geo);");
                sql_query.bindValue(":id", obj_id++);
                sql_query.bindValue(":geo", for_db);
                sql_query.exec();
            }

            xml_query.setQuery("osm/way[*/@k='name']/@id/string()");
            xml_query.evaluateTo(&way_id_st);
            way_id_st.remove(QChar('\n'), Qt::CaseInsensitive);
            way_id = way_id_st.split(QRegExp("\\s+")); //получили массив id всех линий

            //формируем объект типа ЛИНИЯ для бд
            for (int i=0; i<way_id.count(); i++){
                xml_query.setQuery("osm/way[@id='"+way_id[i]+"']/tag[@k='name']/@v/string()");
                xml_query.evaluateTo(&way_name_st);
                way_name_st.remove(QChar('\n'), Qt::CaseInsensitive);

                xml_query.setQuery("osm/way[*/@v='"+way_name_st+"']/nd[@ref]/@ref/string()");
                xml_query.evaluateTo(&way_node_id_st);
                way_node_id_st.remove(QChar('\n'), Qt::CaseInsensitive);
                way_node_id = way_node_id_st.split(QRegExp("\\s+"));

                rezalt += way_name_st + "\n";
                QString for_db_coord = "";

                //QPolygonF polygon;

                for (int j=0; j<way_node_id.count(); j++){
                    xml_query.setQuery("osm/node[@id='"+way_node_id[j]+"']/@lat/string()");
                    xml_query.evaluateTo(&way_lat);
                    way_lat.remove(QChar('\n'), Qt::CaseInsensitive);

                    xml_query.setQuery("osm/node[@id='"+way_node_id[j]+"']/@lon/string()");
                    xml_query.evaluateTo(&way_lon);
                    way_lon.remove(QChar('\n'), Qt::CaseInsensitive);

                    rezalt += "lat = " + way_lat + " lon = " + way_lon + "\n";
                    for_db_coord += way_lat + " " + way_lon + ",";
                }

                QString for_db = "LINESTRING(" + for_db_coord.left(for_db_coord.length()-1) + ")";

                sql_query.prepare("INSERT INTO objects (id_obj, geometry_obj)"
                                  "VALUES (:id, :geo);");
                sql_query.bindValue(":id", obj_id);
                sql_query.bindValue(":geo", for_db);
                sql_query.exec();

                sql_query.prepare("INSERT INTO tags (id_tag, key_tag, value_tag, id_obj)"
                                    "VALUES(:id, '---', :val, :obj);");
                sql_query.bindValue(":id", tag_id++);
                sql_query.bindValue(":val", way_name_st);
                sql_query.bindValue(":obj", obj_id++);
                sql_query.exec();
            }

            xml_query.setQuery("osm/relation[*/@k='name']/@id/string()");
            xml_query.evaluateTo(&relation_id_st);
            relation_id_st.remove(QChar('\n'), Qt::CaseInsensitive);
            relation_id = relation_id_st.split(QRegExp("\\s+")); //получили массив id всех отношений c атрибутом 'name'

//            for (int i=0; i<relation_id.count(); i++){
//                xml_query.setQuery("osm/relation[@id='"+relation_id[i]+"']/tag[@k='name']/@v/string()");
//                xml_query.evaluateTo(&relation_name);
//                relation_name.remove(QChar('\n'), Qt::CaseInsensitive);

//                //вытащили id точек из отношения
//                xml_query.setQuery("osm/(relation[(*/@v='"+relation_name+"')&&(*/@type='node')]/member[@ref]/@ref/string()");
//                xml_query.evaluateTo(&relation_node_st);
//                relation_node_st.remove(QChar('\n'), Qt::CaseInsensitive);
//                relation_node = relation_node_st.split(QRegExp("\\s+")); //получили массив id всех точек, входящих в отношение

//                for (int j=0; j<relation_node.count(); j++){
//                    xml_query.setQuery("osm/node[@id='"+relation_node[j]+"']/@lat/string()");
//                    xml_query.evaluateTo(&node_lat);
//                    node_lat.remove(QChar('\n'), Qt::CaseInsensitive);

//                    xml_query.setQuery("osm/node[@id='"+relation_node[j]+"']/@lon/string()");
//                    xml_query.evaluateTo(&node_lon);
//                    node_lon.remove(QChar('\n'), Qt::CaseInsensitive);

//                    poly = node_lat + " " + node_lon + ", ";
//                }
//                //вытащили id линий, входящих в отношение
//                xml_query.setQuery("osm/(relation[*/@v='"+relation_name+"']) && (relation/[@type=way])/member[@ref]/@ref/string()");
//                xml_query.evaluateTo(&relation_way_st);
//                relation_way_st.remove(QChar('\n'), Qt::CaseInsensitive);
//                relation_way = relation_way_st.split(QRegExp("\\s+")); //получили массив id всех линий, входящих в отношение

//                for (int j=0; j<relation_way.count(); j++){
//                    xml_query.setQuery("osm/way[@id='"+relation_way[i]+"']/tag[@k='name']/@v/string()");
//                    xml_query.evaluateTo(&way_name_st);
//                    way_name_st.remove(QChar('\n'), Qt::CaseInsensitive);

//                    xml_query.setQuery("osm/way[*/@v='"+way_name_st+"']/nd[@ref]/@ref/string()");
//                    xml_query.evaluateTo(&way_node_id_st);
//                    way_node_id_st.remove(QChar('\n'), Qt::CaseInsensitive);
//                    way_node_id = way_node_id_st.split(QRegExp("\\s+"));

//                    rezalt += way_name_st + "\n";

//                    for (int j=0; j<way_node_id.count(); j++){
//                        xml_query.setQuery("osm/node[@id='"+way_node_id[j]+"']/@lat/string()");
//                        xml_query.evaluateTo(&way_lat);
//                        way_lat.remove(QChar('\n'), Qt::CaseInsensitive);

//                        xml_query.setQuery("osm/node[@id='"+way_node_id[j]+"']/@lon/string()");
//                        xml_query.evaluateTo(&way_lon);
//                        way_lon.remove(QChar('\n'), Qt::CaseInsensitive);

//                        poly += way_lat + " " + way_lon + ",";
//                    }
//                }

//                QString for_db = "POLYGONE(" + poly.left(poly.length()-1) + ")";

//                sql_query.prepare("INSERT INTO objects (id_obj, geometry_obj)"
//                                  "VALUES (:id, :geo);");
//                sql_query.bindValue(":id", obj_id);
//                sql_query.bindValue(":geo", for_db);
//                sql_query.exec();

//                sql_query.prepare("INSERT INTO tags (id_tag, key_tag, value_tag, id_obj)"
//                                    "VALUES(:id, '---', :val, :obj);");
//                sql_query.bindValue(":id", tag_id++);
//                sql_query.bindValue(":val", relation_name);
//                sql_query.bindValue(":obj", obj_id++);
//                sql_query.exec();

//            }

        }else{
            rezalt = tr("Соединение с базой данных не установлено.");
        }

        db.close();

        //отрисовка
        //н: границы листа
//        xml_query.setQuery("osm/bounds/@minlat/string()");
//        xml_query.evaluateTo(&minlat_query);
//        minlat_query.remove(QChar('\n'), Qt::CaseInsensitive);

//        xml_query.setQuery("osm/bounds/@minlon/string()");
//        xml_query.evaluateTo(&minlon_query);
//        minlon_query.remove(QChar('\n'), Qt::CaseInsensitive);

//        xml_query.setQuery("osm/bounds/@maxlat/string()");
//        xml_query.evaluateTo(&maxlat_query);
//        maxlat_query.remove(QChar('\n'), Qt::CaseInsensitive);

//        xml_query.setQuery("osm/bounds/@maxlon/string()");
//        xml_query.evaluateTo(&maxlon_query);
//        maxlon_query.remove(QChar('\n'), Qt::CaseInsensitive);

//        float minlat = minlat_query.toFloat();
//        float minlon = minlon_query.toFloat();
//        float maxlat = maxlat_query.toFloat();
//        float maxlon = maxlon_query.toFloat();

//        graphicsView->resetTransform();
//        graphicsView->centerOn((maxlon + minlon)/2, (maxlat + minlat)/2);
//        graphicsView->setResizeAnchor(QGraphicsView::AnchorViewCenter);

//        qreal sx = 80000;
//        qreal sy = 100000;

//        graphicsView->scale(sx, -sy);
//        //к: границы листа

//        way_node_id_st = "";way_lat = "";way_lon = "";way_id_st = "";
//        QStringList way_paint, node_paint;

//        xml_query.setQuery("osm/way/@id/string()");
//        xml_query.evaluateTo(&way_id_st);
//        way_id_st.remove(QChar('\n'), Qt::CaseInsensitive);
//        way_paint = way_id_st.split(QRegExp("\\s+")); //получили массив id всех линий

//        QPen pen(Qt::darkGray);
//        QBrush brush(Qt::lightGray);
//        QList<QGraphicsItem*> layer;

//        for (int i=0; i<way_paint.count(); i++){

//            QPolygonF polygon;

//            xml_query.setQuery("osm/way[@id='"+way_paint[i]+"']/nd[@ref]/@ref/string()"); //id точек из одной линий
//            xml_query.evaluateTo(&way_node_id_st);
//            way_node_id_st.remove(QChar('\n'), Qt::CaseInsensitive);
//            node_paint= way_node_id_st.split(QRegExp("\\s+"));

//            for (int j=0; j<node_paint.count(); j++){
//                xml_query.setQuery("osm/node[@id='"+node_paint[j]+"']/@lat/string()"); //широта
//                xml_query.evaluateTo(&way_lat);
//                way_lat.remove(QChar('\n'), Qt::CaseInsensitive);

//                xml_query.setQuery("osm/node[@id='"+node_paint[j]+"']/@lon/string()"); //долгота
//                xml_query.evaluateTo(&way_lon);
//                way_lon.remove(QChar('\n'), Qt::CaseInsensitive);

//                polygon.append(QPointF(way_lon.toFloat(), way_lat.toFloat()));
//            }

//            QGraphicsPolygonItem *polygon_item = new QGraphicsPolygonItem(polygon);
//            polygon_item->setPen(pen);
//            polygon_item->setBrush(brush);

//            pScene->addItem(polygon_item);
//        }
    }else{
        rezalt = tr("Файл не найден. Введите другое имя файла!");
    }

//    graphicsView->show();
//    pWidget->setLayout(pLayout);
//    pWidget->show();

    input_file.close();

    return rezalt;
}

void ConverterLibrary::ConverterPainter(const QString &file){
    QXmlQuery xml_query;
    QString file_path(file);
    QFile input_file(file_path);

    QWidget* pWidget = new QWidget;
    QGraphicsScene* pScene = new QGraphicsScene (QRectF (0,0,800,600));
    QGraphicsView *graphics = new QGraphicsView(pScene, pWidget);

    QVBoxLayout* pLayout = new QVBoxLayout;
    pLayout->addWidget(graphics);

    bool is_open = input_file.open(QIODevice::ReadOnly | QIODevice::Text);
    xml_query.setFocus(&input_file);

    if (is_open){

        QString maxlon_query,
                maxlat_query,
                minlon_query,
                minlat_query;
        //отрисовка
        //н: границы листа
        xml_query.setQuery("osm/bounds/@minlat/string()");
        xml_query.evaluateTo(&minlat_query);
        minlat_query.remove(QChar('\n'), Qt::CaseInsensitive);

        xml_query.setQuery("osm/bounds/@minlon/string()");
        xml_query.evaluateTo(&minlon_query);
        minlon_query.remove(QChar('\n'), Qt::CaseInsensitive);

        xml_query.setQuery("osm/bounds/@maxlat/string()");
        xml_query.evaluateTo(&maxlat_query);
        maxlat_query.remove(QChar('\n'), Qt::CaseInsensitive);

        xml_query.setQuery("osm/bounds/@maxlon/string()");
        xml_query.evaluateTo(&maxlon_query);
        maxlon_query.remove(QChar('\n'), Qt::CaseInsensitive);

        float minlat = minlat_query.toFloat();
        float minlon = minlon_query.toFloat();
        float maxlat = maxlat_query.toFloat();
        float maxlon = maxlon_query.toFloat();

        graphics->resetTransform();
        graphics->centerOn((maxlon + minlon)/2, (maxlat + minlat)/2);
        graphics->setResizeAnchor(QGraphicsView::AnchorViewCenter);

        qreal sx = 80000;
        qreal sy = 100000;

        graphics->scale(sx, -sy);
        //к: границы листа

        QString way_node_id_st, way_lat, way_lon, way_id_st;
        QStringList way_paint, node_paint;

        xml_query.setQuery("osm/way/@id/string()");
        xml_query.evaluateTo(&way_id_st);
        way_id_st.remove(QChar('\n'), Qt::CaseInsensitive);
        way_paint = way_id_st.split(QRegExp("\\s+")); //получили массив id всех линий

        QPen pen(Qt::darkGray);
        QBrush brush(Qt::lightGray);

        for (int i=0; i<way_paint.count(); i++){

            QPolygonF polygon;

            xml_query.setQuery("osm/way[@id='"+way_paint[i]+"']/nd[@ref]/@ref/string()"); //id точек из одной линий
            xml_query.evaluateTo(&way_node_id_st);
            way_node_id_st.remove(QChar('\n'), Qt::CaseInsensitive);
            node_paint= way_node_id_st.split(QRegExp("\\s+"));

            for (int j=0; j<node_paint.count(); j++){
                xml_query.setQuery("osm/node[@id='"+node_paint[j]+"']/@lat/string()"); //широта
                xml_query.evaluateTo(&way_lat);
                way_lat.remove(QChar('\n'), Qt::CaseInsensitive);

                xml_query.setQuery("osm/node[@id='"+node_paint[j]+"']/@lon/string()"); //долгота
                xml_query.evaluateTo(&way_lon);
                way_lon.remove(QChar('\n'), Qt::CaseInsensitive);

               // polygon.append(QPointF());
                polygon.append(QPointF(way_lon.toFloat(), way_lat.toFloat()));

            }

            QGraphicsPolygonItem *polygon_item = new QGraphicsPolygonItem(polygon);
            polygon_item->setPen(pen);
            polygon_item->setBrush(brush);

            pScene->addItem(polygon_item);
        }
    }else{
         pScene->addText(tr("Файл не найден. Введите другое имя файла!"));
    }

    graphics->show();
    pWidget->setLayout(pLayout);
    pWidget->show();

    input_file.close();
}


