include(../../pri/tests.pri)

QT       += testlib
QT       -= gui

TARGET = main
CONFIG   += console
CONFIG   -= app_bundle

DEFINES += SRCDIR=\\\"$$PWD/\\\"
DEFINES += JSON_LIBRARY

TEMPLATE = app

#registerLibrary('Json')

HEADERS += \
    test_data.h \
    json.h \
    json_arr.h \
    json_obj.h \
    json_global.h \
    defines.h

SOURCES += main.cpp \
    json.cpp \
    json_arr.cpp \
    json_obj.cpp
