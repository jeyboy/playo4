include(../../pri/tests.pri)

QT       += testlib

QT       -= gui

TARGET = main
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += $${INC_PATH}/Js
DEPENDPATH += $${INC_PATH}/Js
LIBS += -lJs$${LIB_VERSION}

SOURCES += main.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    test_data.h
