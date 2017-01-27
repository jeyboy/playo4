#include <QString>
#include <QtTest>

#include <html_page.h>

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
    void testCoding1251();
    void testCodingUtf8();
    void testElementAttrsExtraction();
    void testElementAttrsWtoutQuotasExtraction();
};

using namespace Html;

HtmlTest::HtmlTest() {}

void HtmlTest::testCoding1251() {
    QString data = loadData(TEST_CODING_1251_PATH);
    qDebug() << data;

    Page page(data);
    Tag * title_tag = page.findFirst("title");

    QVERIFY2(title_tag && title_tag -> text() == QStringLiteral("Кодировка"), "Failure");
}

void HtmlTest::testCodingUtf8() {
    qDebug() << loadData(TEST_CODING_UTF8_PATH);

    QVERIFY2(true, "Failure");
}

void HtmlTest::testElementAttrsExtraction() {
    qDebug() << loadData(TEST_ELEM_ATTRS_PATH);

    QVERIFY2(true, "Failure");
}

void HtmlTest::testElementAttrsWtoutQuotasExtraction() {
    qDebug() << loadData(TEST_ELEM_ATTRS_WITOUT_QUOTAS_PATH);

    QVERIFY2(true, "Failure");
}






QTEST_APPLESS_MAIN(HtmlTest)

#include "main.moc"
