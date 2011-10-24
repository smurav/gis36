#---------------------------------------------------
#
# Пример проекта, создающего подключаемую библиотеку
#
# Project created by QtCreator 2011-09-25T13:42:06
#
#---------------------------------------------------
QT       += gui
QT       += core
QT       += xmlpatterns

TARGET = MyLibrary
TEMPLATE = lib
VERSION = 1.0.0
SOURCES += library.cpp

HEADERS += ../includes/library.h

DEFINES     += GIS36_LIBRARY_EXPORTS

INCLUDEPATH = ../includes

OUTPUT      = ../
TEMP        = $${OUTPUT}/temp/
debug {
  DEFINES     += _DEBUG
  DESTDIR     = $${OUTPUT}/bin
  OBJECTS_DIR = $${TEMP}/debug
} else {
  DESTDIR     = $${OUTPUT}/bin
  OBJECTS_DIR = $${TEMP}/release
}

