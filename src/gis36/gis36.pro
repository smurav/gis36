#-------------------------------------------------
#
# Project created by QtCreator 2011-09-28T23:26:13
#
#-------------------------------------------------

QT       += core gui xml

TARGET = gis36
TEMPLATE = app
 INCLUDEPATH  += ../includes

SOURCES += main.cpp\
    main_window.cpp \
    settings_parser.cpp \
    shell_interface.cpp \
    plugin_manager.cpp

HEADERS  += \
    main_window.h \
    settings_parser.h \
    ../includes/shell_interface.h \
    ../includes/plugin_interface.h \
    shell_interface.h \
    plugin_interface.h \
    plugin_manager.h

FORMS    += mainwindow.ui \
    plugin_manager.ui

























