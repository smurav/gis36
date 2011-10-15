#ifndef PLUGIN_INTERFACE_H
#define PLUGIN_INTERFACE_H
#include "shell_interface.h"

class PluginInterface
{
public:
    virtual ~PluginInterface(){}
    virtual void Init(ShellInterface*);
    virtual void Stop();
};
Q_DECLARE_INTERFACE(PluginInterface,
"com.gis36.PluginInterface/1.0")
#endif // PLUGIN_INTERFACE_H
