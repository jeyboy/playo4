#include <QString>
#include <QtTest>

#include <js.h>
#include "test_data.h"

class JsTest : public QObject {
    Q_OBJECT
public:
    JsTest();

private Q_SLOTS:
    void callBuilderString();
    void callBuilderInt();

    void jsCallString();
    void jsCallInt();
    void jsMultiCall();
};

JsTest::JsTest() { }

void JsTest::callBuilderString() {
    QString arg1 = LSTR("abc");
    QString arg2 = LSTR("3");

    QString call_builder_result = Js::callBuilder(NAMED_FUNC_NAME, QVariantList() << arg1 << arg2);
    QString res = NAMED_FUNC_NAME % '(' % '"' % arg1 % LSTR("\", ") % '"' % arg2 % LSTR("\")");

    QVERIFY2(res == call_builder_result, "Failure");
}

void JsTest::callBuilderInt() {
    int arg1 = 546;

    QString call_builder_result = Js::callBuilder(NAMED_FUNC_NAME, QVariantList() << arg1);
    QString res = NAMED_FUNC_NAME % '(' % QString::number(arg1) % LSTR(")");

    QVERIFY2(res == call_builder_result, "Failure");
}

void JsTest::jsCallString() {
    QString arg1 = LSTR("abc");
    QString arg2 = LSTR("3");

    QString js_res = Js(NAMED_FUNC).proceedAsStr(Js::callBuilder(NAMED_FUNC_NAME, QVariantList() << arg1 << arg2));

    QVERIFY2(js_res == arg1 % arg2, "Failure");
}

void JsTest::jsCallInt() {
    int arg1 = 54;
    int arg2 = 46;

    int res = Js(NAMED_FUNC).proceedAsInt(Js::callBuilder(NAMED_FUNC_NAME, QVariantList() << arg1 << arg2));

    QVERIFY2(res == arg1 + arg2, "Failure");
}

void JsTest::jsMultiCall() {
    Js js = Js(COMBO_NAMED_FUNCS);

    QString arg1 = LSTR("abc");
    QString arg2 = LSTR("3");

    int arg3 = 46;

    QString res1 = js.proceedAsStr(Js::callBuilder(NAMED_FUNC_NAME, QVariantList() << arg1 << arg2));
    int res2 = js.proceedAsInt(Js::callBuilder(NAMED_FUNC_NAME2, QVariantList() << arg3));

    QVERIFY2(res1 == arg1 + arg2 && res2 == arg3 + 1, "Failure");
}

QTEST_APPLESS_MAIN(JsTest)

#include "main.moc"


