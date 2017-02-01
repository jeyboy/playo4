#include "html_keys.h"

namespace Html {
    extern const QString tag_doctype            = HTML_DOCTYPE_TAG;
    extern const QString tag_input              = HTML_INPUT_TAG;
    extern const QString tag_select             = LSTR("select");
    extern const QString tag_textarea           = LSTR("textarea");
    extern const QString tag_img                = HTML_IMG_TAG;
    extern const QString tag_br                 = HTML_BR_TAG;
    extern const QString tag_a                  = LSTR("a");
    extern const QString tag_script             = LSTR("script");
    extern const QString tag_head               = LSTR("head");
    extern const QString tag_meta               = HTML_META_TAG;
    extern const QString tag_xml                = HTML_XML_TAG;
    extern const QString tag_link               = HTML_LINK_TAG;

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
    extern const QString attr_checked           = LSTR("checked");
    extern const QString attr_disabled          = LSTR("disabled");


    extern const QString type_radio             = LSTR("radio");
    extern const QString type_checkbox            = LSTR("checkbox");
}
