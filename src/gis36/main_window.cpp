#include "plugin_manager.h"
#include "ui_mainwindow.h"
#include "main_window.h"
#include "plugin_interface.h"
#include "iostream"

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
    SettingsParser * settings = new SettingsParser();
    shell_interface_ = new ShellInterface(this, settings);
    LoadPlugins(settings->GetListPluginInfo());
    //LoadPlugins("../plugin/output/gis_hellod.dll");
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

    action_start_plugin_manager = new QAction(tr("Plugin Manager"), this);
    connect(action_start_plugin_manager, SIGNAL(triggered()), this,
            SLOT(startPluginManager()));

}

void MainWindow::CreateMenu()
{
    file_menu= menuBar()->addMenu(tr("&File"));
    file_menu->addAction(action_close);

    plugins_menu = menuBar()->addMenu(tr("&Plugins"));
    plugins_menu->addAction(action_start_plugin_manager);

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

void MainWindow::startPluginManager()
{
    PluginManager *manager = new PluginManager(
                new ShellInterface(this, new SettingsParser()));
    manager->show();
}

void MainWindow::LoadPlugins(QList<PluginInfo> *info){
    if (info==NULL|| info->size()<=0) return;
    for(int i=0; i<info->length(); i++){
        if (!info->at(i).IsEnabled()){
            continue;
        }
        QString path=info->at(i).GetDirectory();
        QPluginLoader loader(path);
        if (PluginInterface *plugin =qobject_cast<PluginInterface* >(loader.instance())){
            int result=plugin->Init(new ShellInterface(this,new SettingsParser()));
            if (result){
                std::cerr<<"Error while loading plagin from "<<qPrintable(path)<<
                           "Number = "<<result<<endl;
            } else {
                QPair<QString, PluginInterface*>  pair(info->at(i).GetName(), plugin);
                runing_plugins_.append(pair);
            }
        }
    }
}

void MainWindow::LoadPlugins(QString path){
    QList<QString> *paths = new QList<QString>();
    paths->push_back(path);
    //LoadPlugins(paths);
}
void MainWindow::StopPlugins(){
    for (int i=0; i<runing_plugins_.size(); i++){
        runing_plugins_.at(i).second->Stop();
    }
}
