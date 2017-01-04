include(../../pri/api.pri)

QT += widgets network
QT -= gui

TARGET = Api$${LIB_SUFFIX}
TEMPLATE = lib
DEFINES += API_LIBRARY
#CONFIG += staticlib

SOURCES += api.cpp

HEADERS += api.h

INCLUDEPATH += $${INNER_INC_PATH}

win32 {
    QMAKE_TARGET_PRODUCT = Api Lib
    QMAKE_TARGET_DESCRIPTION = API library

#    CONFIG += dll
}

#unix {
#    target.path = /usr/lib
#    INSTALLS += target
#}
