#ifndef CONVERTERINTERFACE_H
#define CONVERTERINTERFACE_H
#include <QDialog>
#include "library.h"

class QLabel;
class QLineEdit;
class QPushButton;
class QComboBox;
class QString;
class QStringList;
class QTextEdit;

class ConverterInterface : public QDialog
{
    Q_OBJECT // макрос для любых классов, включающих сигналы и слоты

public:
    ConverterInterface(QWidget *parent = 0);

signals:
    void findNext(const QString &str, Qt::CaseSensitivity cs);

private slots:
    void enableOkButton(const QString &text);
    void setQuery();
    void empty();
    bool error();

private:
    QLabel *labelbox;
    QLineEdit *lineEdit;
    QLineEdit *path;
    QTextEdit *process;
    QComboBox *box;
    QStringList stringList;
    QPushButton *okButton;
    QPushButton *closeButton;
    QString *text;
    QString *str;
    //QString *file;
};

#endif // CONVERTERINTERFACE_H
