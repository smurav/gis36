#include "dialog.h"
#include "ui_dialog.h"
#include "QCursor"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{

    ui->setupUi(this);    
    this->setMouseTracking(false);

    my_view = new CMyGraphicsView(this);
    my_view->setGeometry(30,40,331,241);//место расположения и параметры сцены
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    my_view->scale(0.9,0.9);//уменьшение масштаба
}

void Dialog::on_pushButton_2_clicked()
{
    my_view->scale(1.1,1.1);//увеличение масштаба
}

