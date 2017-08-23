include(../../pri/tests.pri)

QT       += testlib network gui widgets
QT       -= gui

TARGET = main
CONFIG   += console
CONFIG   -= app_bundle

DEFINES += SRCDIR=\\\"$$PWD/\\\"
DEFINES += WEBMANAGER_LIBRARY

TEMPLATE = app

registerLibrary('Html')
registerLibrary('Json')

#INCLUDEPATH += $${INC_PATH}/Html
#DEPENDPATH += $${INC_PATH}/Html
#LIBS += -lHtml$${LIB_VERSION}

#INCLUDEPATH += $${INC_PATH}/Json
#DEPENDPATH += $${INC_PATH}/Json
#LIBS += -lJson$${LIB_VERSION}

#INCLUDEPATH += $${INC_PATH}/CurlLib
#DEPENDPATH += $${INC_PATH}/CurlLib
#LIBS += -lCurlLib$${LIB_VERSION}

SOURCES += main.cpp \
    web_connection.cpp \
    web_manager.cpp \
    web_cookies.cpp \
    web_request.cpp \
    web_response.cpp \
    variant_convertor.cpp \
    web_proxy.cpp \
    country.cpp

HEADERS += \
    defines.h \
    singleton.h \
    web_connection.h \
    web_headers.h \
    web_manager.h \
    func.h \
    web_cookies.h \
    web_request.h \
    web_response.h \
    web_manager_global.h \
    web_utils.h \
    web_request_params.h \
    variant_ptr.h \
    variant_convertor.h \
    web_proxy.h \
    country.h
