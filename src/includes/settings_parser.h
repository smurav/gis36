#ifndef SETTINGS_PARSER_H
#define SETTINGS_PARSER_H

#include "QtXml/QDomDocument"

class SettingsParser
{
public:
    SettingsParser();
    SettingsParser(SettingsParser&);
    SettingsParser(QString);
    QDomDocument* GetSettings();
    void WriteSettings(QDomDocument);
    void CreateFileSettings();
    QList<QString> *GetPluginsPaths();
private:
    QString file_name_;
    QDomDocument* document;

    QDomDocument* Reload();
};

#endif // SETTINGS_PARSER_H
