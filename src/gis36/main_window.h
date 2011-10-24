#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsView>
#include <QMainWindow>
#include "shell_interface.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QGraphicsView* GetGraphicsView();
    QMenu* GetPluginsMenu();
    QToolBar* GetPluginsToolBar();
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void CreateActions();
    void CreateMenu();
    void CreateToolBar();


    QToolBar *plugins_tool_bar;

    QGraphicsView *map_;

    QMenu *file_menu;
    QMenu *help_menu;
    QMenu *plugins_menu;

    QAction *action_close;
    QAction *action_start_plugin_manager;

    ShellInterface* shell_interface_;
    void LoadPlugins(QList<QString>*);
    void LoadPlugins(QString);
private slots:
    void startPluginManager();
};

#endif // MAINWINDOW_H
