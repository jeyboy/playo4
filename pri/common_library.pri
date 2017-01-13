include(./compile.pri)

DESTDIR = $${LIBS_PATH}/

win32: DLLDESTDIR = $${BIN_PATH}/
QMAKE_TARGET_COPYRIGHT = (c) JB

ADDITIONAL_HEADERS += defines.h #$$absolute_path("$${INNER_INC_PATH}/defines.h")
