#ifndef SETTINGS_PARSER_H
#define SETTINGS_PARSER_H

#include "QtXml/QDomDocument"
#include "QColor"

class PluginInfo
{
public:
    PluginInfo();
    PluginInfo(const QString &name, const QString &directory, const bool &enabled);
    void SetName(const QString&);
    void SetDirectiry(const QString&);
    void SetEnabled(bool);
    QString GetName() const;
    QString GetDirectory() const;
    bool IsEnabled() const;

    //QColor ColorEnabled = QColor(200, 200, 200);
    //QColor ColorDesabled= QColor(240,240,240);
private:
    QString name_;
    QString directory_;
    bool enabled_;
};

class SettingsParser
{
public:
    SettingsParser();
    SettingsParser(SettingsParser&);
    SettingsParser(QString);
    QDomDocument* GetSettings();
    void WriteSettings(QDomDocument);
    void CreateFileSettings();
    QList<PluginInfo> *GetListPluginInfo();
private:
    QString file_name_;
    QDomDocument* document;

    QDomDocument* Reload();
    QDomNode FindElementByTag(QDomNode node, QString tag);
};



#endif // SETTINGS_PARSER_H
