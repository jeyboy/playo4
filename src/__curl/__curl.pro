TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS += \
    __zlib \
#    __libss2 \
    _curl_lib

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
LIBS += -llibeay32 -lssleay32
