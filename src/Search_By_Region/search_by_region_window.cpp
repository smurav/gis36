#include "search_by_region.h"
#include "search_by_region_window.h"

SearchByRegionWindow::SearchByRegionWindow(QWidget *parent)
    : QDialog(parent)
{
    label = new QLabel(tr("Enter radius: "));
    lineEdit = new QLineEdit;

    QHBoxLayout *MyLayOut = new QHBoxLayout;
    MyLayOut->addWidget(label);
    MyLayOut->addWidget(lineEdit);
    setLayout(MyLayOut);

    setWindowTitle(tr("Cafe"));
}

