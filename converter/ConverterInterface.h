#ifndef CONVERTERINTERFACE_H
#define CONVERTERINTERFACE_H
#include <QDialog>
#include "ConverterLibrary.h"

class QLabel;
class QLineEdit;
class QPushButton;
class QComboBox;
class QString;
class QStringList;
class QTextEdit;

class ConverterInterface : public QDialog
{
    Q_OBJECT

public:
    ConverterInterface(QWidget *parent = 0);

signals:
    void findNext(const QString &str, Qt::CaseSensitivity cs);

private slots:

public slots:
    void OnOkButton();
    void OnFindButton();

private:
    QLabel *labelbox;
    QLineEdit *lineEdit;
    QLineEdit *path;
    QTextEdit *process;
    QComboBox *box;
    QStringList stringList;
    QPushButton *okButton;
    QPushButton *findButton;
    QPushButton *closeButton;
    QString *text;
    QString *str;
    ConverterLibrary *lib;
    //QString *file;
};

#endif // CONVERTERINTERFACE_H
