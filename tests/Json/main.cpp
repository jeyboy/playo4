#include <QString>
#include <QtTest>

#include <json.h>
#include <json_obj.h>
#include <json_arr.h>

#include "test_data.h"

class JsonTest : public QObject {
    Q_OBJECT
public:
    JsonTest();

private Q_SLOTS:
    void parsing_data();
    void parsing();

    void sizeJson();
    void sizeObj();
    void sizeArr();

    void hasIndex();
    void hasKey();

    void notHasIndex();
    void notHasKey();

    void bracketsIndex();
    void bracketsKey();

    void valIndex();
    void valKey();

    void val2Index();
    void val2Key();

    void parsingObjChainsStr();
    void parsingArrChainsStr();

    void jsonToString();
    void jsonObjToString();
    void jsonArrToString();

    void jsonStr();
    void jsonBool();
    void jsonInt();
    void jsonInt64();
    void jsonDouble();
    void jsonFStr();
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
        << TJSON_OBJ_KEY(key)
        << val
        << false;

    QTest::newRow("Sub obj")
        << TJSON_SUB_OBJ(root_key, key, val)
        << TJSON_SUB_OBJ_KEY(root_key, key)
        << val
        << false;

    QTest::newRow("Usuall arr")
        << TJSON_ARR(val)
        << TJSON_ARR_KEY
        << val
        << false;


    QTest::newRow("Sub arr")
        << TJSON_SUB_ARR(val)
        << TJSON_SUB_ARR_KEY
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
        << QStringList()
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

void JsonTest::parsingObjChainsStr() {
    QString root_key = LSTR("colors");
    QString key = LSTR("colorVal");
    QString val = LSTR("#f00");

    Json json_obj = Json::fromJsonStr(TJSON_SUB_OBJ(root_key, key, val));
    QVERIFY2(json_obj.string2(root_key, key) == val, "Failure");
}

void JsonTest::parsingArrChainsStr() {
    QString val = LSTR("#f00");

    Json json_obj = Json::fromJsonStr(TJSON_SUB_ARR(val));
    QVERIFY2(json_obj.string2(TJSON_SUB_ARR_KEY_ARGS) == val, "Failure");
}


void JsonTest::sizeJson() {
    Json json_obj = Json::fromJsonStr(TJSON_OBJ(LSTR("colorVal"), LSTR("#f00")));
    QVERIFY2(json_obj.size() == 2, "Failure");
}
void JsonTest::sizeObj() {
    Json json_obj = Json::fromJsonStr(TJSON_OBJ(LSTR("colorVal"), LSTR("#f00")));
    QVERIFY2(json_obj.obj().size() == 2, "Failure");
}
void JsonTest::sizeArr() {
    Json json_obj = Json::fromJsonStr(TJSON_ARR(LSTR("#f00")));
    QVERIFY2(json_obj.arr().size() == 3, "Failure");
}


void JsonTest::hasIndex() {
    Json json_obj = Json::fromJsonStr(TJSON_ARR(LSTR("#f00")));
    QVERIFY2(json_obj.hasIndex(1), "Failure");
}
void JsonTest::hasKey() {
    QString key = LSTR("colorVal");
    QString val = LSTR("#f00");

    Json json_obj = Json::fromJsonStr(TJSON_OBJ(key, val));
    QVERIFY2(json_obj.hasKey(key), "Failure");
}

void JsonTest::notHasIndex() {
    Json json_obj = Json::fromJsonStr(TJSON_ARR(LSTR("#f00")));
    QVERIFY2(!json_obj.hasIndex(3), "Failure");
}
void JsonTest::notHasKey() {
    QString key = LSTR("colorVal");
    QString val = LSTR("#f00");

    Json json_obj = Json::fromJsonStr(TJSON_OBJ(key, val));
    QVERIFY2(!json_obj.hasKey(LSTR("colorV")), "Failure");
}


void JsonTest::bracketsIndex() {
    QString val = LSTR("#f00");

    Json json_obj = Json::fromJsonStr(TJSON_ARR(val));
    QVERIFY2(json_obj[0].string() == val, "Failure");
}
void JsonTest::bracketsKey() {
    QString key = LSTR("colorVal");
    QString val = LSTR("#f00");

    Json json_obj = Json::fromJsonStr(TJSON_OBJ(key, val));
    QVERIFY2(json_obj[key].string() == val, "Failure");
}


void JsonTest::valIndex() {
    QString val = LSTR("#f00");

    Json json_obj = Json::fromJsonStr(TJSON_ARR(val));
    QVERIFY2(json_obj.val(0).string() == val, "Failure");
}
void JsonTest::valKey() {
    QString key = LSTR("colorVal");
    QString val = LSTR("#f00");

    Json json_obj = Json::fromJsonStr(TJSON_OBJ(key, val));
    QVERIFY2(json_obj.val(key).string() == val, "Failure");
}

void JsonTest::val2Index() {
    QString val = LSTR("#f00");

    Json json_obj = Json::fromJsonStr(TJSON_SUB_ARR(val));
    QVERIFY2(json_obj.val2(TJSON_SUB_ARR_KEY_ARGS).string() == val, "Failure");
}
void JsonTest::val2Key() {
    QString root_key = LSTR("colors");
    QString key = LSTR("colorVal");
    QString val = LSTR("#f00");

    Json json_obj = Json::fromJsonStr(TJSON_SUB_OBJ(root_key, key, val));
    QVERIFY2(json_obj.val2(root_key, key).string() == val, "Failure");
}

void JsonTest::jsonToString() {
    QByteArray json_str = TJSON_OBJ(LSTR("genre"), LSTR("pop")).remove(' ').toUtf8();
    Json json_obj = Json::fromJsonStr(json_str);
    QVERIFY2(json_str == json_obj.toJsonStr(), "Failure");
}
void JsonTest::jsonObjToString() {
    QByteArray json_str = TJSON_OBJ(LSTR("genre"), LSTR("pop")).remove(' ').toUtf8();
    JsonObj json_obj = JsonObj::fromJsonStr(json_str);
    QVERIFY2(json_str == json_obj.toJsonStr(), "Failure");
}
void JsonTest::jsonArrToString() {
    QByteArray json_str = TJSON_ARR(LSTR("pop")).remove(' ').toUtf8();
    JsonArr json_arr = JsonArr::fromJsonStr(json_str);
    QVERIFY2(json_str == json_arr.toJsonStr(), "Failure");
}

void JsonTest::jsonStr() {
    QString key = LSTR("color");
    QString val = LSTR("#f00");

    Json json_obj = Json::fromJsonStr(TJSON_OBJ(key, val));
    QVERIFY2(json_obj.string(key) == val, "Failure");
}
void JsonTest::jsonBool() {
    QString key = LSTR("color");
    QString val = LSTR("false");

    Json json_obj = Json::fromJsonStr(TJSON_OBJ2(key, val));
    QVERIFY2(!json_obj.boolean(key), "Failure");
}
void JsonTest::jsonInt() {
    QString key = LSTR("color");
    int val = 5;

    Json json_obj = Json::fromJsonStr(TJSON_OBJ2(key, QString::number(val)));
    QVERIFY2(json_obj.integer(key) == val, "Failure");
}
void JsonTest::jsonInt64() { // qjsonValue not fully supported int64 :(
    QString key = LSTR("color");
    qint64 val = 92233720368547760;
    Json json_obj = Json::fromJsonStr(TJSON_OBJ2(key, QString::number(val)));
    QVERIFY2(json_obj.bigInt(key) == val, "Failure");
}
void JsonTest::jsonDouble() {
    QString key = LSTR("color");
    double val = 123.23342445354756765;
    QString val_str = QString::number(val, 'g', 32);
    Json json_obj = Json::fromJsonStr(TJSON_OBJ2(key, val_str));
    QVERIFY2(json_obj.rational(key) == val, "Failure");
}
void JsonTest::jsonFStr() {
    QString key = LSTR("color");
    int val = 123;

    Json json_obj = Json::fromJsonStr(TJSON_OBJ(key, QString::number(val)));
    QVERIFY2(json_obj.forceString(key) ==QString::number(val), "Failure");
}

//----------------------------

QTEST_APPLESS_MAIN(JsonTest)

#include "main.moc"
