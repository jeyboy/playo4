include(../../../pri/libssh2.pri)

#version 1.8.0

QT -= core gui

TARGET = libss2$${LIB_SUFFIX}
TEMPLATE = lib
DEFINES += LIBSSH2_LIBRARY

defined(STATIC_BUILD) {
    CONFIG += staticlib
}

INCLUDE_HEADERS = \
        libssh2.h \
        libssh2_publickey.h \
        libssh2_sftp.h


HEADERS += \
    $${INCLUDE_HEADERS}


SOURCES += \


include($${PROJECT_ROOT_PATH}/pri/headers_preparer.pri)

win32 {
    QMAKE_TARGET_PRODUCT = LibSSH2
    QMAKE_TARGET_DESCRIPTION = ssh lib
}
