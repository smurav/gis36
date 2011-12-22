#include "mainwindow.h"
#include "ui_mainwindow.h"

#define LAYERS_NAME_COLUMN 0
#define LAYERS_XPATH_COLUMN 1
#define LAYERS_OBJECTS_COUNT_COLUMN 2

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&scene_);
    xml_doc_ptr_ = 0;
}

MainWindow::~MainWindow()
{
  delete ui;
  FreeXMLDoc();
}

void MainWindow::FreeXMLDoc() {
  if (xml_doc_ptr_) {
    xmlFreeDoc(xml_doc_ptr_);
    xml_doc_ptr_ = 0;
  }
}

void MainWindow::on_actionOpenOSM_triggered()
{
  QString file_name = QFileDialog::getOpenFileName(this,
                                                  tr("Выберите файл OSM"),
                                                  "../osm/",
                                                  tr("Файлы OpenStreetMap (*.osm)"));

  if (0 == file_name.length())
    return;

  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
  bool opening_result = OpenOSM(file_name);
  QApplication::restoreOverrideCursor();

  if (false == opening_result) {

    QMessageBox::critical(this, tr("Открытие файла"),
                          tr("Ошибка открытия файла %1").arg(file_name),
                          QMessageBox::Ok);
  }
}

bool MainWindow::OpenOSM(const QString &file_name) {
  scene_.clear();
  FreeXMLDoc();

  xmlParserCtxtPtr xml_parser_ctx_ptr = xmlNewParserCtxt();
  if (0 == xml_parser_ctx_ptr)
    return false;

  // XML документ libxml2
  xml_doc_ptr_ = xmlCtxtReadFile(xml_parser_ctx_ptr,
                                 file_name.toLocal8Bit().data(),
                                 0,
                                 XML_PARSE_NOBLANKS);
  xmlFreeParserCtxt(xml_parser_ctx_ptr);
  xml_parser_ctx_ptr = 0;
  if (0 == xml_doc_ptr_)
    return false;

  xmlXPathContextPtr xpath_context_ptr = xmlXPathNewContext(xml_doc_ptr_);
  if (0 == xpath_context_ptr)
    return false;

  // Определеяем границы листа
  xmlXPathObjectPtr xpath_bounds_query = xmlXPathEvalExpression(
                                           BAD_CAST "//bounds",
                                           xpath_context_ptr);
  if ((0 == xpath_bounds_query) || (1 != xpath_bounds_query->nodesetval->nodeNr))
    return false;

  xmlNodePtr bounds = xpath_bounds_query->nodesetval->nodeTab[0];
  float minlat = QString::fromUtf8((char *)xmlGetProp(bounds, BAD_CAST "minlat")).toFloat();
  float minlon = QString::fromUtf8((char *)xmlGetProp(bounds, BAD_CAST "minlon")).toFloat();
  float maxlat = QString::fromUtf8((char *)xmlGetProp(bounds, BAD_CAST "maxlat")).toFloat();
  float maxlon = QString::fromUtf8((char *)xmlGetProp(bounds, BAD_CAST "maxlon")).toFloat();

  // Настраиваем область видимости
  ui->graphicsView->resetTransform();
  ui->graphicsView->centerOn((maxlon - minlon) * 0.5, (maxlat - minlat) * 0.5);
  ui->graphicsView->setResizeAnchor(QGraphicsView::AnchorViewCenter);

  qreal sx = 8000;
  qreal sy = 10000;

  ui->graphicsView->scale(sx, -sy);

  // Перебираем слои
  int layers_count = ui->treeWidget->topLevelItemCount();
  for (int layer_index = 0; layer_index < layers_count; layer_index++){
    QTreeWidgetItem *layer_item_ptr = ui->treeWidget->topLevelItem(layer_index);
    QString ways_count("0");
    layer_item_ptr->setText(LAYERS_OBJECTS_COUNT_COLUMN, ways_count);

    QString way_query = layer_item_ptr->data(LAYERS_XPATH_COLUMN, 0).toString();

    xmlXPathObjectPtr xpath_way_query = xmlXPathEvalExpression(
      BAD_CAST way_query.toUtf8().data(), xpath_context_ptr);

    if (0 == xpath_way_query)
      continue;

    xmlNodeSetPtr way_set = xpath_way_query->nodesetval;
    if ((0 == way_set) || (0 == way_set->nodeNr))
      continue;

    QPen pen(Qt::darkGray);
    QBrush brush(Qt::lightGray);
    QList<QGraphicsItem*> layer;

    ways_count.setNum(way_set->nodeNr);
    layer_item_ptr->setText(LAYERS_OBJECTS_COUNT_COLUMN, ways_count);

    for (int i = 0; i < way_set->nodeNr; i++){
      xmlNodePtr way = way_set->nodeTab[i];
      if (0 == way)
        continue;

      // Создаем массив точек
      QPolygonF polygon;

      QString way_id = QString::fromUtf8((char *)xmlGetProp(way, BAD_CAST "id"));
      QString nd_query = QString("//way[@id='%1']/nd").arg(way_id);

      // Перебираем ссылки на точки
      xmlXPathObjectPtr xpath_nd_query = xmlXPathEvalExpression(
                                           BAD_CAST nd_query.toUtf8().data(),
                                           xpath_context_ptr);
      if ((0 == xpath_nd_query) || (0 == xpath_nd_query->nodesetval))
        continue;

      for (int nd_index = 0;
           nd_index < xpath_nd_query->nodesetval->nodeNr;
           nd_index++){
        QString ref = QString::fromUtf8((char *)xmlGetProp(xpath_nd_query->nodesetval->nodeTab[nd_index], BAD_CAST "ref"));

        // Ищем точку
        QString node_query = QString("//node[@id='%1']").arg(ref);
        xmlXPathObjectPtr xpath_node_query = xmlXPathEvalExpression(
                                             BAD_CAST node_query.toUtf8().data(),
                                             xpath_context_ptr);
        if ((0 == xpath_node_query) || (1 != xpath_node_query->nodesetval->nodeNr))
          continue;

        xmlNodePtr node = xpath_node_query->nodesetval->nodeTab[0];
        QString latitude = QString::fromUtf8((char *)xmlGetProp(node, BAD_CAST "lat"));
        QString longitude = QString::fromUtf8((char *)xmlGetProp(node, BAD_CAST "lon"));
        polygon.append(QPointF(longitude.toFloat(), latitude.toFloat()));

        xmlXPathFreeNodeSet(xpath_node_query->nodesetval);
        xmlFree(xpath_node_query);
      }

      // Создаем графический объект
      QGraphicsPolygonItem *polygon_item = new QGraphicsPolygonItem(polygon);
      polygon_item->setPen(pen);
      polygon_item->setBrush(brush);
      layer.append(polygon_item);

      xmlXPathFreeNodeSet(xpath_nd_query->nodesetval);
      xmlFree(xpath_nd_query);
    }

    QGraphicsItemGroup* layer_group = scene_.createItemGroup(layer);

    xmlXPathFreeNodeSet(way_set);
    xmlFree(xpath_way_query);
  }

  xmlXPathFreeContext(xpath_context_ptr);
  xpath_context_ptr = 0;

  return true;
}

void MainWindow::on_action_triggered()
{
  ui->graphicsView->scale(2, 2);
}

void MainWindow::on_actionZoomOut_triggered()
{
  ui->graphicsView->scale(0.5, 0.5);
}
