#include <QtGui>

#include "pluginhello.h"


/*
  КОДЫ ОШИБОК
*/
          // Всё прошло успешно.
const int RES_OK = 0;
          // Не удалось создать действие
const int ERR_UNABLE_CREATE_ACTION = RES_OK + 1;
          // Невозможно добавить кнопку на панель инструментов
const int ERR_UNABLE_ADD_ACTION_TO_TOOLBAR = RES_OK + 2;
          // Невозможно добавить пункт в меню
const int ERR_UNABLE_ADD_ACTION_TO_MENU = RES_OK + 3;


int PluginHello::Init(ShellInterface * shell)
{
    // Инициализация начальных значений
    action_hello = NULL;

    // Запоминаем указатель на главный интерфейс во внутреннюю переменную
    f_shell = shell;

    // Получение указателей на Toolbar и Menu, для последующего
    // добавление в них своих пунктов
    QToolBar* main_toolbar = f_shell->GetPluginsToolBar();
    QMenu* main_menu = f_shell->GetPluginsMenu();

    // Создание действия для вывода сообщения "Hello, world!" на экран
    try{
        action_hello = new QAction(tr("Hello world!"), this);
        action_hello->setShortcut(tr("Ctrl+H"));
        action_hello->setStatusTip(tr("Hello world!"));
        connect(action_hello, SIGNAL(triggered()), this, SLOT(Hello()));
    }catch(...){
        return ERR_UNABLE_CREATE_ACTION;
    }

    // Добавляем кнопку на панель инструментов
    try{
        main_toolbar->addAction(action_hello);
    }catch(...){
        return ERR_UNABLE_ADD_ACTION_TO_TOOLBAR;
    }

    // Добавляем свой пункт в меню
    try{
        main_menu->addAction(action_hello);
    }catch(...){
        return ERR_UNABLE_ADD_ACTION_TO_MENU;
    }

    return RES_OK;
}

int PluginHello::Stop()
{
    if(action_hello != NULL)
        delete action_hello;

    return RES_OK;
}


void PluginHello::Hello()
{
    QMessageBox message;
    message.setIcon(QMessageBox::Information);
    message.setText("Hello, World! I'm plugin!");
    message.exec();
}

Q_EXPORT_PLUGIN2(gis36_hello, PluginHello)
