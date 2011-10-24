#include <QtGui>
#include "layer_form.h"
layer_form::layer_form(QWidget *parent):QDialog(parent){
  num_gis_layers = 10;
  //инициализация кнопок
  button_select_all = new QPushButton(tr("Select All"));;
  button_deselect_all = new QPushButton(tr("Deselect All"));
  button_set_upper = new QPushButton(tr("Set Upper//temporary not available "));
  button_set_lower = new QPushButton(tr("Set Lower//temporary not available"));
  //инициализация таблицы и двух табличных айтемов
  int num_columns = 2;
  int num_raws = num_gis_layers;
  q_table_widget = new QTableWidget(num_raws,num_columns,this);
  q_table_widget_item_name = new QTableWidgetItem[num_gis_layers];
  q_table_widget_item_state = new QTableWidgetItem[num_gis_layers];
  //инициализация списка чекбоксов
  list_widget = new QListWidget();
  QStringList lst_layer_names;
  lst_layer_names<<"layer 1"<<"layer 2"<<"layer 3"<<"layer 4"
                 <<"layer 5"<<"layer 6"<<"layer 7"<<"layer 8"
                 <<"layer 9"<<"layer 10";
  for (int i=0;i<num_raws;++i) {
    //добавление элементов в таблицу
    q_table_widget_item_name[i] =*(new QTableWidgetItem(
                      lst_layer_names.at(i).toLocal8Bit().constData()));
    q_table_widget_item_state[i]=*(new QTableWidgetItem("Show"));
    q_table_widget_item_state[i].setBackgroundColor(QColor(0,255,0));
    q_table_widget->setItem(i,0,&q_table_widget_item_name[i]);
    q_table_widget->setItem(i,1,&q_table_widget_item_state[i]);
    //добавление элементов в список
    QListWidgetItem * q_list_widget_item =new QListWidgetItem();
    QString layer_name = "Show/Hide  ";
    layer_name.append(lst_layer_names.at(i).toLocal8Bit().constData());
    q_list_widget_item->setData(Qt::DisplayRole ,layer_name);
    q_list_widget_item->setData(Qt::CheckStateRole , "Description");
    q_list_widget_item->setCheckState(Qt::Checked);   //установка начального нзачения
    list_widget->addItem(q_list_widget_item);
  }
  this->layoutDesigner();//виджеты расположатся на форме
  this->connectionsEstablisher();//определены коннекты
  QStringList lst2;
  lst2<<"Layer Name"<<"Enablety State";
  q_table_widget->setHorizontalHeaderLabels(lst2);
    setWindowTitle(tr("Layer Manager"));
  setMinimumHeight(490);
}
void layer_form::stateOfLayersChanged(QListWidgetItem *n) {
  for (int i=0;i<num_gis_layers;++i) {
    if (list_widget->item(i)->checkState()==Qt::Checked) {
      q_table_widget_item_state[i].setText("Show");
      q_table_widget_item_state[i].setBackgroundColor(QColor(0,255,0));
    }else {
      q_table_widget_item_state[i].setText("Hide");
      q_table_widget_item_state[i].setBackgroundColor(QColor(255,0,0));
    }
  }
}
void layer_form::button_Select_all_clicked() {
  for (int i=0;i<num_gis_layers;++i) {
    list_widget->item(i)->setCheckState(Qt::Checked);
    emit stateOfLayersChanged(list_widget->item(i));
  }
}
void layer_form::button_Deselect_all_clicked() {
  for (int i=0;i<num_gis_layers;++i) {
    list_widget->item(i)->setCheckState(Qt::Unchecked);
    emit stateOfLayersChanged(list_widget->item(i));
  }
}
void layer_form::button_Set_upper_clicked() {
  //QListWidgetItem *item = list_widget->currentItem();
  int current_row = list_widget->row(list_widget->currentItem());
  QListWidgetItem *item = list_widget->item(current_row-1);
  list_widget->insertItem(current_row+1,item);
}
void layer_form::button_Set_lower_clicked() {
}
void layer_form::layoutDesigner() {
  QVBoxLayout *layout_v1 = new QVBoxLayout;
  QVBoxLayout *layout_v2= new QVBoxLayout;
  layout_v1->addWidget(q_table_widget);
  layout_v1->addWidget(button_set_upper);
  layout_v1->addWidget(button_set_lower);
  layout_v2->addStretch();
  layout_v2->addWidget(list_widget);
  layout_v2->addStretch();
  layout_v2->addWidget(button_select_all);
  layout_v2->addWidget(button_deselect_all);
  QHBoxLayout *premain_layout = new QHBoxLayout;
  premain_layout->addLayout(layout_v1);
  premain_layout->addLayout(layout_v2);
  QVBoxLayout *main_layout = new QVBoxLayout;
  main_layout->addLayout(premain_layout);
  setLayout(main_layout);
}
void layer_form::connectionsEstablisher(){
  QObject::connect(button_select_all, SIGNAL (clicked()),
               this, SLOT (button_Select_all_clicked()));
  QObject::connect(button_deselect_all, SIGNAL (clicked()),
               this, SLOT (button_Deselect_all_clicked()));
  QObject::connect(button_set_upper, SIGNAL (clicked()),
               this, SLOT (button_Set_upper_clicked()));
  QObject::connect(button_set_lower, SIGNAL (clicked()),
               this, SLOT (button_Set_lower_clicked()));
  QObject::connect(list_widget, SIGNAL(itemChanged(QListWidgetItem*)),
               this, SLOT(stateOfLayersChanged(QListWidgetItem*)));
}

