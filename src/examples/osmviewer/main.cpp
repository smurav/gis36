#define __WORDSIZE = 32

#include <QtGui/QApplication>
#include <QTextCodec>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
  QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
