include(../../pri/json.pri)

QT       -= gui

TARGET = Json$${LIB_SUFFIX}
TEMPLATE = lib

DEFINES += JSON_LIBRARY

SOURCES += json.cpp

HEADERS += json.h\
        json_global.h

win32 {
    QMAKE_TARGET_PRODUCT = Json Lib
    QMAKE_TARGET_DESCRIPTION = Json library

#    CONFIG += dll
}

#unix {
#    target.path = /usr/lib
#    INSTALLS += target
#}
