#include <QtGui>
#include <QtCore/QDebug>
#include <QApplication>
#include <QtCore/QXmlStreamReader>
#include <QtCore/QString>
#include <QtCore/QFile>
#include <QLabel>
#include <QXmlStreamAttributes>
#include <QtXmlPatterns/QXmlQuery>
#include <QTextCodec>
#include "ConverterInterface.h"
#include "ConverterLibrary.h"

int main(int argc, char *argv[]){

    QApplication app(argc, argv);

    QTextCodec *cyrillicCodec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(cyrillicCodec);
    QTextCodec::setCodecForLocale(cyrillicCodec);
    QTextCodec::setCodecForCStrings(cyrillicCodec);

    ConverterInterface *dialog = new ConverterInterface;
    dialog->show();

    /*QString rez;

    QString FilePath(prs);
    QFile inputFile(FilePath);

    inputFile.open(QIODevice::ReadOnly | QIODevice::Text);

    QXmlStreamReader reader(&inputFile);
    while (!reader.atEnd()){
        reader.readNext();
        if (reader.isStartElement()){
            //if (reader.name() == "pop"){
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

    return app.exec();
}


