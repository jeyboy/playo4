QT += core gui widgets

TARGET = ClientSide
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

include(../../pri/client_side.pri)

win32 {
    LIBS += -lApi$${LIB_SUFFIX}$${MAJOR_VERSION} -lPlayer$${LIB_SUFFIX}$${MAJOR_VERSION}
}

unix {
    LIBS += -lApi$${LIB_SUFFIX}$${VERSION} -lPlayer$${LIB_SUFFIX}$${VERSION}
}
