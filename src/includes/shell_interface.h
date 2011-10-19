#ifndef SHELLINTERFACE_H
#define SHELLINTERFACE_H
#include "QtGui"
#include "QtXml/QDomDocument"
#include "../gis36/settings_parser.h"
#include "../gis36/main_window.h"

class  ShellInterface
{
public:
    ShellInterface(MainWindow*, SettingsParser* );
    virtual QMenu* GetPluginsMenu();
    virtual QToolBar* GetPluginsToolBar();
    virtual QMainWindow* GetMainWindow();
    virtual QGraphicsView* GetGraphicsView();
    virtual SettingsParser* GetSettings();

private:
    MainWindow *main_window_;
    SettingsParser* settings_;
};

#endif // SHELLINTERFACE_H
