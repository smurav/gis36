#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QtGui>
#include "libxml/xmlreader.h"
#include "libxml/xpath.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  bool OpenOSM(const QString &fileName);

private slots:
  void on_actionOpenOSM_triggered();

  void on_action_triggered();

  void on_actionZoomOut_triggered();

private:
  void FreeXMLDoc();

private:
    Ui::MainWindow *ui;
    QGraphicsScene  scene_;
    xmlDocPtr xml_doc_ptr_;
};

#endif // MAINWINDOW_H
