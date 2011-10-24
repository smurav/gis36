#ifndef PLUGIN_MANAGER_H
#define PLUGIN_MANAGER_H

#include <QDialog>
#include "shell_interface.h"

namespace Ui {
    class PluginManager;
}

class PluginManager : public QDialog
{
    Q_OBJECT

public:
    explicit PluginManager(ShellInterface*, QWidget *parent = 0 );
    ~PluginManager();

private:
    Ui::PluginManager *ui;
    ShellInterface *shell_interface_;
    void SetupListPlugins(QDomNode);
private slots:
    void addNewPlugin();
    void removePlugin();
    void turnOnPlugin();
    void turnOffPlugin();
};

#endif // PLUGIN_MANAGER_H
