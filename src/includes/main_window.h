#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsView>
#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    virtual  QGraphicsView* GetGraphicsView();
    virtual QMenu* GetPluginsMenu();
    virtual QToolBar* GetPluginsToolBar();
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
};

#endif // MAINWINDOW_H
