TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS += \
#    src/__curl \
    src/__tag_lib \ # done
    src/_js \ # done
    src/_json \ # done
    src/_html \ # done
    src/_web_manager \
    src/_api \
    src/_player \
    src/desktop_interface \
    tests
