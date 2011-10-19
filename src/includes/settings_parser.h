#ifndef SETTINGS_PARSER_H
#define SETTINGS_PARSER_H

#include "QtXml/QDomDocument"

class SettingsParser
{
public:
    SettingsParser();
    SettingsParser(SettingsParser&);
    SettingsParser(QString);
    virtual QDomDocument* GetSettings();
    virtual void WriteSettings(QDomDocument);
    virtual void CreateFileSettings();
    virtual QList<QString> *GetPluginsPaths();
private:
    QString file_name_;
    QDomDocument* document;

    QDomDocument* Reload();
};

#endif // SETTINGS_PARSER_H
