PROJECT_ROOT_PATH = $$absolute_path($${PWD}/../)
MAJOR_VERSION = 0

win32: OS_SUFFIX = win32
linux-g++: OS_SUFFIX = linux

CONFIG(debug, debug|release) {
    BUILD_FLAG = debug
    LIB_SUFFIX = d
} else {
    BUILD_FLAG = release
}

LIBS_PATH = $${PROJECT_ROOT_PATH}/lib.$${OS_SUFFIX}/
INC_PATH = $${PROJECT_ROOT_PATH}/include/
IMPORT_PATH = $${PROJECT_ROOT_PATH}/import/
BIN_PATH = $${PROJECT_ROOT_PATH}/bin/$${BUILD_FLAG}/
INNER_INC_PATH = $$PROJECT_ROOT_PATH/src/include/

LIBS += -L$${LIBS_PATH}/

linux-g++: QMAKE_CXXFLAGS += -std=c++11

win32 {
    LIB_VERSION = $${LIB_SUFFIX}$${MAJOR_VERSION}
}
unix {
    LIB_VERSION = $${LIB_SUFFIX}#$${VERSION}
}
