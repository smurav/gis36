#include "shell_interface.h"

ShellInterface::ShellInterface(MainWindow *main_window, SettingsParser* settings)
{
    main_window_=main_window;
    settings_=settings;
}

QGraphicsView* ShellInterface::GetGraphicsView(){
    return main_window_->GetGraphicsView();
}

QMenu* ShellInterface::GetPluginsMenu(){
    return main_window_->GetPluginsMenu();
}

QToolBar* ShellInterface::GetPluginsToolBar(){
    return main_window_->GetPluginsToolBar();
}

MainWindow* ShellInterface::GetMainWindow(){
    return main_window_;
}

SettingsParser* ShellInterface::GetSettings(){
    return settings_;
}
