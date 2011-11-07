#include <QtGui>
#include <QtXmlPatterns/QXmlQuery>
#include <qlayout.h>
#include "converterinterface.h"

ConverterInterface::ConverterInterface(QWidget *parent)
    : QDialog(parent){

    labelbox = new QLabel(tr("Choose file: "));
    box = new QComboBox(false);
    labelbox->setBuddy(box);

    stringList << "examplemap.xml" << "map.xml" << "c1.xml" << "a2.xml"; //список имен xml документов
    box->addItems(stringList);
    box->setEditable(true); //возможность редактировать имеющийся список

    QLabel *labelpath = new QLabel (tr("XPath-query: "));
    path = new QLineEdit(tr("osm/way[*/@k='building']/nd[@ref]"));
    labelpath->setBuddy(path);
    path->setEnabled(true);

    okButton = new QPushButton(tr("Do it!!!"));
    okButton->setDefault(true); //кнопка по умолчанию, подсветка
    okButton->setEnabled(true);

    process = new QTextEdit();
    Library *lib = new Library();
    QString str = QString::QString(lib->Parser(box->currentText(), path->text()));
    QTextCursor cursor = process->textCursor();
    cursor.movePosition(QTextCursor::End);
    cursor.insertText(str);
    process->setReadOnly(true);

    closeButton = new QPushButton(tr("Close"));

    connect(box, SIGNAL(activated(int)), process, SLOT(clear()));
    connect(path, SIGNAL(textChanged(QString)), process, SLOT(clear()));

    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout *upperLayout = new QHBoxLayout;
    upperLayout->addWidget(labelbox);
    upperLayout->addWidget(box);


    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(labelpath);
    topLayout->addWidget(path);

    QVBoxLayout *middleLayout = new QVBoxLayout;
    middleLayout->addLayout(upperLayout);
    middleLayout->addLayout(topLayout);
    middleLayout->addWidget(okButton);
    middleLayout->addWidget(process);
    middleLayout->addWidget(closeButton);


    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(middleLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Converter"));
    setFixedSize(QSize(300, 500));
}

bool ConverterInterface::error(){
    return true;
}


void ConverterInterface::setQuery(){

}

void ConverterInterface::empty(){

}

void ConverterInterface::enableOkButton(const QString &text){
    okButton->setEnabled(!text.isEmpty());
}


