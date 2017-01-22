include(../../pri/tests.pri)

QT       += testlib

QT       -= gui

TARGET = main
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += $${INC_PATH}/CurlLib
DEPENDPATH += $${INC_PATH}/CurlLib
LIBS += -lCurlLib$${LIB_VERSION}

DEFINES += SRCDIR=\\\"$$PWD/\\\"

SOURCES += main.cpp
