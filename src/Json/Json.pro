include(../../pri/json.pri)

QT       -= gui

TARGET = Json$${LIB_SUFFIX}
TEMPLATE = lib
#CONFIG += staticlib # add for static linking
DEFINES += JSON_LIBRARY

SOURCES += json.cpp

HEADERS += json.h \
    json_global.h \ # remove for static linking
    pop/lal.h

INCLUDEPATH += $${INNER_INC_PATH}

######## setup block
include(../../pri/headers_preparer.pri)
####### end setup block

win32 {
    QMAKE_TARGET_PRODUCT = Json Lib
    QMAKE_TARGET_DESCRIPTION = Json library

#    CONFIG += dll
}

#unix {
#    target.path = /usr/lib
#    INSTALLS += target
#}
