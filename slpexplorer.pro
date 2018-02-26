
QT       += core gui widgets

TARGET = slpexplorer
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
        widget.cpp

HEADERS += \
        widget.h

LIBS += -lgenieutils -L/home/sandsmark/src/freeaoe/extern/genieutils/build

INCLUDEPATH += /home/sandsmark/src/freeaoe/extern/genieutils/include
