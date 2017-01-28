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

    void testCoding1251();
    void testCoding1251Decode();

    void testCodingUtf8();
    void testCodingUtf8Decode();

    void testElementTextExtraction();
    void testElementAttrsExtraction();
    void testElementAttrsWithoutQuotasExtraction();
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

    QVERIFY2(
        a_tag &&
            a_tag -> link() == QStringLiteral("http://www.w3schools.com") &&
            a_tag -> text() == QStringLiteral("This is a link"),
        "Failure"
    );
}






QTEST_APPLESS_MAIN(HtmlTest)

#include "main.moc"
