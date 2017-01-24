include(../../pri/tests.pri)

QT       += testlib
QT       -= gui

TARGET = main
CONFIG   += console
CONFIG   -= app_bundle

DEFINES += SRCDIR=\\\"$$PWD/\\\"

TEMPLATE = app

INCLUDEPATH += $${INC_PATH}/Html
DEPENDPATH += $${INC_PATH}/Html
LIBS += -lHtml$${LIB_VERSION}

SOURCES += main.cpp

HEADERS += \
    test_data.h
