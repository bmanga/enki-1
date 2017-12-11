TEMPLATE = lib
TARGET = enki-viewer

# Input
HEADERS = EPuckModel.h MarxbotModel.h Thymio2Model.h Viewer.h objects/Objects.h
SOURCES = EPuckModel.cpp \
           MarxbotModel.cpp \
           Thymio2Model.cpp \
           Viewer.cpp \
           objects/EPuckBody.cpp \
           objects/EPuckRest.cpp \
           objects/EPuckRing.cpp \
           objects/EPuckWheelLeft.cpp \
           objects/EPuckWheelRight.cpp \
           objects/MarxbotBase.cpp \
           objects/MarxbotWheel.cpp \
           objects/Thymio2Body.cpp \
           objects/Thymio2Wheel.cpp

RESOURCES += enki-viewer-textures.qrc

QT += opengl widgets
CONFIG          += qt warn_on debug staticlib

QMAKE_CXXFLAGS += -std=c++0x -march=native

LIBS	+= /usr/local/lib/libenki.a

headersDataFiles.path = /usr/local/include
headersDataFiles.files = *.h
INSTALLS += headersDataFiles

libraryFiles.path = /usr/local/lib
libraryFiles.files = libenki-viewer.a
INSTALLS += libraryFiles
