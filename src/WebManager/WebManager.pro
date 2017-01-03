include(../../pri/web_manager.pri)

QT       += network

QT       -= gui

TARGET = WebManager$${LIB_SUFFIX}
TEMPLATE = lib

DEFINES += WEBMANAGER_LIBRARY

SOURCES += webmanager.cpp

HEADERS += webmanager.h\
        webmanager_global.h

win32 {
    QMAKE_TARGET_PRODUCT = WebManager Lib
    QMAKE_TARGET_DESCRIPTION = WebManager library

#    CONFIG += dll
}

#unix {
#    target.path = /usr/lib
#    INSTALLS += target
#}
