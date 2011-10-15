#---------------------------------------------------
#
# Пример проекта, создающего подключаемую библиотеку
#
# Project created by QtCreator 2011-09-25T13:42:06
#
#---------------------------------------------------

# Имя выходного файла
TARGET      = library

# Создаем подключаемую библиотеку
TEMPLATE    = lib
CONFIG      += qt dll
DEFINES     += GIS36_LIBRARY_EXPORTS

# Дополнительные пути поиска заголовчных фалов
INCLUDEPATH = ../include

# Относительный путь рабочего каталога репозитория
OUTPUT      = ../../..

# Относительный путь каталога для хранения временных файлов
TEMP        = $${OUTPUT}/temp/examples/library

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

# Исходные файлы
SOURCES     += library.cpp

# Заголовочные файлы
HEADERS     += library.h
