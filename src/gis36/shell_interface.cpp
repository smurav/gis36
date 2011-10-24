#include "shell_interface.h"
#include "main_window.h"
MainWindow *my_window;
ShellInterface::ShellInterface(QMainWindow *main_window, SettingsParser* settings)
{
    main_window_=main_window;
    settings_=settings;
}

QGraphicsView* ShellInterface::GetGraphicsView(){
    my_window =dynamic_cast<MainWindow*>(main_window_);
    return my_window->GetGraphicsView();
}

QMenu* ShellInterface::GetPluginsMenu(){
    my_window =dynamic_cast<MainWindow*>(main_window_);
    return my_window->GetPluginsMenu();
}

QToolBar* ShellInterface::GetPluginsToolBar(){
    my_window =dynamic_cast<MainWindow*>(main_window_);
    return my_window->GetPluginsToolBar();
}

QMainWindow* ShellInterface::GetMainWindow(){
    return main_window_;
}

SettingsParser* ShellInterface::GetSettings(){
    return settings_;
}
