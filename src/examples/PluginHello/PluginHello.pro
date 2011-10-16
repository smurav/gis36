 TEMPLATE      = lib
 CONFIG       += plugin
 INCLUDEPATH  += ../../includes
 HEADERS +=\
     pluginhello.h \
    ../../includes/plugin_interface.h
 SOURCES += \
     pluginhello.cpp
 TARGET        = $$qtLibraryTarget(gis36_hello)

 DESTDIR       =  ./output

 # install	
 target.path = ./output
 sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS PluginHello.pro
 sources.path = ./
 INSTALLS += target sources
