include(../../pri/tests.pri)

QT       += testlib
QT       -= gui

TARGET = main
CONFIG   += console
CONFIG   -= app_bundle

DEFINES += SRCDIR=\\\"$$PWD/\\\" HTML_LIBRARY

TEMPLATE = app

#INCLUDEPATH += $${INC_PATH}/Html
#DEPENDPATH += $${INC_PATH}/Html
#LIBS += -lHtml$${LIB_VERSION}


### test

HEADERS += \
    html_global.h \
    html_page.h \
    unicode_decoding.h \
    html_keys.h \
    html_selector.h \
    html_set.h \
    html_tag.h \
    defines.h

SOURCES += \
    html_page.cpp \
    unicode_decoding.cpp \
    html_keys.cpp \
    html_selector.cpp \
    html_set.cpp \
    html_tag.cpp
### test



SOURCES += main.cpp

HEADERS += \
    test_data.h
