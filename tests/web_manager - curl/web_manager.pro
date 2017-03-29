include(../../pri/tests.pri)

QT       += testlib network
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
#    web_connection.cpp \
#    web_manager.cpp

#HEADERS += \
#    web_connection.h \
#    web_headers.h \
#    web_manager.h \
#    func.h
