#-------------------------------------------------
#
# Project created by QtCreator 2011-10-17T20:55:07
#
#-------------------------------------------------

QT       += gui core

#вот сюда как правильно сделать
LIBS += -Lbin -lMyLibrary1
INCLUDEPATH += ./includes
TARGET = ConverterInterface
TEMPLATE = app


SOURCES += \
    converterinterface.cpp \
    main.cpp

HEADERS  += \
    converterinterface.h

FORMS    +=

OUTPUT      = ./
TEMP        = $${OUTPUT}/temp/
debug {
  DEFINES     += _DEBUG
  DESTDIR     = $${OUTPUT}/bin
  OBJECTS_DIR = $${TEMP}/debug
} else {
  DESTDIR     = $${OUTPUT}/bin
  OBJECTS_DIR = $${TEMP}/release
}











