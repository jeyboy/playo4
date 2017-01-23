include(../../pri/tests.pri)

QT       += testlib
QT       -= gui

TARGET = main
CONFIG   += console
CONFIG   -= app_bundle

DEFINES += SRCDIR=\\\"$$PWD/\\\"

TEMPLATE = app

INCLUDEPATH += $${INC_PATH}/CurlLib
DEPENDPATH += $${INC_PATH}/CurlLib
LIBS += -lCurlLib$${LIB_VERSION}

SOURCES += main.cpp
