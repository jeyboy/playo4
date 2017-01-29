#ifndef TEST_DATA_H
#define TEST_DATA_H

#include <qfile.h>
#include <qstringbuilder.h>
#include <qdebug.h>

#define DATA_PATH(name) SRCDIR % QStringLiteral("test_data/") % name

#define TEST_FOURSHARED_PATH DATA_PATH(QStringLiteral("fourshared.txt"))
#define TEST_GOOGLE_PATH DATA_PATH(QStringLiteral("google.txt"))

#define TEST_XML_PATH DATA_PATH(QStringLiteral("test_xml.txt"))

#define TEST_CODING_1251_PATH DATA_PATH(QStringLiteral("test_1251_head.txt"))
#define TEST_CODING_UTF8_PATH DATA_PATH(QStringLiteral("test_utf8_head.txt"))

#define TEST_ELEM_ATTRS_PATH DATA_PATH(QStringLiteral("test_attr.txt"))
#define TEST_ELEM_ATTRS_WITOUT_QUOTAS_PATH DATA_PATH(QStringLiteral("test_attr_without_quotas.txt"))

#define TEST_BASE_TEMPLATE_PATH DATA_PATH(QStringLiteral("test_base_template.txt"))
#define TEST_BASE_SHORT_TEMPLATE_PATH DATA_PATH(QStringLiteral("test_base_short_template.txt"))

#define TEST_CLASSES_PATH DATA_PATH(QStringLiteral("test_classes.txt"))

#define TEST_CONDITIONAL_COMMENTS_PATH DATA_PATH(QStringLiteral("test_conditional_comments.txt"))
#define TEST_HIDDEN_COMMENTS_PATH DATA_PATH(QStringLiteral("test_hidden_comments.txt"))

#define TEST_JS_PATH DATA_PATH(QStringLiteral("test_js.txt"))
#define TEST_JS_CDATA_PATH DATA_PATH(QStringLiteral("test_js_cdata.txt"))

#define TEST_EMAIL_FORM_PATH DATA_PATH(QStringLiteral("test_email_form.txt"))
#define TEST_POST_FORM_DATALIST_PATH DATA_PATH(QStringLiteral("test_post_form_datalist.txt"))
#define TEST_POST_FORM_SELECT_PATH DATA_PATH(QStringLiteral("test_post_form_select.txt"))
#define TEST_POST_FORM_TEXT_PATH DATA_PATH(QStringLiteral("test_post_form_text.txt"))

#define TEST_IFRAME_PATH DATA_PATH(QStringLiteral("test_iframe.txt"))
#define TEST_TABLE_PATH DATA_PATH(QStringLiteral("test_table.txt"))
#define TEST_VIDEO_HTML5_PATH DATA_PATH(QStringLiteral("test_video_html5.txt"))

#endif // TEST_DATA_H
