include(../../pri/json.pri)

QT       -= gui

TARGET = Json$${LIB_SUFFIX}
TEMPLATE = lib
#CONFIG += staticlib # add for static linking
DEFINES += JSON_LIBRARY

SOURCES += json.cpp \
    json_obj.cpp \
    json_arr.cpp

HEADERS += json.h \
    json_global.h \  # remove for static linking
    json_obj.h \
    json_arr.h \
    json_interface.h

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
