#include "settings_parser.h"
#include "QFile"
#include <iostream>

SettingsParser::SettingsParser(){
    file_name_="settings.xml";
}

SettingsParser::SettingsParser(SettingsParser &s){
}

SettingsParser::SettingsParser(QString file_name="")
{
    if (file_name==""){
        file_name_="settings.xml";
    } else {
        file_name_=file_name;
    }
}

QDomDocument* SettingsParser::GetSettings(){
    //if (document==NULL) Reload();
    document = Reload();
    return document;
}

void SettingsParser::CreateFileSettings(){
    QFile file(file_name_);

    document=new QDomDocument();

}

void SettingsParser::WriteSettings(QDomDocument doc){

}

QDomDocument* SettingsParser::Reload(){
    QDomDocument* doc= new QDomDocument();
    QFile file(file_name_);
    if (!file.open(QFile::ReadOnly|QFile::Text)){
        std::cerr<<"Error: Cannot open settings file"<<std::endl;
        return NULL;
    }

    QString error_string;
    int error_line;
    int error_column;
    if (!doc->setContent(&file, false, &error_string, &error_line,
                        &error_column)){
        std::cerr<<"Error: Parse error at line"<<error_line<<", "
                <<"column " << error_column<< ":"
               <<qPrintable(error_string)<<std::endl;
        return NULL;
    }
    return doc;
}

/**
  *Функция читает из файла настроек информацию о плагинах
  *
  */
QList<PluginInfo> * SettingsParser::GetListPluginInfo()
{
    QList<PluginInfo> *result = new QList<PluginInfo>();
    document =Reload();
    if (document->isNull()){
        std::cerr<<"Error parce settings"<<std::endl;
        return result;
    }
    //QDomNodeList settings= document->toElement().elementsByTagName("settings");
    QDomNode settings = FindElementByTag(*document, "settings");
    if (settings.isNull()){
        std::cerr<<"Error parce settings: tag settings not found"<<std::endl;
        return result;
    }
    QDomNode plugins = FindElementByTag(settings, "plugins");

    if (plugins.isNull()){
        std::cerr<<"Error parce settings: tag plugins nod found"<<std::endl;
        return result;
    }
    QDomNode plugin= FindElementByTag(plugins, "plugin");
    if (plugin.isNull()){
        std::cerr<<"Information about plugins not found"<<std::endl;
        return result;
    }
    while(!plugin.isNull()){
        QString name = FindElementByTag(plugin,"name").toElement().text();
        QString directory = FindElementByTag(plugin,"directory").toElement().text();
        QString strEnable = FindElementByTag(plugin,"enabled").toElement().text();
        bool enabled;
        if (strEnable.toLower()=="true"){
            enabled=true;
        } else {
            enabled = false;
        }
        PluginInfo info =PluginInfo(name,directory,enabled);
        result->append(info);
        plugin=plugin.nextSibling();
    }
    return result;
}

QDomNode SettingsParser::FindElementByTag(QDomNode node, QString tag){
    if (node.isNull()){
        return QDomNode();
    }
    QDomNode child= node.firstChild();
    while (!child.isNull()&& child.toElement().tagName()!=tag){
        child = child.nextSibling();
    }
    return child;

}

/**
  *Class provide information about plugin
  *
  */
PluginInfo::PluginInfo(const QString &name,const QString &directory, const bool &enabled)
{
    name_=name;
    directory_=directory;
    enabled_=enabled;
}

void PluginInfo::SetName(const QString &name)
{
    name_=name;
}

void PluginInfo::SetDirectiry(const QString &directory)
{
    directory_=directory;
}

void PluginInfo::SetEnabled(bool enabled)
{
    enabled_=enabled;
}

QString PluginInfo::GetName() const
{
    return name_;
}

QString PluginInfo::GetDirectory() const
{
    return directory_;
}

bool PluginInfo::IsEnabled() const
{
    return enabled_;
}




