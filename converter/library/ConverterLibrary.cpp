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

#include "ConverterLibrary.h"

ConverterLibrary::ConverterLibrary() {
}

QString ConverterLibrary::Parser(const QString &file){
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    QXmlQuery xmlQuery;
    QString FilePath(file);
    QFile inputFile(FilePath);

    QString objId, objLat, objLon, wayId, rezalt, objName, forPost, postgr;
    QStringList listObjId, listWayId, listObjName, listObjLon, listObjLat;

    bool isOpen = inputFile.open(QIODevice::ReadOnly | QIODevice::Text);
    xmlQuery.setFocus(&inputFile);

    if (isOpen){
        QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
        db.setHostName("127.0.0.1");
        db.setDatabaseName("GIS");
        db.setPort(5432);
        db.setUserName("postgres");
        db.setPassword("1234");

        bool isConnected = db.open();

        if (isConnected){
            QSqlQuery sqlQueryF, sqlQueryS;

            xmlQuery.setQuery("osm/way[(*/@k='building')and(*/@k='name')]/@id/string()");
            xmlQuery.evaluateTo(&wayId);
            wayId.remove(QChar('\n'), Qt::CaseInsensitive);
            listWayId = wayId.split(QRegExp("\\s+"));
            forPost = "";
            postgr = "";
            for (int k=0; k<(listWayId.count()); k++){
                xmlQuery.setQuery("osm/way[@id='"+listWayId[k]+"']/tag[@k='name']/@v/string()");
                xmlQuery.evaluateTo(&objName);
                objName.remove(QChar('\n'), Qt::CaseInsensitive);
                listObjName << objName;

                xmlQuery.setQuery("osm/way[*/@v='"+objName+"']/nd[@ref]/@ref/string()");
                xmlQuery.evaluateTo(&objId);
                objId.remove(QChar('\n'), Qt::CaseInsensitive);

                listObjId = objId.split(QRegExp("\\s+"));
                rezalt += objName + "\n";
                forPost = "";
                for (int i=0; i<(listObjId.count()); i++){
                    xmlQuery.setQuery("osm/node[@id='"+listObjId[i]+"']/@lat/string()");
                    xmlQuery.evaluateTo(&objLat);
                    objLat.remove(QChar('\n'), Qt::CaseInsensitive);
                    listObjLat = objLat.split(QRegExp("\\s+"));

                    xmlQuery.setQuery("osm/node[@id='"+listObjId[i]+"']/@lon/string()");
                    xmlQuery.evaluateTo(&objLon);
                    objLon.remove(QChar('\n'), Qt::CaseInsensitive);
                    listObjLon = objLon.split(QRegExp("\\s+"));

                    rezalt += "lat = " + objLat + " lon = " + objLon + "\n";
                    forPost += objLat + " " + objLon + ", ";
                }
                forPost = forPost.left(forPost.length()-2);
                int z=k+1;
                postgr = "LINESTRING(" + forPost + ")";
                sqlQueryF.prepare("INSERT INTO objects (id_obj, geometry_obj)"
                                  "VALUES (:id, :geo);");
                sqlQueryF.bindValue(":id", z);
                sqlQueryF.bindValue(":geo", postgr);
                sqlQueryF.exec();

                sqlQueryS.prepare("INSERT INTO tags (id_tag, key_tag, value_tag, id_obj)"
                                    "VALUES(:id, 'building', :val, :obj);");
                sqlQueryS.bindValue(":id", z);
                sqlQueryS.bindValue(":val", objName);
                sqlQueryS.bindValue(":obj", z);
                sqlQueryS.exec();
            }

        }else{
            rezalt = tr("Соединение с базой данных не установлено.");
        }

        db.close();
    }else{
        rezalt = tr("Файл не найден. Введите другое имя файла!");
    }
    inputFile.close();

    return rezalt;
}

