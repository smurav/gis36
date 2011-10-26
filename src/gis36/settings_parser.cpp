#include "settings_parser.h"
#include "QFile"
#include "QTextStream"
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

/**
  *Загружает данные из file_name_ в document
  *
  */
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
    document=doc;
    return doc;
}

/**
  *Достает из document записи о плагинах, возвращает информацию о плагинах.
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

int SettingsParser::WriteListPluginInfo(QList<PluginInfo> *plugins_info)
{
    Reload();
    QDomNode settings= FindElementByTag(*document, "settings");
    if (settings.isNull()){
        CreateFileSettings();
        Reload();
        QDomNode settings= FindElementByTag(*document, "settings");
        if (settings.isNull()){
            return -1;
        }
    }
    QDomNode plugins = FindElementByTag(settings, "plugins");
    if (!plugins.isNull()){
        settings.replaceChild(MakePluginsNode(plugins_info), plugins);
    } else {
        settings.appendChild(MakePluginsNode(plugins_info));
    }

    QFile file(file_name_);
    if(file.exists()){
        file.remove();

    }
    if (!file.open(QFile::ReadWrite|QFile::Text)){
        std::cerr<<"Error: Cannot open settings file"<<std::endl;
        return -2;
    }

    QTextStream stream(&file);
    document->save(stream,4);
    return 0;
}
QDomNode SettingsParser::MakePluginsNode(QList<PluginInfo>* plugins_info){
    QDomDocument doc;
    QDomElement plugins=doc.createElement("plugins");
    doc.appendChild(plugins);
    //QDomNode plugins = QDomNode();
    plugins.toElement().setTagName("plugins");
    for (int i=0; i<plugins_info->size(); i++){
        QDomElement plugin = doc.createElement("plugin");
        QDomElement name = doc.createElement("name");
        QDomElement directory = doc.createElement("directory");
        QDomElement enabled = doc.createElement("enabled");
        QDomText nameText = doc.createTextNode(plugins_info->at(i).GetName());
        QDomText directoryText = doc.createTextNode(plugins_info->at(i).GetDirectory());
        QString en;
        if (plugins_info->at(i).IsEnabled()){
            en="true";
        } else {
            en="false";
        }
        QDomText enabledText = doc.createTextNode(en);
        plugins.appendChild(plugin);
        plugin.appendChild(name);
        name.appendChild(nameText);
        plugin.appendChild(directory);
        directory.appendChild(directoryText);
        plugin.appendChild(enabled);
        enabled.appendChild(enabledText);
    }
    return plugins;
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






