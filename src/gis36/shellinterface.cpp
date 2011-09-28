#include "shellinterface.h"

ShellInterface::ShellInterface()
{

}

ShellInterface::ShellInterface(ShellInterface *shell_interface)
{

}

ShellInterface::ShellInterface(QMainWindow *main_window)
{
    _main_window=main_window;
}

void addActionToToolBar(QAction *action)
{

}
