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

QList<QString> * SettingsParser::GetPluginsPaths(){
    return NULL;
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
