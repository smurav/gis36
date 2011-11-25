#include <QtGui>
#include <QtXmlPatterns/QXmlQuery>
#include <qlayout.h>
#include "converterinterface.h"
#include <iostream>

ConverterInterface::ConverterInterface(QWidget *parent)
    : QDialog(parent){

    labelbox = new QLabel(tr("Choose file: "));
    box = new QComboBox(false);
    labelbox->setBuddy(box);

    stringList << "examplemap.xml" << "mapch.xml";
    box->addItems(stringList);
    box->setEditable(true);

    QLabel *labelPath = new QLabel (tr("The rezalts of parsing"));

    okButton = new QPushButton(tr("Do it!!!"));
    okButton->setDefault(true);
    okButton->setEnabled(true);

    process = new QTextEdit();
    process->setReadOnly(true);
    lib = new ConverterLibrary();
    connect(okButton, SIGNAL(clicked()), this, SLOT(OnOkButton()));
    connect(box, SIGNAL(activated(int)), process, SLOT(clear()));

    closeButton = new QPushButton(tr("Close"));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout *upperLayout = new QHBoxLayout;
    upperLayout->addWidget(labelbox);
    upperLayout->addWidget(box);


    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(okButton);

    QVBoxLayout *middleLayout = new QVBoxLayout;
    middleLayout->addLayout(upperLayout);
    middleLayout->addLayout(topLayout);
    middleLayout->addWidget(labelPath);
    middleLayout->addWidget(process);
    middleLayout->addWidget(closeButton);


    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(middleLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Converter"));
    setFixedSize(QSize(300, 500));
}

void ConverterInterface::OnOkButton(){

    QString str = "";

    if(lib)
    {
        str = QString::QString(lib->Parser(box->currentText()));
    }else
        str = "The connection with ConverterLibrary is not established"//выдать ошибку
        ;

    QTextCursor cursor = process->textCursor();
    cursor.movePosition(QTextCursor::End);
    cursor.insertText(str);
    process->setText(str);
}




