#ifndef SHELLINTERFACE_H
#define SHELLINTERFACE_H
#include "QtGui"
#include "QtXml/QDomDocument"

class  ShellInterface
{
public:
    ShellInterface(QMainWindow*);
    QMenuBar GetMenuBar();
    QToolBox GetToolBox();
    QMainWindow GetMainWindow();
    QGraphicsView GetGraphicsView();
    QDomDocument GetSettingsXML();

private:
    QMainWindow *main_window_;
};

#endif // SHELLINTERFACE_H
