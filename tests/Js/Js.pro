include(../../pri/tests.pri)

QT       += testlib
QT       -= gui

TARGET = main
CONFIG   += console
CONFIG   -= app_bundle

DEFINES += SRCDIR=\\\"$$PWD/\\\"

TEMPLATE = app

INCLUDEPATH += $${INC_PATH}/Js
DEPENDPATH += $${INC_PATH}/Js
LIBS += -lJs$${LIB_VERSION}

SOURCES += main.cpp

HEADERS += \
    test_data.h
