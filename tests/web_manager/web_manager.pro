include(../../pri/tests.pri)

QT       += testlib network gui widgets
#QT       -= gui

TARGET = main
CONFIG   += console
CONFIG   -= app_bundle

DEFINES += SRCDIR=\\\"$$PWD/\\\"

TEMPLATE = app

INCLUDEPATH += $${INC_PATH}/Html
DEPENDPATH += $${INC_PATH}/Html
LIBS += -lHtml$${LIB_VERSION}

#INCLUDEPATH += $${INC_PATH}/CurlLib
#DEPENDPATH += $${INC_PATH}/CurlLib
#LIBS += -lCurlLib$${LIB_VERSION}

SOURCES += main.cpp \
    web_connection.cpp \
    web_manager.cpp \
    web_cookies.cpp \
    web_request.cpp \
    web_response.cpp

HEADERS += \
    singleton.h \
    web_connection.h \
    web_headers.h \
    web_manager.h \
    func.h \
    web_cookies.h \
    web_request.h \
    web_response.h \
    web_manager_params.h \
    web_manager_global.h \
    web_utils.h
