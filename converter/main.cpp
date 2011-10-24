#include <QtCore/QDebug>
#include <QApplication>
#include <QtCore/QXmlStreamReader>
#include <QtCore/QString>
#include <QtCore/QFile>
#include <QLabel>
#include <QXmlStreamAttributes>
#include <QtXmlPatterns/QXmlQuery>
#include "converterinterface.h"
#include "library.h"

int main(int argc, char *argv[]){

    QApplication app(argc, argv);

    ConverterInterface *dialog = new ConverterInterface;
    dialog->show();
    return app.exec();
}


