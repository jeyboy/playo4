include(../../pri/desktop_interface.pri)

QT += core gui widgets

TARGET = Playo4
TEMPLATE = app

SOURCES += main.cpp \
    mainwindow.cpp

HEADERS += mainwindow.h

FORMS += mainwindow.ui

INCLUDEPATH += $${INNER_INC_PATH}

LIBS += -lTagLib$${LIB_VERSION} -lJson$${LIB_VERSION} -lHtml$${LIB_VERSION} -lWebManager$${LIB_VERSION} -lApi$${LIB_VERSION} -lPlayer$${LIB_VERSION}
#LIBS += -L$$PWD/libs/bass/ -lbass -lbass_fx -lbassmix
#INCLUDEPATH += $$PWD/libs/bass/include
#DEPENDPATH += $$PWD/libs/bass
