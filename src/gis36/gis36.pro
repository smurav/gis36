#-------------------------------------------------
#
# Project created by QtCreator 2011-09-26T03:04:34
#
#-------------------------------------------------

QT          += core gui

TARGET      = gis36
TEMPLATE    = app

# Относительный путь рабочего каталога репозитория
OUTPUT      = ../..

# Относительный путь каталога для хранения временных файлов
TEMP        = $${OUTPUT}/temp/gis36

# Настройки путей для сборки отладочных и релизных версий
debug {
  DEFINES     += _DEBUG
  DESTDIR     = $${OUTPUT}/debug
  OBJECTS_DIR = $${TEMP}/debug
} else {
  DESTDIR     = $${OUTPUT}/release
  OBJECTS_DIR = $${TEMP}/release
}

# Путь для сохранения временных файлов Qt
MOC_DIR     = $${OBJECTS_DIR}

# Дополнительные пути поиска заголовчных фалов
INCLUDEPATH = ../include

SOURCES     += main.cpp\
               mainwindow.cpp

HEADERS     += mainwindow.h

FORMS       += mainwindow.ui
