include(../../pri/tests.pri)

QT       += testlib
QT       -= gui

TARGET = main
CONFIG   += console
CONFIG   -= app_bundle

DEFINES += SRCDIR=\\\"$$PWD/\\\"

TEMPLATE = app

#INCLUDEPATH += $${INC_PATH}/Html
#DEPENDPATH += $${INC_PATH}/Html
#LIBS += -lHtml$${LIB_VERSION}


### test
TEST_PATH = $${INNER_INC_PATH}/../_html/

HEADERS += \
    $${TEST_PATH}html_global.h \
    $${TEST_PATH}html_page.h \
    $${TEST_PATH}unicode_decoding.h \
    $${TEST_PATH}html_keys.h \
    $${TEST_PATH}html_selector.h \
    $${TEST_PATH}html_set.h \
    $${TEST_PATH}html_tag.h \
    ../../src/include/defines.h

SOURCES += \
    $${TEST_PATH}html_page.cpp \
    $${TEST_PATH}unicode_decoding.cpp \
    $${TEST_PATH}html_keys.cpp \
    $${TEST_PATH}html_selector.cpp \
    $${TEST_PATH}html_set.cpp \
    $${TEST_PATH}html_tag.cpp
### test



SOURCES += main.cpp

HEADERS += \
    test_data.h
