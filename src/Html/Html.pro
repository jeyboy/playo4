include(../../pri/html.pri)

QT       -= gui

TARGET = Html$${LIB_SUFFIX}
TEMPLATE = lib

DEFINES += HTML_LIBRARY

SOURCES += html.cpp

HEADERS += html.h\
        html_global.h

win32 {
    QMAKE_TARGET_PRODUCT = Html Lib
    QMAKE_TARGET_DESCRIPTION = Html library

#    CONFIG += dll
}

#unix {
#    target.path = /usr/lib
#    INSTALLS += target
#}
