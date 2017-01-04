include(../../pri/json.pri)

QT       -= gui

TARGET = Json$${LIB_SUFFIX}
TEMPLATE = lib
#CONFIG += staticlib # add for static linking
DEFINES += JSON_LIBRARY

SOURCES += json.cpp

HEADERS += json.h \
    json_global.h # remove for static linking

INCLUDEPATH += $${INNER_INC_PATH}

######## setup block

HEADERS_OUTPUT_PATH = $$shell_path($${INC_PATH}/$${TARGET})
!exists($$HEADERS_OUTPUT_PATH) {
    post_link = $(MKDIR) $$HEADERS_OUTPUT_PATH $$escape_expand(\\n\\t)
}

for(header, HEADERS) {
    post_link += $(COPY_FILE) "$$shell_path($$PWD/$$header)" "$$shell_path($$HEADERS_OUTPUT_PATH/$$header)" $$escape_expand(\\n\\t)
}

QMAKE_POST_LINK = $$post_link

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
