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
    $${INCLUDE_HEADERS} \
    channel.h \
    comp.h \
    crypto.h \
    libgcrypt.h \
    libssh2_priv.h \
    mac.h \
    mbedtls.h \
    misc.h \
    openssl.h \
    os400qc3.h \
    packet.h \
    session.h \
    sftp.h \
    transport.h \
    userauth.h \
    wincng.h \
    libssh2_config.h


SOURCES += \
    agent.c \
    channel.c \
    comp.c \
    crypt.c \
    global.c \
    hostkey.c \
    keepalive.c \
    kex.c \
    knownhost.c \
    libgcrypt.c \
    mac.c \
    mbedtls.c \
    misc.c \
    openssl.c \
    os400qc3.c \
    packet.c \
    pem.c \
    publickey.c \
    scp.c \
    session.c \
    sftp.c \
    transport.c \
    userauth.c \
    version.c \
    wincng.c


include($${PROJECT_ROOT_PATH}/pri/headers_preparer.pri)

win32 {
    QMAKE_TARGET_PRODUCT = LibSSH2
    QMAKE_TARGET_DESCRIPTION = ssh lib
}
