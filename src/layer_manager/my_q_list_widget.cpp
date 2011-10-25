#include <iostream>
#include <QList>
#include <QMessageBox>
#include "my_q_list_widget.h"


MyQListWidget::MyQListWidget(QWidget * parent ) :QListWidget(parent){

}

void MyQListWidget::dropEvent(QDropEvent *event) {
  QListWidget::dropEvent(event);//сначала метод базового класса
  //затем создаем список нынешний расположений чекбоксов
  QList<int> list_with_cur_order = this->currentCheckBoxOrder();

  //далее будет работа с БД . пока я для проверки их просто на экран выводил
  //на QMessageBox'e
  QString str_for_message_box="Current chexbox location \n";

  QList<int>::iterator i;
   for (i=list_with_cur_order.begin();
        i!=list_with_cur_order.end();++i){
     str_for_message_box.append(QString::number(*i));
     str_for_message_box.append("  ");
  }
   QMessageBox * box = new QMessageBox();
   box->setText(str_for_message_box);
   box->exec();
}



QList<int> MyQListWidget::currentCheckBoxOrder(){
  QList<int> cur_checkbox_order;
  for(int i=0;i<this->count();++i) {
    QListWidgetItem* item = this->item(i);
    int res;//результат, который добавим в список

    //при создании записи в MyQListWidget я использовал строчку
    //q_list_widget_item->setData(Qt::UserRole,QString::number(i));
    //стало быть у каждой записи типа Qt::UserRole есть свой номер в строковом
    //представлении. следующими двумя строками я его нахожу
    QVariant qvar = item->data(Qt::UserRole);
    int n = qvar.toInt();

    switch (n) {
    case 0: {res = n; break;}
    case 1: {res = n; break;}
    case 2: {res = n; break;}
    case 3: {res = n; break;}
    case 4: {res = n; break;}
    case 5: {res = n; break;}
    case 6: {res = n; break;}
    case 7: {res = n; break;}
    case 8: {res = n; break;}
    case 9: {res = n; break;}
    }
    cur_checkbox_order.append(n);//добавили в конец списка
  }
  return cur_checkbox_order;
}




