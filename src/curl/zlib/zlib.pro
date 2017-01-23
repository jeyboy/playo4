include(../../../pri/zlib.pri)

#version 1.2.11

QT -= core gui

TARGET = zlib$${LIB_SUFFIX}
TEMPLATE = lib
DEFINES += ZLIB_LIBRARY

defined(STATIC_BUILD) {
    CONFIG += staticlib
}


INCLUDE_HEADERS = \
        "crc32.h" \
        "deflate.h" \
        "gzguts.h" \
        "inffast.h" \
        "inffixed.h" \
        "inflate.h" \
        "inftrees.h" \
        "trees.h" \
        "zconf.h" \
        "zlib.h" \
        "zlib_global.h" \
        "zutil.h"


HEADERS += \
        $${INCLUDE_HEADERS}

SOURCES += \
        "adler32.c" \
        "compress.c" \
        "crc32.c" \
        "deflate.c" \
        "gzclose.c" \
        "gzlib.c" \
        "gzread.c" \
        "gzwrite.c" \
        "infback.c" \
        "inffast.c" \
        "inflate.c" \
        "inftrees.c" \
        "trees.c" \
        "uncompr.c" \
        "zutil.c"


include($${PROJECT_ROOT_PATH}/pri/headers_preparer.pri)

win32 {
    QMAKE_TARGET_PRODUCT = LibCurl
    QMAKE_TARGET_DESCRIPTION = Socket requests lib
}
