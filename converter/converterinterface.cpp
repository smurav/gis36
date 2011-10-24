#include <QtGui>
#include <QtXmlPatterns/QXmlQuery>
#include <qlayout.h>
#include "converterinterface.h"

ConverterInterface::ConverterInterface(QWidget *parent)
    : QDialog(parent){

    label = new QLabel(tr("Choose file: "));
    box = new QComboBox(false);
    label->setBuddy(box);

    stringList << "map.xml" << "b1.xml" << "c1.xml" << "a2.xml"; //список имен xml документов
    box->addItems(stringList);
    //box->setEditable(true); //возможность редактировать имеющийся список

    okButton = new QPushButton(tr("Do it!!!"));
    okButton->setDefault(true); //кнопка по умолчанию, подсветка
    okButton->setEnabled(true);

    QString prs = QString::QString(box->currentText());
    Library *lib = new Library();
    QString str = QString::QString(lib->Parser(prs));
    process = new QLabel(str);
    process->setVisible(false);
    process->setWordWrap(true);

    closeButton = new QPushButton(tr("Close"));

    connect(box, SIGNAL(textChanged(const QString &)), this, SLOT(enableOkButton(const QString &)));
    connect(okButton, SIGNAL(clicked()), process, SLOT(show())); //ок нажата, парсим
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(label);
    topLayout->addWidget(box);

    QVBoxLayout *middleLayout = new QVBoxLayout;
    middleLayout->addLayout(topLayout);
    middleLayout->addWidget(okButton);
    middleLayout->addWidget(process);
    middleLayout->addSpacing(100);
    middleLayout->addWidget(closeButton);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(middleLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Converter"));
}

void ConverterInterface::okClicked(){

}

void ConverterInterface::enableOkButton(const QString &text){
    //okButton->setVisible(true);
}


