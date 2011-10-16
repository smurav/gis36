#ifndef PLUGINHELLO_H
#define PLUGINHELLO_H

#include "plugin_interface.h"

class PluginHello: public QObject, public PluginInterface{
    Q_OBJECT
    Q_INTERFACES(PluginInterface)

private:
    ShellInterface* f_shell;
    QAction* action_hello;


private slots:
    void Hello();

public:
    void Init(ShellInterface*);
    void Stop();
};

#endif // PLUGINHELLO_H
