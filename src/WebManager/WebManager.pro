include(../../pri/web_manager.pri)

QT += network
QT -= gui

TARGET = WebManager$${LIB_SUFFIX}
TEMPLATE = lib
#CONFIG += staticlib # add for static linking
DEFINES += WEBMANAGER_LIBRARY

SOURCES += webmanager.cpp

HEADERS += $${INNER_INC_PATH}defines.h \
    webmanager.h \
    webmanager_global.h # remove for static linking

win32 {
    QMAKE_TARGET_PRODUCT = WebManager Lib
    QMAKE_TARGET_DESCRIPTION = WebManager library

#    CONFIG += dll
}

#unix {
#    target.path = /usr/lib
#    INSTALLS += target
#}
