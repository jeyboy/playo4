include(../../pri/client_side.pri)

QT += core gui widgets

TARGET = ClientSide
TEMPLATE = app

SOURCES += main.cpp \
    mainwindow.cpp

HEADERS += $${INNER_INC_PATH}/defines.h \
    mainwindow.h


FORMS += mainwindow.ui

win32 {
    LIB_VERSION = $${LIB_SUFFIX}$${MAJOR_VERSION}
}
unix {
    LIB_VERSION = $${LIB_SUFFIX}$${VERSION}
}

LIBS += -lTagLib$${LIB_VERSION} -lJson$${LIB_VERSION} -lHtml$${LIB_VERSION} -lWebManager$${LIB_VERSION} -lApi$${LIB_VERSION} -lPlayer$${LIB_VERSION}
