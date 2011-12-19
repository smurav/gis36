#ifndef CONVERTERINTERFACE_H
#define CONVERTERINTERFACE_H
#include <QWidget>
#include <QGraphicsView>
#include "ConverterLibrary.h"


class QLabel;
class QLineEdit;
class QPushButton;
class QComboBox;
class QString;
class QStringList;
class QTextEdit;

class ConverterInterface : public QWidget
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
    void OnViewButton();

private:
    QLabel *labelbox;
    QLineEdit *lineEdit;
    QLineEdit *path;
    QTextEdit *process;
    QComboBox *box;
    QStringList stringList;
    QPushButton *okButton;
    QPushButton *viewButton;
    QPushButton *findButton;
    QPushButton *closeButton;
    QString *text;
    QString *str;
    ConverterLibrary *lib;
    ConverterLibrary *paintMap;
    //QGraphicsView* my_view;

};

#endif // CONVERTERINTERFACE_H
