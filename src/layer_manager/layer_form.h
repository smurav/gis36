#ifndef layer_form_H
#define layer_form_H
#include <QDialog>
#include "my_q_list_widget.h"

class QListWidget;
class QTableWidget;
class QTableWidgetItem;
class QListWidgetItem;
class LayerForm :public QDialog
{
  Q_OBJECT
  public:
    LayerForm(QWidget *parent = 0);
  private slots:
    void stateOfLayersChanged(QListWidgetItem * n=NULL); //состояние видимости изменилось
    void button_Select_all_clicked(); //все чекбоксы помечены галочкой
    void button_Deselect_all_clicked();

  private:
    MyQListWidget *list_widget; //виджет с чекбоксами
    int num_gis_layers; //количество слоев в нашей карте
    QTableWidget * q_table_widget; //табличка видимости, порядка и имен слоев

    //далее следуют два указателя (будущих массива)
    QTableWidgetItem * q_table_widget_item_name; //с названиями слоев
    QTableWidgetItem * q_table_widget_item_state;//с состояниями видимости
    QPushButton * button_select_all;
    QPushButton * button_deselect_all;

    void layoutDesigner(); //метод размещающий виджеты на форме
    void connectionsEstablisher(); //метод в котором прописаны все коннекты
};
#endif // layer_form_H

