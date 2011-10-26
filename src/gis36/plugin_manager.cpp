#include "plugin_manager.h"
#include "ui_plugin_manager.h"
#include "iostream"

PluginManager::PluginManager(ShellInterface *shell, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PluginManager)
{
    shell_interface_=shell;


    ui->setupUi(this);
    setFixedSize(400,300);
    plugin_info_ = shell_interface_->GetSettings()->GetListPluginInfo();
    if (plugin_info_!=NULL && !plugin_info_->isEmpty()){
        SetupListPlugins(*plugin_info_);
    }
}

PluginManager::~PluginManager()
{
    delete ui;
}

void PluginManager::SetupListPlugins(const QList<PluginInfo> &plugins){
    ui->list_plugins->clear();
    for (int i=0; i<plugins.size(); i++){
        QListWidgetItem *list_item= new QListWidgetItem();
        list_item->setData(Qt::DisplayRole, plugins.at(i).GetName());
        if (plugins.at(i).IsEnabled()){
            list_item->setBackgroundColor(QColor(0,200,0));
        } else {
            list_item->setBackgroundColor(QColor(200,0,0));
        }
        ui->list_plugins->addItem(list_item);
    }
}

void PluginManager::addNewPlugin()
{
    plugin_info_ =shell_interface_->GetSettings()->GetListPluginInfo();
    shell_interface_->GetSettings()->WriteListPluginInfo(plugin_info_);
    std::cerr<<"addPlugin"<<std::endl;
}

void PluginManager::removePlugin()
{
    QListWidgetItem *current_item = ui->list_plugins->currentItem();
    if (current_item==NULL){
        ShowMessage("Select plugin");
        return;
    }
    QString current_name = current_item->text();
    for (int i=0; i<plugin_info_->size(); i++){
        if( plugin_info_->at(i).GetName()==current_name){
            plugin_info_->removeAt(i);
        }
    }
    shell_interface_->GetSettings()->WriteListPluginInfo(plugin_info_);
    SetupListPlugins(*plugin_info_);
    std::cerr<<"removePlugin"<<std::endl;
}

void PluginManager::turnOnPlugin()
{
    QListWidgetItem *current_item = ui->list_plugins->currentItem();
    if (current_item==NULL){
        ShowMessage("Select plugin");
        return;
    }
    QString current_name = current_item->text();
    for (int i=0; i<plugin_info_->size(); i++){
        if( plugin_info_->at(i).GetName()==current_name){
            PluginInfo info(plugin_info_->at(i).GetName(),
                            plugin_info_->at(i).GetDirectory(), true);
            //plugin_info_->at(i).SetEnabled(true);
            plugin_info_->replace(i, info);
        }
    }
    shell_interface_->GetSettings()->WriteListPluginInfo(plugin_info_);
    SetupListPlugins(*plugin_info_);
    std::cerr<<"turnOnPlugin"<<std::endl;
}

void PluginManager::turnOffPlugin()
{
    QListWidgetItem *current_item = ui->list_plugins->currentItem();
    if (current_item==NULL){
        ShowMessage("Select plugin");
        return;
    }
    QString current_name = current_item->text();
    for (int i=0; i<plugin_info_->size(); i++){
        if( plugin_info_->at(i).GetName()==current_name){
            PluginInfo info(plugin_info_->at(i).GetName(),
                            plugin_info_->at(i).GetDirectory(), false);
            //plugin_info_->at(i).SetEnabled(false);
            plugin_info_->replace(i, info);
        }
    }
    shell_interface_->GetSettings()->WriteListPluginInfo(plugin_info_);
    SetupListPlugins(*plugin_info_);
    std::cerr<<"turnOffPlugin"<<std::endl;
}
void PluginManager::ShowMessage(const QString& str){
    QMessageBox message;
    message.setIcon(QMessageBox::Information);
    message.setText(str);
    message.exec();
}


