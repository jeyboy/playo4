include(../../pri/api.pri)

QT += widgets network
QT -= gui

TARGET = Api$${LIB_SUFFIX}
TEMPLATE = lib
DEFINES += API_LIBRARY

defined(STATIC_BUILD) {
    CONFIG += staticlib
}

INCLUDE_HEADERS =

HEADERS += \
    $${INCLUDE_HEADERS} \
    api.h

SOURCES += api.cpp

include($${PROJECT_ROOT_PATH}/pri/headers_preparer.pri)

win32 {
    QMAKE_TARGET_PRODUCT = Api Lib
    QMAKE_TARGET_DESCRIPTION = API library
}
