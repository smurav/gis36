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

class ConverterInterface : public QDialog
{
    Q_OBJECT // макрос для любых классов, включающих сигналы и слоты

public:
    ConverterInterface(QWidget *parent = 0);

signals:
    void findNext(const QString &str, Qt::CaseSensitivity cs);

private slots:
    void okClicked();
    void enableOkButton(const QString &text);

private:
    QLabel *label;
    QLabel *process;
    QComboBox *box;
    QStringList stringList;
    QLineEdit *lineEdit;
    QPushButton *okButton;
    QPushButton *closeButton;
    QString *text;
};

#endif // CONVERTERINTERFACE_H
