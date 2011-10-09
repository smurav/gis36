#ifndef SHELLINTERFACE_H
#define SHELLINTERFACE_H
#include "QtGui"

class  ShellInterface
{
public:
    ShellInterface();
    ShellInterface(const ShellInterface&);
    ShellInterface(QMainWindow);
    void addActionToToolBox(QAction);
    void addActionToMenu(QAction);
    bool addPanel(QWidget);
    QGraphicsView getGraphicsArea();

private:
    QMainWindow *_main_window;
};

#endif // SHELLINTERFACE_H
