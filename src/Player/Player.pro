include(../../pri/player.pri)

QT += widgets opengl
QT -= gui

TARGET = Player$${LIB_SUFFIX}
TEMPLATE = lib
DEFINES += PLAYER_LIBRARY

defined(STATIC_BUILD) {
    CONFIG += staticlib
}

INCLUDE_HEADERS = \
    player.h

HEADERS += \
    $${INCLUDE_HEADERS}


SOURCES += \
    player.cpp


######## setup block
include($${PROJECT_ROOT_PATH}/pri/headers_preparer.pri)
####### end setup block

win32 {
    QMAKE_TARGET_PRODUCT = Player Lib
    QMAKE_TARGET_DESCRIPTION = PLAYER library
}
