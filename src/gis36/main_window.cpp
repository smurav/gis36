#include "main_window.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    map = new QGraphicsView(this);
    setCentralWidget(map);

    CreateActions();
    CreateMenu();
    CreateToolBar();

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
    plagins_menu = menuBar()->addMenu(tr("&Plugins"));
    help_menu = menuBar()->addMenu(tr("&Help"));

}

void MainWindow::CreateToolBar()
{
    plagins_tool_bar= this->addToolBar(tr("Plagins"));
    plagins_tool_bar->addAction(action_close);
}

MainWindow::~MainWindow()
{
    delete ui;
}
