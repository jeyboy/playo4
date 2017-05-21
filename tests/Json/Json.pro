include(../../pri/tests.pri)

QT       += testlib
QT       -= gui

TARGET = main
CONFIG   += console
CONFIG   -= app_bundle

DEFINES += SRCDIR=\\\"$$PWD/\\\"

TEMPLATE = app

registerLibrary('Json')

HEADERS += test_data.h

SOURCES += main.cpp
