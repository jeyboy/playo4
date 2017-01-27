#include "html_keys.h"

namespace Html {
    extern const QString tag_doctype            = LSTR("!DOCTYPE");
    extern const QString tag_input              = LSTR("input");
    extern const QString tag_select             = LSTR("select");
    extern const QString tag_img                = LSTR("img");
    extern const QString tag_br                 = LSTR("br");
    extern const QString tag_a                  = LSTR("a");
    extern const QString tag_script             = LSTR("script");
    extern const QString tag_head               = LSTR("head");
    extern const QString tag_meta               = LSTR("meta");
    extern const QString tag_xml                = LSTR("?xml");
    extern const QString tag_link               = LSTR("link");

    extern const QString tkn_split              = LSTR(" ");
    extern const QString tkn_any_elem           = LSTR("*");
    extern const QString tkn_text_block         = LSTR("text");
    extern const QString tkn_comment_block      = LSTR("comment");
    extern const QString tkn_service_block      = LSTR("service");

    extern const QString tkn_charset            = LSTR("charset");
    extern const QString tkn_encoding           = LSTR("encoding");
    extern const QString tkn_charset_attr       = LSTR("charset=");
    extern const QString tkn_http_equiv         = LSTR("http-equiv");
    extern const QString tkn_content_type       = LSTR("content-type");
    extern const QString tkn_content            = LSTR("content");

    extern const QString attr_name              = LSTR("name");
    extern const QString attr_action            = LSTR("action");
    extern const QString attr_href              = LSTR("href");
    extern const QString attr_src               = LSTR("src");
    extern const QString attr_id                = LSTR("id");
    extern const QString attr_class             = LSTR("class");
    extern const QString attr_type              = LSTR("type");
    extern const QString attr_default           = LSTR("value");
}
