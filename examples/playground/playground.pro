TEMPLATE = app
TARGET = playground
INCLUDEPATH += .

# Input
SOURCES += Playground.cpp

QT += opengl widgets
CONFIG          += qt warn_on debug
QMAKE_CXXFLAGS += -std=c++0x -march=native

LIBS	+= /usr/local/lib/libenki.a
LIBS    += /usr/local/lib/libenki-viewer.a
