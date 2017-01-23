pathes =
post_link =

HEADERS_OUTPUT_PATH = $$shell_path($${INC_PATH}/$${TARGET})
!exists($$HEADERS_OUTPUT_PATH) {
    post_link = $(MKDIR) $$HEADERS_OUTPUT_PATH $$escape_expand(\\n\\t)
}

pathes += $$HEADERS_OUTPUT_PATH

for(header, INCLUDE_HEADERS) {
    hpath = $$shell_path($$HEADERS_OUTPUT_PATH/$$header)
    hdir = $$dirname(hpath)

    !contains(pathes, $$hdir) {
        !exists($$hdir) {
            post_link += $(MKDIR) "$$hdir" $$escape_expand(\\n\\t)
            pathes += $$hdir
        }
    }

    post_link += $(COPY_FILE) "$$shell_path($$_PRO_FILE_PWD_/$$header)" "$$hpath" $$escape_expand(\\n\\t)
}

for(header, ADDITIONAL_HEADERS) {
    hpath = $$shell_path($$HEADERS_OUTPUT_PATH/$$header)
    hdir = $$dirname(hpath)

    !contains(pathes, $$hdir) {
        !exists($$hdir) {
            post_link += $(MKDIR) "$$hdir" $$escape_expand(\\n\\t)
            pathes += $$hdir
        }
    }

    post_link += $(COPY_FILE) "$$shell_path($${INNER_INC_PATH}/$$header)" "$$hpath" $$escape_expand(\\n\\t)
}

QMAKE_POST_LINK = $$post_link
