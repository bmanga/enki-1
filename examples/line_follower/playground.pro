TEMPLATE = app
TARGET = run
INCLUDEPATH += .

INCLUDEPATH += /usr/local/include/enki
INCLUDEPATH += /home/sama/Documents/clBP/include

# Input
HEADERS += Racer.h \
    Ico.h \
    IcoFilters.h \
    filterbank.h

SOURCES += run.cpp \
    Racer.cpp \
    Ico.cpp \
    IcoFilters.cpp \
    filterbank.cpp

QT += opengl widgets
CONFIG          += qt warn_on debuge debug
QMAKE_CXXFLAGS += -std=c++0x -march=native -Wunused -pedantic -lenki
QMAKE_LFLAGS += -lenki

LIBS    += /home/sama/Documents/clBP/cmake-build-release/libclBP.a /home/sama/Documents/enki-1/enki/libenki.a

RESOURCES += \
    textures.qrc


copydata.commands = $(COPY_DIR) $$PWD/h.dat $$PWD/cc.png $$PWD/hh.dat $$OUT_PWD

first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata

