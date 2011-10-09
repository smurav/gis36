#ifndef SETTINGS_PARSER_H
#define SETTINGS_PARSER_H

#include "QtXml/QDomDocument"

class SettingsParser
{
public:
    SettingsParser(SettingsParser&);
    SettingsParser(QString&);
    QDomDocument* GetSettings();
    void WriteSettings(QDomDocument);
    void CreateFileSettings();
private:
    QString file_name_;
};

#endif // SETTINGS_PARSER_H
