#ifndef START_PLUGIN_H
#define START_PLUGIN_H

#include <QtGui>
#include "../gis36/plugin_interface.h"

class StartPlugin : public QWidget, public PluginInterface
{
    Q_OBJECT
    Q_INTERFACES(PluginInterface)
private:
    ShellInterface* f_shell;
    QAction* action_hello;

public:
    int Init(ShellInterface *);
    int Stop();
signals:

public slots:
    void Hello();
};

#endif // START_PLUGIN_H
