#include "../includes/main_window.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    map_ = new QGraphicsView(this);
    setCentralWidget(map_);

    CreateActions();
    CreateMenu();
    CreateToolBar();

}

QGraphicsView* MainWindow::GetGraphicsView(){
    return map_;
}

QToolBar* MainWindow::GetPluginsToolBar(){
    return plugins_tool_bar;
}

QMenu* MainWindow::GetPluginsMenu(){
    return plugins_menu;
}

void MainWindow::CreateActions()
{
    action_close = new QAction(tr("Exit"), this);
    action_close->setShortcut(tr("Ctrl+Q"));
    action_close->setStatusTip(tr("Exit"));
    connect(action_close, SIGNAL(triggered()), this, SLOT(close()));

}

void MainWindow::CreateMenu()
{
    file_menu= menuBar()->addMenu(tr("&File"));
    file_menu->addAction(action_close);
    plugins_menu = menuBar()->addMenu(tr("&Plugins"));
    help_menu = menuBar()->addMenu(tr("&Help"));

}

void MainWindow::CreateToolBar()
{
    plugins_tool_bar= this->addToolBar(tr("Plagins"));
    plugins_tool_bar->addAction(action_close);
}

MainWindow::~MainWindow()
{
    delete ui;
}
