#include <QString>
#include <QtTest>

#include "test_data.h"

class HtmlTest : public QObject {
    Q_OBJECT

public:
    HtmlTest();

private Q_SLOTS:
    void testCase1();
};

HtmlTest::HtmlTest() {}

void HtmlTest::testCase1() {
    QVERIFY2(true, "Failure");
}


QTEST_APPLESS_MAIN(HtmlTest)

#include "main.moc"
