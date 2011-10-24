#ifndef layer_form_H
#define layer_form_H
#include <QDialog>
class QListWidget;
class QTableWidget;
class QTableWidgetItem;
class QListWidgetItem;
class layer_form :public QDialog
{
  Q_OBJECT
  public:
    layer_form(QWidget *parent = 0);
  private slots:
    void stateOfLayersChanged(QListWidgetItem * n=NULL);
    void button_Select_all_clicked();
    void button_Deselect_all_clicked();
    void button_Set_lower_clicked();
    void button_Set_upper_clicked();
  private:
    QListWidget *list_widget;
    int num_gis_layers;
    QTableWidget * q_table_widget;
    QTableWidgetItem * q_table_widget_item_name;
    QTableWidgetItem * q_table_widget_item_state;
    QPushButton * button_select_all;
    QPushButton * button_deselect_all;
    QPushButton * button_set_upper;
    QPushButton * button_set_lower;
    void layoutDesigner();
    void connectionsEstablisher();
};
#endif // layer_form_H

