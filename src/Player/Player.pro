include(../../pri/player.pri)

QT += widgets opengl

QT -= gui

TARGET = Player$${LIB_SUFFIX}
TEMPLATE = lib
#CONFIG += staticlib
DEFINES += PLAYER_LIBRARY

SOURCES += player.cpp

HEADERS += player.h

win32 {
    QMAKE_TARGET_PRODUCT = Player Lib
    QMAKE_TARGET_DESCRIPTION = PLAYER library

#    CONFIG += dll
}

#unix {
#    target.path = /usr/lib
#    INSTALLS += target
#}
