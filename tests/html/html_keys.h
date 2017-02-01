#ifndef HTML_PARSER_KEYS
#define HTML_PARSER_KEYS

#include "defines.h"

#define HTML_BR_TAG LSTR("br")
#define HTML_META_TAG LSTR("meta")
#define HTML_LINK_TAG LSTR("link")
#define HTML_IMG_TAG LSTR("img")
#define HTML_DOCTYPE_TAG LSTR("!DOCTYPE")
#define HTML_XML_TAG LSTR("?xml")
#define HTML_INPUT_TAG LSTR("input")
#define HTML_BASE_TAG LSTR("base")

namespace Html {
    extern const QString tag_doctype;
    extern const QString tag_input;
    extern const QString tag_select;
    extern const QString tag_textarea;
    extern const QString tag_img;
    extern const QString tag_br;
    extern const QString tag_a;
    extern const QString tag_script;
    extern const QString tag_head;
    extern const QString tag_xml;
    extern const QString tag_meta;
    extern const QString tag_link;

    extern const QString tkn_split;
    extern const QString tkn_any_elem;
    extern const QString tkn_text_block;
    extern const QString tkn_comment_block;
    extern const QString tkn_service_block;

    extern const QString tkn_charset;
    extern const QString tkn_encoding;
    extern const QString tkn_charset_attr;
    extern const QString tkn_http_equiv;
    extern const QString tkn_content_type;
    extern const QString tkn_content;

    extern const QString attr_name;
    extern const QString attr_action;
    extern const QString attr_href;
    extern const QString attr_src;
    extern const QString attr_id;
    extern const QString attr_class;
    extern const QString attr_type;
    extern const QString attr_default;
    extern const QString attr_checked;

    extern const QString type_radio;
}

#endif // HTML_PARSER_KEYS
