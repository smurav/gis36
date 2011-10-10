#include <QtCore/QDebug>
#include <QApplication>
#include <QtCore/QXmlStreamReader>
#include <QtCore/QString>
#include <QtCore/QFile>
#include <QLabel>
#include <QXmlStreamAttributes>

int main(int argc, char *argv[]){

    QApplication app(argc, argv);

    QString FilePath("map.xml");
    QFile inputFile(FilePath);
    inputFile.open(QIODevice::ReadOnly | QIODevice::Text);

    QXmlStreamReader reader(&inputFile);
    while (!reader.atEnd()){
        reader.readNext();
        if (reader.isStartElement()){
            //if (reader.name() == "node"){  //это условие для вывода только тегов <node>
                qDebug() << reader.name().toString();
                QXmlStreamAttributes attrs = reader.QXmlStreamReader::attributes();
                for (int i = 0; i < attrs.count(); i++)
                 qDebug() << attrs[i].name().toString() << "=" << attrs[i].value().toString();
           // }
        }
    }

    inputFile.close();

    return app.exec();
}


