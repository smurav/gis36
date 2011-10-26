
#include "search_by_region.h"
#include "search_by_region_window.h"


#include <QtGui>
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


int SearchByRegion::Init(ShellInterface * shell)
{
    // Инициализация начальных значений
    cafe_dialog = NULL;

    // Запоминаем указатель на главный интерфейс во внутреннюю переменную
    f_shell = shell;

    // Получение указателей на Toolbar и Menu, для последующего
    // добавление в них своих пунктов
    QToolBar* main_toolbar = f_shell->GetPluginsToolBar();
    QMenu* main_menu = f_shell->GetPluginsMenu();

    // Создание действия для вывода нового окошка
    try{
        cafe_dialog = new QAction(tr("Cafe"), this);
        //cafe_dialog->setShortcut(tr("Ctrl+H"));
        cafe_dialog->setStatusTip(tr("Cafe"));
        connect(cafe_dialog, SIGNAL(triggered()), this, SLOT(Cafe()));
    }catch(...){
        return ERR_UNABLE_CREATE_ACTION;
    }

    // Добавляем кнопку на панель инструментов
    try{
        main_toolbar->addAction(cafe_dialog);
    }catch(...){
        return ERR_UNABLE_ADD_ACTION_TO_TOOLBAR;
    }

    // Добавляем свой пункт в меню
    try{
        main_menu->addAction(cafe_dialog);
    }catch(...){
        return ERR_UNABLE_ADD_ACTION_TO_MENU;
    }

    return RES_OK;
}

int SearchByRegion::Stop()
{
    if(cafe_dialog != NULL)
        delete cafe_dialog;

    return RES_OK;
}

void SearchByRegion::Cafe()
{
    SearchByRegionWindow *window = new SearchByRegionWindow();
    window->show();
}

Q_EXPORT_PLUGIN2(gis36_SearchByRegion, SearchByRegion)
