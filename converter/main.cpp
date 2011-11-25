#include <QtCore/QDebug>
#include <QApplication>
#include <QtCore/QXmlStreamReader>
#include <QtCore/QString>
#include <QtCore/QFile>
#include <QLabel>
#include <QXmlStreamAttributes>
#include <QtXmlPatterns/QXmlQuery>
#include <QTextCodec>
#include "converterinterface.h"
#include "ConverterLibrary.h"

int main(int argc, char *argv[]){

    QApplication app(argc, argv);

    QTextCodec *cyrillicCodec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(cyrillicCodec);
    QTextCodec::setCodecForLocale(cyrillicCodec);
    QTextCodec::setCodecForCStrings(cyrillicCodec);

    ConverterInterface *dialog = new ConverterInterface;
    dialog->show();


    return app.exec();
}


