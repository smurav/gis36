 TEMPLATE      = lib
 CONFIG       += plugin
 INCLUDEPATH  += ../../includes
 HEADERS +=\
     pluginhello.h \
    ../../includes/plugin_interface.h
 SOURCES += \
     pluginhello.cpp
 TARGET        = $$qtLibraryTarget(gis_hello)
 DESTDIR       = /home/delphist007/

 # install
 target.path = /home/delphist007
 sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS PluginHello.pro
 sources.path = /home/delphist007/projects/DB/example
 INSTALLS += target sources

 symbian: include($$QT_SOURCE_TREE/examples/symbianpkgrules.pri)

s ymbian:TARGET.EPOCALLOWDLLDATA = 1
