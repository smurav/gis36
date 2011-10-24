#include <QtGui>
#include "layer_manager_shower.h""
#include "layer_form.h"

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


int Layer_manager_shower::Init(ShellInterface * shell)
{
    // Инициализация начальных значений
    action_add_layer_manager_form = NULL;

    // Запоминаем указатель на главный интерфейс во внутреннюю переменную
    f_shell = shell;

    // Получение указателей на Toolbar и Menu, для последующего
    // добавление в них своих пунктов
    QToolBar* main_toolbar = f_shell->GetPluginsToolBar();
    QMenu* main_menu = f_shell->GetPluginsMenu();

    // Создание действия для вывода формы работы со слоями
    try{
        action_add_layer_manager_form = new QAction(tr("Layer Manager!"), this);
        action_add_layer_manager_form->setShortcut(tr("Ctrl+H"));
        action_add_layer_manager_form->setStatusTip(tr("Hello world!"));
        connect(action_add_layer_manager_form, SIGNAL(triggered()),
                this, SLOT(init_layer_manager_slot()));
    }catch(...){
        return ERR_UNABLE_CREATE_ACTION;
    }

    // Добавляем кнопку на панель инструментов
    try{
        main_toolbar->addAction(action_add_layer_manager_form);
    }catch(...){
        return ERR_UNABLE_ADD_ACTION_TO_TOOLBAR;
    }

    // Добавляем свой пункт в меню
    try{
        main_menu->addAction(action_add_layer_manager_form);
    }catch(...){
        return ERR_UNABLE_ADD_ACTION_TO_MENU;
    }

    return RES_OK;
}

int Layer_manager_shower::Stop()
{
    if(action_add_layer_manager_form != NULL)
        delete action_add_layer_manager_form;

    return RES_OK;
}


void Layer_manager_shower::init_layer_manager_slot()
{
  layer_form *layer_manager_form = new layer_form();
  layer_manager_form->show();
}

Q_EXPORT_PLUGIN2(gis36_layer_manager, Layer_manager_shower)
