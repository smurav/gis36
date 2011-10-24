#include <QtCore/QXmlStreamReader>
#include <QtCore/QDebug>
#include <QtCore/QString>
#include <QtCore/QFile>
#include <QtXmlPatterns/QXmlQuery>
#include <QXmlStreamAttributes>
#include "library.h"

Library::Library() {
}

int Library::Sum(int a, int b) {
  return a + b;
}

QString Library::Parser(const QString &prs){
    /*QString rez;

    QString FilePath(prs);
    QFile inputFile(FilePath);

    inputFile.open(QIODevice::ReadOnly | QIODevice::Text);

    QXmlStreamReader reader(&inputFile);
    while (!reader.atEnd()){
        reader.readNext();
        if (reader.isStartElement()){
            //if (reader.name() == "pop"){  //это условие для вывода только тегов <node>
            rez += reader.name().toString() + " ";
                QXmlStreamAttributes attrs = reader.QXmlStreamReader::attributes();
                for (int i = 0; i < attrs.count(); i++){
                    rez += attrs[i].name().toString() + "=" + attrs[i].value().toString() + " ";
                }
            //}
        }
    }

    inputFile.close();
    return rez;*/

    QXmlQuery query;
    QString rez;
    QString FilePath(prs);
    QFile inputFile(FilePath);

    inputFile.open(QIODevice::ReadOnly | QIODevice::Text);
    query.setFocus(&inputFile);
    query.setQuery("osm/pop[@user='sanok']");
    //assert(query.isValid());
    query.evaluateTo(&rez);
    inputFile.close();
    return rez;

}
