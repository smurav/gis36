/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed Nov 23 19:35:42 2011
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QSplitter>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QTreeWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpenOSM;
    QAction *action;
    QAction *actionZoomOut;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QSplitter *splitter;
    QTreeWidget *treeWidget;
    QGraphicsView *graphicsView;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(850, 517);
        MainWindow->setWindowTitle(QString::fromUtf8("OpenStreetMap viewer"));
        MainWindow->setIconSize(QSize(16, 16));
        actionOpenOSM = new QAction(MainWindow);
        actionOpenOSM->setObjectName(QString::fromUtf8("actionOpenOSM"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpenOSM->setIcon(icon);
        action = new QAction(MainWindow);
        action->setObjectName(QString::fromUtf8("action"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/zoomin.png"), QSize(), QIcon::Normal, QIcon::Off);
        action->setIcon(icon1);
        actionZoomOut = new QAction(MainWindow);
        actionZoomOut->setObjectName(QString::fromUtf8("actionZoomOut"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/zoomout.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoomOut->setIcon(icon2);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(3);
        gridLayout->setContentsMargins(3, 3, 3, 3);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        treeWidget = new QTreeWidget(splitter);
        new QTreeWidgetItem(treeWidget);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setFrameShadow(QFrame::Sunken);
        treeWidget->setSelectionMode(QAbstractItemView::ContiguousSelection);
        splitter->addWidget(treeWidget);
        graphicsView = new QGraphicsView(splitter);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        splitter->addWidget(graphicsView);

        gridLayout->addWidget(splitter, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 850, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        mainToolBar->addAction(actionOpenOSM);
        mainToolBar->addSeparator();
        mainToolBar->addAction(action);
        mainToolBar->addAction(actionZoomOut);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        actionOpenOSM->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionOpenOSM->setToolTip(QApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 OSM \321\204\320\260\320\271\320\273", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        action->setText(QApplication::translate("MainWindow", "\320\243\320\262\320\265\320\273\320\270\321\207\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        actionZoomOut->setText(QApplication::translate("MainWindow", "\320\243\320\274\320\265\320\275\321\214\321\210\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(2, QApplication::translate("MainWindow", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(1, QApplication::translate("MainWindow", "\320\227\320\260\320\277\321\200\320\276\321\201", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "\320\241\320\273\320\276\320\271", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = treeWidget->isSortingEnabled();
        treeWidget->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget->topLevelItem(0);
        ___qtreewidgetitem1->setText(1, QApplication::translate("MainWindow", "//way[tag[(@k=\"building\")and(@v=\"yes\")]]", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem1->setText(0, QApplication::translate("MainWindow", "\320\227\320\264\320\260\320\275\320\270\321\217", 0, QApplication::UnicodeUTF8));
        treeWidget->setSortingEnabled(__sortingEnabled);

        Q_UNUSED(MainWindow);
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
