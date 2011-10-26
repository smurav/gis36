#ifndef SEARCH_BY_REGION_WINDOW_H
#define SEARCH_BY_REGION_WINDOW_H

#include <QtGui/QDialog>

class QLabel;
class QLineEdit;

class SearchByRegionWindow : public QDialog
{
    Q_OBJECT

public:
    SearchByRegionWindow(QWidget *parent = 0);

private:
    QLabel *label;
    QLineEdit *lineEdit;

};

#endif // SEARCH_BY_REGION_WINDOW_H
