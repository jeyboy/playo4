#ifndef HTML_PARSER_KEYS
#define HTML_PARSER_KEYS

#include "defines.h"
//#include <qbytearray.h>

#define HTML_ANY_TAG QByteArray("*")

#define HTML_BR_TAG QByteArray("br")
#define HTML_HR_TAG QByteArray("hr")
#define HTML_META_TAG QByteArray("meta")
#define HTML_LINK_TAG QByteArray("link")
#define HTML_IMG_TAG QByteArray("img")
#define HTML_DOCTYPE_TAG QByteArray("!doctype")
#define HTML_XML_TAG QByteArray("?xml")
#define HTML_INPUT_TAG QByteArray("input")
#define HTML_BASE_TAG QByteArray("base")
#define HTML_ATTR_TYPE QByteArray("type")

namespace Html {
    extern const QByteArray tag_doctype;
    extern const QByteArray tag_input;
    extern const QByteArray tag_select;
    extern const QByteArray tag_textarea;
    extern const QByteArray tag_img;
    extern const QByteArray tag_br;
    extern const QByteArray tag_a;
    extern const QByteArray tag_script;
    extern const QByteArray tag_style;
    extern const QByteArray tag_head;
    extern const QByteArray tag_body;
    extern const QByteArray tag_xml;
    extern const QByteArray tag_meta;
    extern const QByteArray tag_link;
    extern const QByteArray tag_iframe;

//    extern const char tkn_split;
    extern const QByteArray tkn_any_elem;
    extern const QByteArray tkn_text_block;
    extern const QByteArray tkn_comment_block;

    extern const QByteArray tkn_charset;
    extern const QByteArray tkn_encoding;
    extern const QByteArray tkn_charset_attr;
    extern const QByteArray tkn_http_equiv;
    extern const QByteArray tkn_content_type;
    extern const QByteArray tkn_content;

    extern const QByteArray tkn_scdata;
    extern const QByteArray tkn_ecdata;

    extern const QByteArray attr_name;
    extern const QByteArray attr_action;
    extern const QByteArray attr_href;
    extern const QByteArray attr_src;
    extern const QByteArray attr_id;
    extern const QByteArray attr_class;
    extern const QByteArray attr_type;
    extern const QByteArray attr_default;
    extern const QByteArray attr_checked;
    extern const QByteArray attr_disabled;

    extern const QByteArray type_radio;
    extern const QByteArray type_checkbox;
}

#endif // HTML_PARSER_KEYS
