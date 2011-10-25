#include "plugin_manager.h"
#include "ui_plugin_manager.h"
#include "iostream"

PluginManager::PluginManager(ShellInterface *shell, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PluginManager)
{
    shell_interface_=shell;


    ui->setupUi(this);
//    QDomDocument *settings = shell->GetSettings()->GetSettings();
//    /*if (!settings->isNull()){
//    QDomNode child = settings->firstChild();

//    while (!child.isNull()){

//        std::cerr<<qPrintable(child.toElement().tagName())<<std::endl;
//        if (child.toElement().tagName()=="settings"){
//            QDomNode plugins = child.firstChild();
//            while (!plugins.isNull()){
//                std::cerr<<qPrintable(plugins.toElement().tagName())<<std::endl;
//                if (plugins.toElement().tagName()=="plugins"){
//                    setupListPlugins(plugins);
//                    break;
//                } else {
//                    plugins=plugins.nextSibling();
//                }
//            }
//            break;
//        }else {
//            child=child.nextSibling();
//        }
//    }
//    }*/
//    if (settings->isNull()){
//        return;
//    }
//    QDomNode child = settings->firstChild();
//    while (!child.isNull()){
//        if (child.toElement().tagName()=="settings"){
//            break;
//        } else {
//            child = child.nextSibling();
//        }
//    }
//    if (child.isNull()){
//        std::cerr<<"settings tag not found"<<std::endl;
//        return;
//    }
//    QDomNode plugins = child.firstChild();
//    while (!plugins.isNull()&&plugins.toElement().tagName()!="plugins"){
//        plugins= plugins.nextSibling();
//    }
//    if (plugins.isNull()){
//        std::cerr<<"plugins tag not found"<<std::endl;
//    }
    QList<PluginInfo> *info = shell_interface_->GetSettings()->GetListPluginInfo();
    if (info!=NULL && !info->isEmpty()){
        SetupListPlugins(*info);
    }
}

PluginManager::~PluginManager()
{
    delete ui;
}

void PluginManager::SetupListPlugins(const QList<PluginInfo> &plugins){
    for (int i=0; i<plugins.size(); i++){
        QListWidgetItem *list_item= new QListWidgetItem();
        list_item->setData(Qt::DisplayRole, plugins.at(i).GetName());
        if (plugins.at(i).IsEnabled()){
            list_item->setBackgroundColor(QColor(200,200,200));
        } else {
            list_item->setBackgroundColor(QColor(240,240,240));
        }
        ui->list_plugins->addItem(list_item);
    }
//    QDomNode child = plugins.firstChild();
//    while (!child.isNull()){
//        if (child.toElement().tagName()=="plugin"){
//            QDomNode plugin_node = child.firstChild();
//            while (!plugin_node.isNull()){
//                if (plugin_node.toElement().tagName()=="name"){
//                    QListWidgetItem* list_item=
//                            new QListWidgetItem();
//                    list_item->setData(Qt::DisplayRole,
//                                       plugin_node.toElement().text());
//                    std::cerr<<qPrintable(plugin_node.toElement().tagName())<<std::endl;
//                    ui->list_plugins->addItem(list_item);
//                }
//                plugin_node = plugin_node.nextSibling();
//            }
//        }
//        child = child.nextSibling();
//    }
    ui->list_plugins;
}

void PluginManager::addNewPlugin()
{
    std::cerr<<"addPlugin"<<std::endl;
}

void PluginManager::removePlugin()
{
    std::cerr<<"removePlugin"<<std::endl;
}

void PluginManager::turnOnPlugin()
{
    std::cerr<<"turnOnPlugin"<<std::endl;
}

void PluginManager::turnOffPlugin()
{
    std::cerr<<"turnOffPlugin"<<std::endl;
}


