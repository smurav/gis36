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

QString Library::Parser(const QString &file, const QString &path){
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
    QString FilePath(file);
    QFile inputFile(FilePath);

    inputFile.open(QIODevice::ReadOnly | QIODevice::Text);
    query.setFocus(&inputFile);
    query.setQuery(path);
    //assert(query.isValid());
    //query.selectSingleNode("v").nodeTypedValue;
    query.evaluateTo(&rez);
    inputFile.close();
    return rez;

}
