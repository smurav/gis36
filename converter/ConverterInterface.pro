QT+= gui core

LIBS += -Lbin -lConverterLibrary1
INCLUDEPATH += ./includes
TARGET = ConverterInterface
TEMPLATE = app


SOURCES += \
    main.cpp \
    ConverterInterface.cpp

HEADERS  += \
    ConverterInterface.h

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






