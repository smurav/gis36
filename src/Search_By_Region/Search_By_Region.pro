#-------------------------------------------------
#
# Project created by QtCreator 2011-10-27T02:41:48
#
#-------------------------------------------------

QT       += core gui

TARGET = Search_By_Region
TEMPLATE = lib

DEFINES += SEARCH_BY_REGION_LIBRARY

SOURCES += search_by_region.cpp \
    search_by_region_window.cpp

HEADERS += search_by_region.h\
        Search_By_Region_global.h \
    ../includes/plugin_interface.h \
    search_by_region_window.h




 TARGET        = $$qtLibraryTarget(search_by_region)

 DESTDIR       =  ./output

 # install
 target.path = ./output
 sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS PluginHello.pro
 sources.path = ./
 INSTALLS += target sources



