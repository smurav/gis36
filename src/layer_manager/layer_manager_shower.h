#ifndef LAYER_MANAGER_H
#define LAYER_MANAGER_H

#include <QString>
#include "../includes/plugin_interface.h"





// Основной класс плагина
class LayerMananagerShower : public QObject, public PluginInterface {
    Q_OBJECT
    Q_INTERFACES(PluginInterface)

private:
    // Интерфейс для работы с основным модулем программы
    ShellInterface* f_shell;
    // экшн, добавляющий на тулбар кнопочку моего плагина
    QAction* action_add_layer_manager_form;

private slots:
    // Функция вывода на экран окошка менеджера слоёв
    void init_layer_manager_slot();

public:
    // Переопределяем основные методы интерфейса
    int Init(ShellInterface*);
    int Stop();
};


#endif // LAYER_MANAGER_H
