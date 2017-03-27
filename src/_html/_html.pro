include(../../pri/html.pri)

QT       -= gui

TARGET = Html$${LIB_SUFFIX}
TEMPLATE = lib
DEFINES += HTML_LIBRARY

defined(STATIC_BUILD) {
    CONFIG += staticlib
}

INCLUDE_HEADERS = \
    html_decoding.h \
    html_global.h \
    html_keys.h \
    html_page.h \
    html_selector.h \
    html_set.h \
    html_tag.h \
    unicode.h


HEADERS += \
    $${INCLUDE_HEADERS}


SOURCES += \
    html_decoding.cpp \
    html_keys.cpp \
    html_page.cpp \
    html_selector.cpp \
    html_set.cpp \
    html_tag.cpp \
    unicode.cpp



######## setup block
include($${PROJECT_ROOT_PATH}/pri/headers_preparer.pri)
####### end setup block

win32 {
    QMAKE_TARGET_PRODUCT = Html Lib
    QMAKE_TARGET_DESCRIPTION = Html library
}
