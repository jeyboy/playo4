include(../../pri/tests.pri)

QT       += testlib
QT       -= gui

TARGET = main
CONFIG   += console
CONFIG   -= app_bundle

DEFINES += SRCDIR=\\\"$$PWD/\\\" HTML_LIBRARY

TEMPLATE = app

INCLUDEPATH += $${INC_PATH}/Html
DEPENDPATH += $${INC_PATH}/Html
LIBS += -lHtml$${LIB_VERSION}


#### test

#HEADERS += \
#    html_global.h \
#    html_page.h \
#    html_keys.h \
#    html_selector.h \
#    html_set.h \
#    html_tag.h \
#    defines.h \
#    list.h \
#    html_decoding.h \
#    unicode.h \
#    memory.h

#SOURCES += \
#    html_page.cpp \
#    html_keys.cpp \
#    html_selector.cpp \
#    html_set.cpp \
#    html_tag.cpp \
#    html_decoding.cpp \
#    unicode.cpp
#### test



SOURCES += main.cpp

HEADERS += \
    test_data.h

win32:LIBS += -lpsapi
