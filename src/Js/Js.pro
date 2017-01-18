include(../../pri/js.pri)

QT       -= gui

TARGET = Js$${LIB_SUFFIX}
TEMPLATE = lib
#CONFIG += staticlib # add for static linking
DEFINES += JS_LIBRARY

HEADERS += js.h\
        js_global.h \ # remove for static linking
    pizduck/duk_config.h \
    pizduck/duktape.h

SOURCES += js.cpp \
    pizduck/duktape.c

ADDITIONAL_HEADERS += variant_convertor.h

######## setup block
include(../../pri/headers_preparer.pri)
#include(../../pri/test_compile.pri)
####### end setup block

win32 {
    QMAKE_TARGET_PRODUCT = Js Lib
    QMAKE_TARGET_DESCRIPTION = Js library

#    CONFIG += dll
}

#unix {
#    target.path = /usr/lib
#    INSTALLS += target
#}

DISTFILES += \
    pizduck/metadata.json
