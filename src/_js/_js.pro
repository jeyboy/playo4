include(../../pri/js.pri)

QT       -= gui

TARGET = Js$${LIB_SUFFIX}
TEMPLATE = lib
DEFINES += JS_LIBRARY

defined(STATIC_BUILD) {
    CONFIG += staticlib
}

INCLUDE_HEADERS = \
    js_global.h \ # remove for static linking
    js.h\
    pizduck/duk_config.h \
    pizduck/duktape.h

HEADERS += \
    $${INCLUDE_HEADERS}


SOURCES += \
    js.cpp \
    pizduck/duktape.c

registerInnerInclusion('variant_convertor')

######## setup block
include($${PROJECT_ROOT_PATH}/pri/headers_preparer.pri)
#include($${PROJECT_ROOT_PATH}/pri/test_compile.pri)
####### end setup block

win32 {
    QMAKE_TARGET_PRODUCT = Js Lib
    QMAKE_TARGET_DESCRIPTION = Js library
}

#DISTFILES += \
#    pizduck/metadata.json
