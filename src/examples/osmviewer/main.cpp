<<<<<<< HEAD
=======
#define __WORDSIZE = 32

>>>>>>> da716cc6f3ac4c24d8c92a8faaca344e0473697f
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
