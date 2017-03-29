#ifndef HTML_PARSER_KEYS
#define HTML_PARSER_KEYS

#include "defines.h"
//#include <qbytearray.h>

#define HTML_ANY_TAG QByteArrayLiteral("*")
#define HTML_TEXT_BLOCK QByteArrayLiteral("text")
#define HTML_TAG_DOCTYPE QByteArrayLiteral("!doctype")
#define HTML_TAG_XML QByteArrayLiteral("?xml")
#define HTML_TAG_INPUT QByteArrayLiteral("input")
#define HTML_TAG_IMG QByteArrayLiteral("img")
#define HTML_TAG_BR QByteArrayLiteral("br")
#define HTML_TAG_BODY QByteArrayLiteral("body")
#define HTML_TAG_HEAD QByteArrayLiteral("head")
#define HTML_TAG_LINK QByteArrayLiteral("link")
#define HTML_TAG_A QByteArrayLiteral("a")
#define HTML_TAG_META QByteArrayLiteral("meta")
#define HTML_TAG_IFRAME QByteArrayLiteral("iframe")
#define HTML_TAG_SCRIPT QByteArrayLiteral("script")
#define HTML_TAG_STYLE QByteArrayLiteral("style")
#define HTML_TAG_SELECT QByteArrayLiteral("select")
#define HTML_TAG_TEXTAREA QByteArrayLiteral("textarea")

#define HTML_ATTR_TYPE QByteArrayLiteral("type")

namespace Html {
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
