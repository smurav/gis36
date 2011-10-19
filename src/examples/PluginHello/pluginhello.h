#ifndef PLUGINHELLO_H
#define PLUGINHELLO_H

#include <QString>

#include "plugin_interface.h"

// Основной класс плагина
class PluginHello: public QObject, public PluginInterface{
    Q_OBJECT
    Q_INTERFACES(PluginInterface)

private:    
    // Интерфейс для работы с основным модулем программы
    ShellInterface* f_shell;
    // Основное действие модуля - вывод сообщений "Hello, world!"
    QAction* action_hello;    

private slots:
    // Функция вывода на экран сообщения "Hello, world!"
    void Hello();

public:
    // Переопределяем основные методы интерфейса
    int Init(ShellInterface*);
    int Stop();
};

#endif // PLUGINHELLO_H
