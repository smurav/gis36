/********************************************************************************
** Form generated from reading UI file 'plugin_manager.ui'
**
** Created: Tue 25. Oct 21:33:27 2011
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLUGIN_MANAGER_H
#define UI_PLUGIN_MANAGER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PluginManager
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QListWidget *list_plugins;
    QVBoxLayout *verticalLayout_2;
    QPushButton *add_plugin;
    QPushButton *remove_plugin;
    QPushButton *turn_on_plugin;
    QPushButton *turn_off_plugin;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *PluginManager)
    {
        if (PluginManager->objectName().isEmpty())
            PluginManager->setObjectName(QString::fromUtf8("PluginManager"));
        PluginManager->resize(400, 300);
        layoutWidget = new QWidget(PluginManager);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(12, 13, 381, 281));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        list_plugins = new QListWidget(layoutWidget);
        list_plugins->setObjectName(QString::fromUtf8("list_plugins"));

        horizontalLayout->addWidget(list_plugins);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        add_plugin = new QPushButton(layoutWidget);
        add_plugin->setObjectName(QString::fromUtf8("add_plugin"));
        add_plugin->setEnabled(false);

        verticalLayout_2->addWidget(add_plugin);

        remove_plugin = new QPushButton(layoutWidget);
        remove_plugin->setObjectName(QString::fromUtf8("remove_plugin"));
        remove_plugin->setEnabled(true);

        verticalLayout_2->addWidget(remove_plugin);

        turn_on_plugin = new QPushButton(layoutWidget);
        turn_on_plugin->setObjectName(QString::fromUtf8("turn_on_plugin"));
        turn_on_plugin->setEnabled(true);

        verticalLayout_2->addWidget(turn_on_plugin);

        turn_off_plugin = new QPushButton(layoutWidget);
        turn_off_plugin->setObjectName(QString::fromUtf8("turn_off_plugin"));
        turn_off_plugin->setEnabled(true);

        verticalLayout_2->addWidget(turn_off_plugin);

        verticalSpacer = new QSpacerItem(20, 131, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(PluginManager);
        QObject::connect(add_plugin, SIGNAL(clicked()), PluginManager, SLOT(addNewPlugin()));
        QObject::connect(remove_plugin, SIGNAL(clicked()), PluginManager, SLOT(removePlugin()));
        QObject::connect(turn_on_plugin, SIGNAL(clicked()), PluginManager, SLOT(turnOnPlugin()));
        QObject::connect(turn_off_plugin, SIGNAL(clicked()), PluginManager, SLOT(turnOffPlugin()));

        QMetaObject::connectSlotsByName(PluginManager);
    } // setupUi

    void retranslateUi(QDialog *PluginManager)
    {
        PluginManager->setWindowTitle(QApplication::translate("PluginManager", "Plugin Manager", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("PluginManager", "\320\241\320\277\320\270\321\201\320\276\320\272 \320\277\320\273\320\260\320\263\320\270\320\275\320\276\320\262", 0, QApplication::UnicodeUTF8));
        add_plugin->setText(QApplication::translate("PluginManager", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        remove_plugin->setText(QApplication::translate("PluginManager", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        turn_on_plugin->setText(QApplication::translate("PluginManager", "\320\222\320\272\320\273\321\216\321\207\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        turn_off_plugin->setText(QApplication::translate("PluginManager", "\320\236\321\202\320\272\320\273\321\216\321\207\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PluginManager: public Ui_PluginManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLUGIN_MANAGER_H
