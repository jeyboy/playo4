#include <QString>
#include <QtTest>

#include "html_page.h"

#include "test_data.h"

class HtmlTest : public QObject {
    Q_OBJECT

    QString loadData(const QString & path) {
        QString res;
        QFile f(path);
        if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
            res = f.readAll();
            f.close();
        }
        else qDebug() << "Error file opening" << path;

        return res;
    }
public:
    HtmlTest();

private Q_SLOTS:
    void testHtmlDoctype();
    void testXmlDoctype();

    void testHtmlBaseTemplate();
    void testHtmlShortTemplate();

    void testCoding1251();
    void testCoding1251Decode();

    void testCodingUtf8();
    void testCodingUtf8Decode();

    void testJS();
//    void testCDATAJs();
    void testCDATAHtml();

    void testElementTextExtraction();
    void testElementAttrsExtraction();
    void testElementAttrsWithoutQuotasExtraction();

    void testElementClasses();
    void testElementId();

    void testFormCheckboxes();
    void testFormRadio();
    void testFormSelect();
    void testFormText();
    void testFormTextArea();

    void testIframe();
//    void testTable(); //TEST_TABLE_PATH
//    void testVideo(); //TEST_VIDEO_HTML5_PATH
};

using namespace Html;

HtmlTest::HtmlTest() {}

void HtmlTest::testHtmlDoctype() {
    Page page(loadData(TEST_ELEM_ATTRS_PATH));
    QVERIFY2(!page.isXml(), "Failure");
}
void HtmlTest::testXmlDoctype() {
    Page page(loadData(TEST_XML_PATH));
    QVERIFY2(page.isXml(), "Failure");
}

void HtmlTest::testHtmlBaseTemplate() {
    Page page(loadData(TEST_BASE_TEMPLATE_PATH));
    Tag * h1_tag = page.findFirst("h1");
    Tag * p_tag = page.findFirst("p");

    QVERIFY2(
        h1_tag -> text() == QStringLiteral("My First Heading") &&
            p_tag -> text() == QStringLiteral("My first paragraph."),
        "Failure"
    );
}
void HtmlTest::testHtmlShortTemplate() {
    Page page(loadData(TEST_BASE_SHORT_TEMPLATE_PATH));
    Tag * title_tag = page.findFirst("title");
    Tag * h1_tag = page.findFirst("h1");
    Tag * p_tag = page.findFirst("p");

    QVERIFY2(
        title_tag -> text() == QStringLiteral("Page Title") &&
            h1_tag -> text() == QStringLiteral("This is a heading") &&
            p_tag -> text() == QStringLiteral("This is a paragraph."),
        "Failure"
    );
}

void HtmlTest::testCoding1251() {
    Page page(loadData(TEST_CODING_1251_PATH));
    QVERIFY2(page.charsetType() == Page::charset_cp1251, "Failure");
}
void HtmlTest::testCoding1251Decode() {
    Page page(loadData(TEST_CODING_1251_PATH));
    Tag * title_tag = page.findFirst("title");

    QVERIFY2(
        title_tag && title_tag -> text() == QStringLiteral("Кодировка"),
        "Failure"
    );
}

void HtmlTest::testCodingUtf8() {
    Page page(loadData(TEST_CODING_UTF8_PATH));
    QVERIFY2(page.charsetType() == Page::charset_utf8, "Failure");
}
void HtmlTest::testCodingUtf8Decode() {
    Page page(loadData(TEST_CODING_UTF8_PATH));
    Tag * title_tag = page.findFirst("title");
    QVERIFY2(
        title_tag && title_tag -> text() == QStringLiteral("My First HTML"),
        "Failure"
    );
}

void HtmlTest::testJS() {
    Page page(loadData(TEST_JS_PATH));
    Set script_tags = page.find("script");

    QVERIFY2(
        script_tags.size() == 1 &&
        script_tags.first() -> text() == QStringLiteral("function myFunction() {document.getElementById(\"demo\").innerHTML = \"Hello JavaScript!\";}"),
        "Failure"
    );
}
//void HtmlTest::testCDATAJs() {
//    Page page(loadData(TEST_CDATA_JS_PATH));

//}
void HtmlTest::testCDATAHtml() {
    Page page(loadData(TEST_CDATA_HTML_PATH));
    Tag * div = page.findFirst("div");

    QVERIFY2(
        div &&
        div -> childrenCount() == 0,
        "Failure"
    );
}

void HtmlTest::testElementTextExtraction() {
    Page page(loadData(TEST_ELEM_ATTRS_PATH));
    Tag * h2_tag = page.findFirst("h2");

    QVERIFY2(h2_tag && h2_tag -> text() == QStringLiteral("The title attribute"), "Failure");
}
void HtmlTest::testElementAttrsExtraction() {
    Page page(loadData(TEST_ELEM_ATTRS_PATH));
    Tag * p_tag = page.findFirst("p");

    QVERIFY2(
        p_tag && p_tag -> value(QStringLiteral("title")) == QStringLiteral("I'm a tooltip"),
        "Failure"
    );
}
void HtmlTest::testElementAttrsWithoutQuotasExtraction() {
    Page page(loadData(TEST_ELEM_ATTRS_WITOUT_QUOTAS_PATH));
    Tag * a_tag = page.findFirst("a");

    qDebug() << a_tag;

    QVERIFY2(
        a_tag &&
            a_tag -> link() == QStringLiteral("http://www.w3schools.com") &&
            a_tag -> text() == QStringLiteral("This is a link"),
        "Failure"
    );
}

void HtmlTest::testElementClasses() {
    Page page(loadData(TEST_CLASSES_PATH));
    QString cl1_cl2("cl1 cl2 classes");
    QString cl2_cl3("cl2 cl3 classes");

    Set cl1_tags = page.find(".cl1");
    Set cl2_tags = page.find(".cl2");
    Set cl3_tags = page.find(".cl3");

    bool cl1_tags_valid = cl1_tags.size() == 1 && cl1_tags.first() -> text() == cl1_cl2;
    bool cl2_tags_valid = cl2_tags.size() == 2 && cl2_tags.first() -> text() == cl1_cl2 && cl2_tags.last() -> text() == cl2_cl3;
    bool cl3_tags_valid = cl3_tags.size() == 1 && cl3_tags.first() -> text() == cl2_cl3;

    QVERIFY2(
        cl1_tags_valid && cl2_tags_valid && cl3_tags_valid,
        "Failure"
    );
}
void HtmlTest::testElementId() {
    Page page(loadData(TEST_CLASSES_PATH));
    Set tags = page.find("#blia");

    QVERIFY2(
        tags.size() == 1 && tags.first() -> name() == QStringLiteral("p"),
        "Failure"
    );
}


void HtmlTest::testFormCheckboxes() {
    Page page(loadData(TEST_POST_FORM_CHECKBOX_PATH));
    Tag * form_tag = page.findFirst("form");

    QUrl url = form_tag -> serializeFormToUrl();
    QUrlQuery query(url.query());

    QString vehicles = query.queryItemValue(QStringLiteral("vehicle"));
    qDebug() << vehicles;

    QVERIFY2(
        vehicles.contains(QStringLiteral("Bike")) && vehicles.contains(QStringLiteral("Ship")),
        "Failure"
    );
}
void HtmlTest::testFormRadio() {
    Page page(loadData(TEST_POST_FORM_RADIO_PATH));
    Tag * form_tag = page.findFirst("form");

    QUrl url = form_tag -> serializeFormToUrl();
    QUrlQuery query(url.query());

    QString browser = query.queryItemValue(QStringLiteral("browser"));
    qDebug() << browser;

    QVERIFY2(
        browser == QStringLiteral("opera"),
        "Failure"
    );
}
void HtmlTest::testFormSelect() {
    Page page(loadData(TEST_POST_FORM_SELECT_PATH));
    Tag * form_tag = page.findFirst("form");

    QUrl url = form_tag -> serializeFormToUrl();
    QUrlQuery query(url.query());

    QString car = query.queryItemValue(QStringLiteral("cars"));

    QVERIFY2(
        car == QStringLiteral("fiat"),
        "Failure"
    );
}
void HtmlTest::testFormText() {
    Page page(loadData(TEST_POST_FORM_TEXT_PATH));
    Tag * form_tag = page.findFirst("form");

    QUrl url = form_tag -> serializeFormToUrl();
    QUrlQuery query(url.query());

    QString name = query.queryItemValue(QStringLiteral("lastname"));

    QVERIFY2(
        name == QStringLiteral("Mouse"),
        "Failure"
    );
}
void HtmlTest::testFormTextArea() {
    Page page(loadData(TEST_POST_FORM_TEXT_PATH));
    Tag * form_tag = page.findFirst("form");

    QUrl url = form_tag -> serializeFormToUrl();
    QUrlQuery query(url.query());

    QString comment = query.queryItemValue(QStringLiteral("comment"));
    qDebug() << comment;

    QVERIFY2(
        comment == QStringLiteral("Some sheety text"),
        "Failure"
    );
}

void HtmlTest::testIframe() {
    Page page(loadData(TEST_IFRAME_PATH));

    QVERIFY2(
        false,
        "Failure"
    );
}


QTEST_APPLESS_MAIN(HtmlTest)

#include "main.moc"
