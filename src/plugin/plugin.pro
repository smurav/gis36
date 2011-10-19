TEMPLATE      = lib
 CONFIG       += plugin
 INCLUDEPATH  += ../gis36
 HEADERS +=\
     start_plugin.h \
    ../gis36/plugin_interface.h \
    ../gis36/shell_interface.h
 SOURCES += \
     start_plugin.cpp
 TARGET        = $$qtLibraryTarget(gis_hello)
DESTDIR       =  ./output

 # install
 target.path = ./output
 sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS PluginHello.pro
 sources.path = ./
 INSTALLS += target sources





