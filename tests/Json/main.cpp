#include <QString>
#include <QtTest>

#include <json.h>
#include <json_obj.h>
#include <json_arr.h>

#define INT_KEY 'i'
#define STR_KEY 's'


#define TJSON_OBJ(key, val) \
    QString(\
        "{"\
        "   \"colorName\":\"red\","\
        "   \"" % key % "\":\"" % val % "\""\
        "}"\
    )

#define TJSON_SUB_OBJ(root_key, key, val) \
    QString(\
        "{"\
        "   \"" % root_key % "\":{"\
        "       \"colorName\":\"red\","\
        "       \"" % key % "\":\"" % val % "\""\
        "   }"\
        "}"\
    )

#define TJSON_ARR(val) \
    QString(\
        "["\
        "   \"" % val % "\""\
        "]"\
    )

#define TJSON_SUB_ARR(key, val) \
    QString(\
        "["\
        "   ["\
        "       \"red\","\
        "       \"" % val % "\""\
        "   ]"\
        "]"\
    )

#define TJSON_OBJ_SUB_ARR(root_key, val) \
    QString(\
        "{"\
        "   \"" % root_key % "\":["\
        "       \"red\","\
        "       \"" % val % "\""\
        "   ]"\
        "}"\
    )

#define TJSON_ARR_SUB_OBJ(key, val) \
    QString(\
        "["\
        "   {"\
        "       \"colorName\":\"red\","\
        "       \"" % key % "\":\"" % val % "\""\
        "   }"\
        "]"\
    )


class JsonTest : public QObject {
    Q_OBJECT
public:
    JsonTest();

private Q_SLOTS:
    void parsing_data();
    void parsing();

    void parsingChains_data();
    void parsingChains();

    void jsonToString();
    void jsonObjToString();
    void jsonArrToString();
};

JsonTest::JsonTest() {}

void JsonTest::parsing_data() {
    QTest::addColumn<QString>("json");
    QTest::addColumn<QStringList>("keys");
    QTest::addColumn<QString>("val");
    QTest::addColumn<bool>("has_error");

    QString root_key = LSTR("colors");
    QString key = LSTR("colorVal");
    QString val = LSTR("#f00");

    QTest::newRow("Usuall obj")
        << TJSON_OBJ(key, val)
        << (QStringList() << QString(STR_KEY % key))
        << val
        << false;

    QTest::newRow("Sub obj")
        << TJSON_SUB_OBJ(root_key, key, val)
        << (QStringList() << QString(STR_KEY % root_key) << QString(STR_KEY % key))
        << val
        << false;

    QTest::newRow("Usuall arr")
        << TJSON_ARR(val)
        << (QStringList() << QString(INT_KEY % QString::number(0)))
        << val
        << false;


    QTest::newRow("Sub arr")
        << TJSON_SUB_ARR(key, val)
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
void JsonTest::parsing() {
    QFETCH(QString, json);
    QFETCH(QStringList, keys);
    QFETCH(QString, val);
    QFETCH(bool, has_error);

    QString error_output;
    Json json_obj = Json::fromJsonStr(json, error_output);

    for(QStringList::Iterator key = keys.begin(); key != keys.end(); key++) {
        if ((*key)[0] == INT_KEY)
            json_obj = json_obj[(*key).mid(1).toInt()];
        else
            json_obj = json_obj[(*key).mid(1)];
    }

    bool errorable = has_error && !error_output.isEmpty();
    QVERIFY2(errorable || (!errorable && json_obj.toString() == val), "Failure");
}

void JsonTest::parsingChains_data() {
    QTest::addColumn<QString>("json");
    QTest::addColumn<QStringList>("keys");
    QTest::addColumn<QString>("val");


}
void JsonTest::parsingChains() {

}

void JsonTest::jsonToString() {
    QByteArray json_str = TJSON_OBJ(LSTR("genre"), LSTR("pop")).remove(' ').toUtf8();
    Json json_obj = Json::fromJsonStr(json_str);
    QVERIFY2(json_str == json_obj.toJsonStr(), "Failure");
}

void JsonTest::jsonObjToString() {
    QByteArray json_str = TJSON_OBJ(LSTR("genre"), LSTR("pop")).remove(' ').toUtf8();
    JsonObj json_obj = JsonObj::fromJsonStr(json_str);

    qDebug() << json_str;
    qDebug() << json_obj.toJsonStr();

    QVERIFY2(json_str == json_obj.toJsonStr(), "Failure");
}
void JsonTest::jsonArrToString() {
    QByteArray json_str = TJSON_ARR(LSTR("pop")).remove(' ').toUtf8();
    JsonArr json_arr = JsonArr::fromJsonStr(json_str);

    qDebug() << json_str;
    qDebug() << json_arr.toJsonStr();

    QVERIFY2(json_str == json_arr.toJsonStr(), "Failure");
}

//----------------------------

QTEST_APPLESS_MAIN(JsonTest)

#include "main.moc"
