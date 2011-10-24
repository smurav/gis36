#ifndef SHELLINTERFACE_H
#define SHELLINTERFACE_H
#include "QtGui"
#include "QtXml/QDomDocument"
#include "../gis36/settings_parser.h"
class  ShellInterface
{
public:
    ShellInterface(QMainWindow*, SettingsParser*);
    virtual QMenu* GetPluginsMenu();
    virtual QToolBar* GetPluginsToolBar();
    virtual QMainWindow* GetMainWindow();
    virtual QGraphicsView* GetGraphicsView();
    virtual SettingsParser* GetSettings();

private:
    QMainWindow *main_window_;
    SettingsParser* settings_;
};

#endif // SHELLINTERFACE_H
