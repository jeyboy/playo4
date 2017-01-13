isEmpty(LIB_SUFFIX) {
    load(configure)

    CONFIG += recheck

    QMAKE_CONFIG_TESTS_DIR = $${PROJECT_ROOT_PATH}/tests/

    qtCompileTest($${TARGET})
}
