QT       += gui
QT       += core
QT       += xmlpatterns
QT       += xml
QT       += sql

TARGET = ConverterLibrary
TEMPLATE = lib
VERSION = 1.0.0

HEADERS += ../includes/ConverterLibrary.h

SOURCES += ConverterLibrary.cpp

DEFINES     += GIS36_LIBRARY_EXPORTS

INCLUDEPATH = \
            ../includes
#            C:\PostgreSQL\9.1\include

#LIBS    *= -lpq

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

