include(../../pri/web_manager.pri)

QT += network
QT -= gui

TARGET = WebManager$${LIB_SUFFIX}
TEMPLATE = lib
DEFINES += WEBMANAGER_LIBRARY

defined(STATIC_BUILD) {
    CONFIG += staticlib
}

INCLUDE_HEADERS = \
    webmanager_global.h \ # remove for static linking
    webmanager.h

IMPORT_LIBRARIES_SET = \
    QT \
    BASS


HEADERS += \
    $${INCLUDE_HEADERS}


SOURCES += \
    webmanager.cpp

######## setup block
registerInnerInclusion('singleton')
registerInnerInclusion('func')
include($${PROJECT_ROOT_PATH}/pri/headers_preparer.pri)
####### end setup block

win32 {
    QMAKE_TARGET_PRODUCT = WebManager Lib
    QMAKE_TARGET_DESCRIPTION = WebManager library
}
