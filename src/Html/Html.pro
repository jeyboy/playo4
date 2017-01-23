include(../../pri/html.pri)

QT       -= gui

TARGET = Html$${LIB_SUFFIX}
TEMPLATE = lib
DEFINES += HTML_LIBRARY

defined(STATIC_BUILD) {
    CONFIG += staticlib
}

INCLUDE_HEADERS = \
    html_global.h \ # remove for static linking
    html.h \
    unicode_decoding.h \
    html_keys.h \
    html_selector.h \
    html_set.h \
    html_tag.h

HEADERS += \
    $${INCLUDE_HEADERS}


SOURCES += \
    html.cpp \
    unicode_decoding.cpp \
    html_keys.cpp \
    html_selector.cpp \
    html_set.cpp \
    html_tag.cpp


######## setup block
include($${PROJECT_ROOT_PATH}/pri/headers_preparer.pri)
####### end setup block

win32 {
    QMAKE_TARGET_PRODUCT = Html Lib
    QMAKE_TARGET_DESCRIPTION = Html library
}
