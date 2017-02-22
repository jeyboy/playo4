#include "html_keys.h"

namespace Html {
    extern const QByteArray tag_doctype            = HTML_DOCTYPE_TAG;
    extern const QByteArray tag_input              = HTML_INPUT_TAG;
    extern const QByteArray tag_select             = QByteArray("select");
    extern const QByteArray tag_textarea           = QByteArray("textarea");
    extern const QByteArray tag_img                = HTML_IMG_TAG;
    extern const QByteArray tag_br                 = HTML_BR_TAG;
    extern const QByteArray tag_a                  = QByteArray("a");
    extern const QByteArray tag_script             = QByteArray("script");
    extern const QByteArray tag_style              = QByteArray("style");
    extern const QByteArray tag_head               = QByteArray("head");
    extern const QByteArray tag_body               = QByteArray("body");
    extern const QByteArray tag_meta               = HTML_META_TAG;
    extern const QByteArray tag_xml                = HTML_XML_TAG;
    extern const QByteArray tag_link               = HTML_LINK_TAG;
    extern const QByteArray tag_iframe             = QByteArray("iframe");

//    extern const char tkn_split                    = ' ';
    extern const QByteArray tkn_any_elem           = HTML_ANY_TAG;
    extern const QByteArray tkn_text_block         = QByteArray("text");
    extern const QByteArray tkn_comment_block      = QByteArray("comment");

    extern const QByteArray tkn_charset            = QByteArray("charset");
    extern const QByteArray tkn_encoding           = QByteArray("encoding");
    extern const QByteArray tkn_charset_attr       = QByteArray("charset=");
    extern const QByteArray tkn_http_equiv         = QByteArray("http-equiv");
    extern const QByteArray tkn_content_type       = QByteArray("content-type");
    extern const QByteArray tkn_content            = QByteArray("content");


    extern const QByteArray tkn_scdata             = QByteArray("![CDATA[");
    extern const QByteArray tkn_ecdata             = QByteArray("]]>");

    extern const QByteArray attr_name              = QByteArray("name");
    extern const QByteArray attr_action            = QByteArray("action");
    extern const QByteArray attr_href              = QByteArray("href");
    extern const QByteArray attr_src               = QByteArray("src");
    extern const QByteArray attr_id                = QByteArray("id");
    extern const QByteArray attr_class             = QByteArray("class");
    extern const QByteArray attr_type              = HTML_ATTR_TYPE;
    extern const QByteArray attr_default           = QByteArray("value");
    extern const QByteArray attr_checked           = QByteArray("checked");
    extern const QByteArray attr_disabled          = QByteArray("disabled");




    extern const QByteArray type_radio             = QByteArray("radio");
    extern const QByteArray type_checkbox          = QByteArray("checkbox");
}
