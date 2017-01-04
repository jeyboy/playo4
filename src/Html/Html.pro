include(../../pri/html.pri)

QT       -= gui

TARGET = Html$${LIB_SUFFIX}
TEMPLATE = lib
#CONFIG += staticlib # add for static linking
DEFINES += HTML_LIBRARY

SOURCES += html.cpp

HEADERS += html.h \
    html_global.h # remove for static linking

INCLUDEPATH += $${INNER_INC_PATH}

######## setup block
include(../../pri/headers_preparer.pri)
####### end setup block

win32 {
    QMAKE_TARGET_PRODUCT = Html Lib
    QMAKE_TARGET_DESCRIPTION = Html library

#    CONFIG += dll
}

#unix {
#    target.path = /usr/lib
#    INSTALLS += target
#}
