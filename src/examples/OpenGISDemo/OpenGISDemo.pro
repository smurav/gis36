#---------------------------------------------------
#
# Пример работы с OpenGIS
#
#---------------------------------------------------

QT       += core gui
TARGET   = osmviewer
TEMPLATE = app

# Дополнительные пути поиска заголовчных фалов
INCLUDEPATH = ../include

# Относительный путь рабочего каталога репозитория
OUTPUT = ../../..

# Относительный путь каталога для хранения временных файлов
TEMP = $${OUTPUT}/temp/examples/osmviewer

# Настройки путей для сборки отладочных и релизных версий
debug {
  DEFINES += _DEBUG
  DESTDIR = $${OUTPUT}/debug
  OBJECTS_DIR = $${TEMP}/debug
} else {
  DESTDIR = $${OUTPUT}/release
  OBJECTS_DIR = $${TEMP}/release
}

win32 {
} else {
  INCLUDEPATH += /usr/include/libxml2\
                 /usr/include
  LIBS +=	-lxml2
}

RCC_DIR = ./res

RESOURCES = ./res/resource.qrc

# Путь для сохранения временных файлов Qt
MOC_DIR = $${OBJECTS_DIR}

SOURCES += main.cpp\
           mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui


#######################################################################
## Systemprom files 0.1
#######################################################################

#TEMPLATE 		= lib
#INCLUDEPATH 	=	../include\
#					../../shell/include \
#					../../common/iconv/include \
#					../../common/libxml2/include \
#					../../common/pg/include \
#					../../common/include
#OUTPUT			= ../../..
#TEMP			= ../../../temp/src/gis/OpenGISDemo
#CONFIG      	+= plugin
#QT				+= opengl

#RCC_DIR		= ./res
#RESOURCES	= ./res/resource.qrc

#debug {
#	DEFINES		+= _DEBUG
#	DESTDIR 	= $${OUTPUT}/debug
#	OBJECTS_DIR	= $${TEMP}/debug
#} else {
#	DESTDIR 	= $${OUTPUT}/release
#	OBJECTS_DIR	= $${TEMP}/release
#}

#win32 {
#	LIBS		+=	$${DESTDIR}/SpmXml.lib
#	LIBS 		+=	../../common/pg/lib/libpq.lib
#} else {
#	LIBS		+=	-lspmxml
#}

#MOC_DIR		= $${OBJECTS_DIR}

#PRECOMPILED_HEADER  = stdspm.h
 
#HEADERS += GLWidget.h \
# 	stdspm.h \
#			OpenGISDemo.h
#SOURCES	+= GLWidget.cpp \
#	OpenGISDemo.cpp
