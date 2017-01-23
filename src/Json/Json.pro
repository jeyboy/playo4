include(../../pri/json.pri)

QT -= gui

TARGET = Json$${LIB_SUFFIX}
TEMPLATE = lib
DEFINES += JSON_LIBRARY

defined(STATIC_BUILD) {
    CONFIG += staticlib
}

INCLUDE_HEADERS = \
    json_global.h \  # remove for static linking
    json.h \
    json_obj.h \
    json_arr.h

HEADERS += \
    $${INCLUDE_HEADERS}


SOURCES += json.cpp \
    json_obj.cpp \
    json_arr.cpp


######## setup block
include($${PROJECT_ROOT_PATH}/pri/headers_preparer.pri)
#include($${PROJECT_ROOT_PATH}/pri/test_compile.pri)
####### end setup block

win32 {
    QMAKE_TARGET_PRODUCT = Json Lib
    QMAKE_TARGET_DESCRIPTION = Json library
}
