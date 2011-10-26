#ifndef SEARCH_BY_REGION_H
#define SEARCH_BY_REGION_H

#include "Search_By_Region_global.h"

#include "../includes/plugin_interface.h"

// Основной класс плагина
class SearchByRegion: public QObject, public PluginInterface{
    Q_OBJECT
    Q_INTERFACES(PluginInterface)

private:
    // Интерфейс для работы с основным модулем программы
    ShellInterface* f_shell;
    // Основное действие модуля - новое окошко с запросом радиуса например
    QAction* cafe_dialog;

private slots:
    // Функция вывода окошка на экран
    void Cafe();

public:
    // Переопределяем основные методы интерфейса
    int Init(ShellInterface*);
    int Stop();
};

#endif // SEARCH_BY_REGION_H
