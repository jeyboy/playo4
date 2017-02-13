#include <QString>
#include <QtTest>

#include "html_page.h"

#include "test_data.h"

class HtmlTest : public QObject {
    Q_OBJECT
public:
    HtmlTest();

private Q_SLOTS:
    void measurementSelectionParsing();

    void measurementParsing();
    void measurementSelection();

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
    void testElementAttrsWithoutQuotesExtraction();

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

    void testSelectionAnyRelation();

    void testSelectionPrevParent();
    void testSelectionOnlyChilds();

    void testSelectionPrevSibling();
    void testSelectionNextSibling();
    void testSelectionAnySibling();

    void testSelectionId();
    void testSelectionMultipleClasses();

    void testSelectionMultipleAttrs();

    void testSelectionPosLimit();

    void testSelectionTextEqualTo();
    void testSelectionTextStartedWith();
    void testSelectionTextEndedWith();
    void testSelectionTextContains();
    void testSelectionTextNotContains();

    void testSelectionClassesEqualTo();
    void testSelectionClassesStartedWith();
    void testSelectionClassesEndedWith();
    void testSelectionClassesContains();
    void testSelectionClassesNotContains();
};

using namespace Html;

HtmlTest::HtmlTest() {}

void HtmlTest::measurementSelectionParsing() {
    QBENCHMARK { Selector(TestData::dataSelectorParsingHuge()); }
}

void HtmlTest::measurementParsing() {
//    QString html_data = TestData::dataHtmlFourshared();
    QString html_data = TestData::dataHtmlYoutube();
    QBENCHMARK { Page(html_data.toUtf8().constData()); }
}

void HtmlTest::measurementSelection() {
    Page page(TestData::dataHtmlFourshared());
    QBENCHMARK { page.find(".row"); }
}

void HtmlTest::testHtmlDoctype() {
    Page page(TestData::dataHtmlParserAttrs());
    QVERIFY2(!page.isXml(), "Failure");
}
void HtmlTest::testXmlDoctype() {
    Page page(TestData::dataXmlParser());
    QVERIFY2(page.isXml(), "Failure");
}

void HtmlTest::testHtmlBaseTemplate() {
    Page page(TestData::dataHtmlParserBaseTemplate());
    Tag * h1_tag = page.findFirst("h1");
    Tag * p_tag = page.findFirst("p");

    QVERIFY2(
        h1_tag -> text() == QByteArray("My First Heading") &&
            p_tag -> text() == QByteArray("My first paragraph."),
        "Failure"
    );
}
void HtmlTest::testHtmlShortTemplate() {
    Page page(TestData::dataHtmlParserShortTemplate());
    Tag * title_tag = page.findFirst("title");
    Tag * h1_tag = page.findFirst("h1");
    Tag * p_tag = page.findFirst("p");

    QVERIFY2(
        title_tag -> text() == QByteArray("Page Title") &&
            h1_tag -> text() == QByteArray("This is a heading") &&
            p_tag -> text() == QByteArray("This is a paragraph."),
        "Failure"
    );
}

void HtmlTest::testCoding1251() {
    Page page(TestData::dataHtmlParserCoding1251());
    QVERIFY2(page.charsetType() == Page::charset_cp1251, "Failure");
}
void HtmlTest::testCoding1251Decode() {
    Page page(TestData::dataHtmlParserCoding1251());
    Tag * title_tag = page.findFirst("title");

    QVERIFY2(
        title_tag && title_tag -> text() == QByteArray("Кодировка"),
        "Failure"
    );
}

void HtmlTest::testCodingUtf8() {
    Page page(TestData::dataHtmlParserCodingUtf8());
    QVERIFY2(page.charsetType() == Page::charset_utf8, "Failure");
}
void HtmlTest::testCodingUtf8Decode() {
    Page page(TestData::dataHtmlParserCodingUtf8());
    Tag * title_tag = page.findFirst("title");
    QVERIFY2(
        title_tag && title_tag -> text() == QByteArrayLiteral("My First HTML"),
        "Failure"
    );
}

void HtmlTest::testJS() {
    Page page(TestData::dataHtmlParserJs2());
    Set script_tags = page.find("script");

    QVERIFY2(
        script_tags.size() == 1 &&
        script_tags.first() -> text() == QByteArray("function myFunction() {document.getElementById(\"demo\").innerHTML = \"Hello JavaScript!\";}"),
        "Failure"
    );
}
//void HtmlTest::testCDATAJs() {
//    Page page(TestData::dataHtmlParserCdataJs());

//}
void HtmlTest::testCDATAHtml() {
    Page page(TestData::dataHtmlParserCdataHtml());
    Tag * div = page.findFirst("div");

    QVERIFY2(
        div &&
        div -> childrenCount() == 0,
        "Failure"
    );
}

void HtmlTest::testElementTextExtraction() {
    Page page(TestData::dataHtmlParserAttrs());
    Tag * h2_tag = page.findFirst("h2");

    QVERIFY2(h2_tag && h2_tag -> text() == QByteArray("The title attribute"), "Failure");
}
void HtmlTest::testElementAttrsExtraction() {
    Page page(TestData::dataHtmlParserAttrs());
    Tag * p_tag = page.findFirst("p");

    QVERIFY2(
        p_tag && p_tag -> value("title") == QByteArray("I'm a tooltip"),
        "Failure"
    );
}
void HtmlTest::testElementAttrsWithoutQuotesExtraction() {
    Page page(TestData::dataHtmlParserAttrsWithoutQuotes());
    Tag * a_tag = page.findFirst("a");

    QVERIFY2(
        a_tag &&
            a_tag -> link() == QByteArray("http://www.w3schools.com") &&
            a_tag -> text() == QByteArray("This is a link"),
        "Failure"
    );
}

void HtmlTest::testElementClasses() {
    Page page(TestData::dataHtmlParserClasses());
    QByteArray cl1_cl2("cl1 cl2 classes");
    QByteArray cl2_cl3("cl2 cl3 classes");

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
    Page page(TestData::dataHtmlParserClasses());
    Set tags = page.find("#blia");

    QVERIFY2(
        tags.size() == 1 && tags.first() -> name() == LSTR("p"),
        "Failure"
    );
}


void HtmlTest::testFormCheckboxes() {
    Page page(TestData::dataHtmlParserCheckboxes());
    Tag * form_tag = page.findFirst("form");

    QUrl url = form_tag -> serializeFormToUrl();
    QUrlQuery query(url.query());

    QStringList vehicles = query.allQueryItemValues(LSTR("vehicle"));
    QVERIFY2(
        vehicles.size() == 2 &&
        vehicles.first() == LSTR("Bike") && vehicles.last() == LSTR("Ship"),
        "Failure"
    );
}
void HtmlTest::testFormRadio() {
    Page page(TestData::dataHtmlParserRadios());
    Tag * form_tag = page.findFirst("form");

    QUrl url = form_tag -> serializeFormToUrl();
    QUrlQuery query(url.query());

    QStringList browsers = query.allQueryItemValues(LSTR("browser"));
    QVERIFY2(
        browsers.size() == 1 &&
        browsers.first() == LSTR("opera"),
        "Failure"
    );
}
void HtmlTest::testFormSelect() {
    Page page(TestData::dataHtmlParserSelects());
    Tag * form_tag = page.findFirst("form");

    QUrl url = form_tag -> serializeFormToUrl();
    QUrlQuery query(url.query());

    QString car = query.queryItemValue(LSTR("cars"));

    QVERIFY2(
        car == LSTR("fiat"),
        "Failure"
    );
}
void HtmlTest::testFormText() {
    Page page(TestData::dataHtmlParserTexts());
    Tag * form_tag = page.findFirst("form");

    QUrl url = form_tag -> serializeFormToUrl();
    QUrlQuery query(url.query());

    QString name = query.queryItemValue(LSTR("lastname"));

    QVERIFY2(
        name == LSTR("Mouse"),
        "Failure"
    );
}
void HtmlTest::testFormTextArea() {
    Page page(TestData::dataHtmlParserTexts());
    Tag * form_tag = page.findFirst("form");

    QUrl url = form_tag -> serializeFormToUrl();
    QUrlQuery query(url.query());

    QString comment = query.queryItemValue(LSTR("comment"));
    QVERIFY2(
        comment == LSTR("Some sheety text"),
        "Failure"
    );
}

void HtmlTest::testIframe() {
    Page page(TestData::dataHtmlParserIFrame());

    QVERIFY2(
        false,
        "Failure"
    );
}


void HtmlTest::testSelectionAnyRelation() {
    Page page(TestData::dataHtmlStackOverflow());
    Tag * div = page.findFirst("body .topbar");

    QVERIFY2(div && div -> hasClass("topbar"), "Failure");
}

void HtmlTest::testSelectionPrevParent() {
    Page page(TestData::dataHtmlStackOverflow());
    Tag * div = page.findFirst(".js-gps-track < .modal-content");

    QVERIFY2(div && div -> hasClass("modal-content"), "Failure");
}
void HtmlTest::testSelectionOnlyChilds() {
    Page page(TestData::dataHtmlStackOverflow());
    Set bar_as = page.find(".topbar > div");

    Tag * topbar = page.findFirst(".topbar");
    bool res = !bar_as.isEmpty();

    for(Set::Iterator tag = bar_as.begin(); tag != bar_as.end(); tag++)
        if ((*tag) -> parent() != topbar) {
            res = false;
            break;
        }

    QVERIFY2(res, "Failure");
}

void HtmlTest::testSelectionPrevSibling() {
    Page page(TestData::dataHtmlStackOverflow());
    Tag * div = page.findFirst("#custom-header - div");

    QVERIFY2(div && div -> hasId("notify-container"), "Failure");
}
void HtmlTest::testSelectionNextSibling() {
    Page page(TestData::dataHtmlStackOverflow());
    Tag * div = page.findFirst("#notify-container + div");

    QVERIFY2(div && div -> hasId("custom-header"), "Failure");
}
void HtmlTest::testSelectionAnySibling() {
    Page page(TestData::dataHtmlStackOverflow());
    Set bars = page.find("body ~ .topbar");

    QVERIFY2(bars.size() == 1 && bars.first() -> hasClass("topbar"), "Failure");
}

void HtmlTest::testSelectionId() {
    Page page(TestData::dataHtmlStackOverflow());
    Set divs = page.find("body #your-communities-header");
    QVERIFY2(divs.size() == 1 && divs.first() -> hasId("your-communities-header"), "Failure");
}
void HtmlTest::testSelectionMultipleClasses() {
    Page page(TestData::dataHtmlStackOverflow());
    Tag * as = page.findFirst(".current-site-link.site-link.js-gps-track");

    QVERIFY2(as && as -> hasClass("site-link"), "Failure");
}

void HtmlTest::testSelectionMultipleAttrs() {
    Page page(TestData::dataHtmlStackOverflow());
    Tag * as = page.findFirst("a[data-gps-track='site_switcher.show'][title='A list of all 163 Stack Exchange sites']");

    QVERIFY2(as && as -> hasAttr("data-gps-track"), "Failure");
}

void HtmlTest::testSelectionPosLimit() {
    Page page(TestData::dataHtmlStackOverflow());
    Tag * div = page.findFirst("body > :4");

    QVERIFY2(div && div -> hasId("notify-container"), "Failure");
}

void HtmlTest::testSelectionTextEqualTo() {
    Page page(TestData::dataHtmlParserAttrs());
    Tag * div = page.findFirst("[text='The title attribute']");

    QVERIFY2(div, "Failure");
}
void HtmlTest::testSelectionTextStartedWith() {
    Page page(TestData::dataHtmlParserAttrs());
    Set tags = page.find("[text^'The']");

    QVERIFY2(tags.size() == 2, "Failure");
}
void HtmlTest::testSelectionTextEndedWith() {
    Page page(TestData::dataHtmlParserAttrs());
    Set tags = page.find("[text$'bute']");

    QVERIFY2(tags.size() == 2, "Failure");
}
void HtmlTest::testSelectionTextContains() {
    Page page(TestData::dataHtmlParserAttrs());
    Set tags = page.find("[text~'title']");

    QVERIFY2(tags.size() == 2, "Failure");
}
void HtmlTest::testSelectionTextNotContains() {
    Page page(TestData::dataHtmlParserAttrs());
    Set tags = page.find("body [text!'title']");

    QVERIFY2(tags.size() == 2, "Failure");
}

void HtmlTest::testSelectionClassesEqualTo() {
    //    Page page(TestData::dataHtmlStackOverflow());
    //    Tag * div = page.findFirst("body .topbar :2");

        QVERIFY2(false, "Failure");
}
void HtmlTest::testSelectionClassesStartedWith() {
    //    Page page(TestData::dataHtmlStackOverflow());
    //    Tag * div = page.findFirst("body .topbar :2");

        QVERIFY2(false, "Failure");
}
void HtmlTest::testSelectionClassesEndedWith() {
    //    Page page(TestData::dataHtmlStackOverflow());
    //    Tag * div = page.findFirst("body .topbar :2");

        QVERIFY2(false, "Failure");
}
void HtmlTest::testSelectionClassesContains() {
    //    Page page(TestData::dataHtmlStackOverflow());
    //    Tag * div = page.findFirst("body .topbar :2");

        QVERIFY2(false, "Failure");
}
void HtmlTest::testSelectionClassesNotContains() {
    //    Page page(TestData::dataHtmlStackOverflow());
    //    Tag * div = page.findFirst("body .topbar :2");

        QVERIFY2(false, "Failure");
}


QTEST_APPLESS_MAIN(HtmlTest)

#include "main.moc"
