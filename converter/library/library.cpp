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
