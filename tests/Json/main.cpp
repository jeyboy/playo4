#include <QString>
#include <QtTest>

class JsonTest : public QObject {
    Q_OBJECT

public:
    JsonTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1_data();
    void testCase1();
};

JsonTest::JsonTest() {
}

void JsonTest::initTestCase() {
}

void JsonTest::cleanupTestCase() {
}

void JsonTest::testCase1_data() {
    QTest::addColumn<QString>("data");
    QTest::newRow("0") << QString();
}

void JsonTest::testCase1() {
    QFETCH(QString, data);
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(JsonTest)

#include "main.moc"
