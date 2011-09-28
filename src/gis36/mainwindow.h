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
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void createActions();
    void createMenu();
    void createToolBar();

    QToolBar *plagins_tool_bar;

    QGraphicsView *map;

    QMenu *file_menu;
    QMenu *help_menu;
    QMenu *plagins_menu;

    QAction *action_close;
};

#endif // MAINWINDOW_H
