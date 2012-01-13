TEMPLATE      = lib
 CONFIG       += plugin
 INCLUDEPATH  += ../includes
 HEADERS +=\
     start_plugin.h

 SOURCES += \
     start_plugin.cpp
 TARGET        = $$qtLibraryTarget(gis_hello)
DESTDIR       =  ./output

 # install
 target.path = ./output
 sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS PluginHello.pro
 sources.path = ./
 INSTALLS += target sources





