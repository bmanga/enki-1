TEMPLATE = app
TARGET = run
INCLUDEPATH += .
INCLUDEPATH += ../../enki
INCLUDEPATH += ../../enki/interactions
INCLUDEPATH += ../../enki/objects
INCLUDEPATH += ../../enki/robots
INCLUDEPATH += ../../enki/textures
INCLUDEPATH += ../../enki/widgets
INCLUDEPATH += /usr/local/include/enki
INCLUDEPATH += /home/sama/Documents/clBP/include

# Input
HEADERS += Racer.h \
    Filter.h \
    ICO.h \
    FilterBank.h

SOURCES += run.cpp \
    Racer.cpp \
    Filter.cpp \
    ICO.cpp \
    FilterBank.cpp

QT += opengl widgets
CONFIG          += qt warn_on debuge debug
QMAKE_CXXFLAGS += -std=c++0x -march=native -Wunused -pedantic

#LIBS	+= /usr/local/lib/libenki.a
LIBS	+= ../../enki/libenki.a
LIBS    += /home/sama/Documents/clBP/cmake-build-release/libclBP.a

