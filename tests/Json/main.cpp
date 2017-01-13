#include <QString>
#include <QtTest>

#include <json.h>

#define INT_KEY 'i'
#define STR_KEY 's'
#define PAIR_KEY 'p'

class JsonTest : public QObject {
    Q_OBJECT

public:
    JsonTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void Parsing_data();
    void Parsing();
};

JsonTest::JsonTest() {}

void JsonTest::initTestCase() {}

void JsonTest::cleanupTestCase() {}

void JsonTest::Parsing_data() {
    QTest::addColumn<QString>("json");
    QTest::addColumn<QStringList>("keys");
    QTest::addColumn<QString>("val");
    QTest::addColumn<bool>("has_error");

//    QTest::newRow("0") << QString("{a: 1, b: 'sdfsf'}");

    QString root_key = LSTR("colors");
    QString key = QStringLiteral("colorVal");
    QString val = QStringLiteral("#f00");

    QTest::newRow("Usuall obj")
        << QString(
            "{"
            "   \"colorName\":\"red\","
            "   \"" % key % "\":\"" % val % "\""
            "}"
        )
        << (QStringList() << QString(STR_KEY % key))
        << val
        << false;

    QTest::newRow("Sub obj")
        << QString(
            "{"
            "   \"" % root_key % "\":{"
            "       \"colorName\":\"red\","
            "       \"" % key % "\":\"" % val % "\""
            "   }"
            "}"
        )
        << (QStringList() << QString(STR_KEY % root_key) << QString(STR_KEY % key))
        << val
        << false;

    QTest::newRow("Usuall arr")
        << QString(
            "["
            "   {"
            "       \"colorName\":\"red\","
            "       \"" % key % "\":\"" % val % "\""
            "   }"
            "]"
        )
        << (QStringList() << QString(INT_KEY % QString::number(0)) << QString(STR_KEY % key))
        << val
        << false;


    QTest::newRow("Sub arr")
        << QString(
            "["
            "   ["
            "       \"red\","
            "       \"" % val % "\""
            "   ]"
            "]"
        )
        << (QStringList() << QString(INT_KEY % QString::number(0)) << QString(INT_KEY % QString::number(1)))
        << val
        << false;

    QTest::newRow("Wrong json")
        << QString(
            "["
            "   ["
            "       \"red\""
            "       \"" % val % "\""
            "   ]"
            "]"
        )
        << (QStringList() << QString(INT_KEY % QString::number(0)) << QString(INT_KEY % QString::number(1)))
        << val
        << true;
}

void JsonTest::Parsing() {
    QFETCH(QString, json);
    QFETCH(QStringList, keys);
    QFETCH(QString, val);
    QFETCH(bool, has_error);

    QString error_str;
    Json json_obj = Json::fromText(json, error_str);
    qDebug() << "ERROR" << error_str;

    for(QStringList::Iterator key = keys.begin(); key != keys.end(); key++) {
        if ((*key)[0] == INT_KEY)
            json_obj = json_obj[(*key).mid(1).toInt()];
        else
            json_obj = json_obj[(*key).mid(1)];
    }

    bool errorable = has_error && !error_str.isEmpty();
    QVERIFY2(errorable || (!errorable && json_obj.toString() == val), "Failure");
}


QTEST_APPLESS_MAIN(JsonTest)

#include "main.moc"
