include(../../pri/tests.pri)

QT       += testlib
QT       -= gui

TARGET = main
CONFIG   += console
CONFIG   -= app_bundle

DEFINES += SRCDIR=\\\"$$PWD/\\\"

TEMPLATE = app

INCLUDEPATH += $${INC_PATH}/Json
DEPENDPATH += $${INC_PATH}/Json
LIBS += -lJson$${LIB_VERSION}

HEADERS += \
    test_data.h

SOURCES += main.cpp
