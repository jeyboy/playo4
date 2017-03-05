#include "html_keys.h"

namespace Html {
    extern const QByteArray tag_doctype            = HTML_TAG_DOCTYPE;
    extern const QByteArray tag_input              = HTML_TAG_INPUT;
    extern const QByteArray tag_select             = HTML_TAG_SELECT;
    extern const QByteArray tag_textarea           = HTML_TAG_TEXTAREA;
    extern const QByteArray tag_img                = HTML_TAG_IMG;
    extern const QByteArray tag_br                 = HTML_TAG_BR;
    extern const QByteArray tag_a                  = HTML_TAG_A;
    extern const QByteArray tag_script             = HTML_TAG_SCRIPT;
    extern const QByteArray tag_style              = HTML_TAG_STYLE;
    extern const QByteArray tag_head               = HTML_TAG_HEAD;
    extern const QByteArray tag_body               = HTML_TAG_BODY;
    extern const QByteArray tag_meta               = HTML_TAG_META;
    extern const QByteArray tag_xml                = HTML_TAG_XML;
    extern const QByteArray tag_link               = HTML_TAG_LINK;
    extern const QByteArray tag_iframe             = HTML_TAG_IFRAME;

//    extern const char tkn_split                    = ' ';
    extern const QByteArray tkn_any_elem           = HTML_ANY_TAG;
    extern const QByteArray tkn_text_block         = HTML_TEXT_BLOCK;
    extern const QByteArray tkn_comment_block      = QByteArrayLiteral("comment");

    extern const QByteArray tkn_charset            = QByteArrayLiteral("charset");
    extern const QByteArray tkn_encoding           = QByteArrayLiteral("encoding");
    extern const QByteArray tkn_charset_attr       = QByteArrayLiteral("charset=");
    extern const QByteArray tkn_http_equiv         = QByteArrayLiteral("http-equiv");
    extern const QByteArray tkn_content_type       = QByteArrayLiteral("content-type");
    extern const QByteArray tkn_content            = QByteArrayLiteral("content");


    extern const QByteArray tkn_scdata             = QByteArrayLiteral("![CDATA[");
    extern const QByteArray tkn_ecdata             = QByteArrayLiteral("]]>");

    extern const QByteArray attr_name              = QByteArrayLiteral("name");
    extern const QByteArray attr_action            = QByteArrayLiteral("action");
    extern const QByteArray attr_href              = QByteArrayLiteral("href");
    extern const QByteArray attr_src               = QByteArrayLiteral("src");
    extern const QByteArray attr_id                = QByteArrayLiteral("id");
    extern const QByteArray attr_class             = QByteArrayLiteral("class");
    extern const QByteArray attr_type              = HTML_ATTR_TYPE;
    extern const QByteArray attr_default           = QByteArrayLiteral("value");
    extern const QByteArray attr_checked           = QByteArrayLiteral("checked");
    extern const QByteArray attr_disabled          = QByteArrayLiteral("disabled");




    extern const QByteArray type_radio             = QByteArrayLiteral("radio");
    extern const QByteArray type_checkbox          = QByteArrayLiteral("checkbox");
}
