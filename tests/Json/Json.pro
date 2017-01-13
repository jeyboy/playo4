include(../../pri/tests.pri)

QT       += testlib

QT       -= gui

TARGET = main
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += $${INC_PATH}/Json
DEPENDPATH += $${INC_PATH}/Json
LIBS += -lJson$${LIB_VERSION}

SOURCES += main.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
