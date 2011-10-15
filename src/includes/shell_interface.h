#ifndef SHELLINTERFACE_H
#define SHELLINTERFACE_H
#include "QtGui"
#include "QtXml/QDomDocument"
#include "settings_parser.h"
#include "main_window.h"

class  ShellInterface
{
public:
    ShellInterface(MainWindow*, SettingsParser* );
    QMenu* GetPluginsMenu();
    QToolBar* GetPluginsToolBar();
    MainWindow* GetMainWindow();
    QGraphicsView* GetGraphicsView();
    SettingsParser* GetSettings();

private:
    MainWindow *main_window_;
    SettingsParser* settings_;
};

#endif // SHELLINTERFACE_H
