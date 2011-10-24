#-------------------------------------------------
#
# Project created by QtCreator 2011-10-20T09:10:54
#
#-------------------------------------------------

QT       += sql

TARGET = layer_manager
TEMPLATE = lib

DEFINES += LAYER_MANAGER_LIBRARY

SOURCES += \
    layer_manager_shower.cpp \
    layer_form.cpp

HEADERS += \
    layer_manager_shower.h \
    layer_form.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE4E87D59
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = layer_manager.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}







