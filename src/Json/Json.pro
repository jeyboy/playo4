include(../../pri/json.pri)

QT       -= gui

TARGET = Json$${LIB_SUFFIX}
TEMPLATE = lib
#CONFIG += staticlib # add for static linking
DEFINES += JSON_LIBRARY

SOURCES += json.cpp

HEADERS += $${INNER_INC_PATH}/defines.h \
    json.h \
    json_global.h # remove for static linking

win32 {
    QMAKE_TARGET_PRODUCT = Json Lib
    QMAKE_TARGET_DESCRIPTION = Json library

#    CONFIG += dll
}

#unix {
#    target.path = /usr/lib
#    INSTALLS += target
#}
