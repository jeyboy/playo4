#include "json.h"

#include <qjsondocument.h>

#include "json_obj.h"
#include "json_arr.h"

Json::Json(const Type & jtype) : QJsonValue(jtype) {}
Json::Json(const QJsonObject & obj) : QJsonValue(obj) {}
Json::Json(const JsonObj & obj) : QJsonValue(obj) {}
Json::Json(const QJsonArray & arr) : QJsonValue(arr) {}
//Json::Json(const JsonArr & arr) : QJsonValue(arr) {}


Json Json::fromText(const QString & text) { return Json(); }

bool Json::hasKey(const QString & key) { return toObject().contains(key); }


QString Json::concatKeys(const QString & key1, const QString & key2, const QString & separator) {
    QJsonObject qobj = toObject();
    JsonObj obj = *reinterpret_cast<JsonObj *>(&qobj);
    return obj.concatKeys(key1, key2, separator);
}
// concat key from array of objs
QString Json::concatKeys(const QString & key, const QString & separator) {}

Json Json::operator[](const QString & key) {}
Json Json::val(const QString & key) {}
Json Json::val2(const QString & key1, const QString & key2) {}

Json Json::operator[](const int & index) {}
Json Json::val(const int & index) {}

bool Json::boolean(const QString & key) {}
bool Json::boolean2(const QString & key1, const QString & key2) {}

int Json::integer(const QString & key) {}
int Json::integer2(const QString & key1, const QString & key2) {}

qint64 Json::bigInt(const QString & key) {}
qint64 Json::bigInt2(const QString & key1, const QString & key2) {}

QString Json::string(const QString & key) {}
QString Json::string(const QString & key, const QString & default_val) {}
QString Json::string2(const QString & key1, const QString & key2) {}

QString Json::stringConv(const QString & key) {}
QString Json::stringConv2(const QString & key1, const QString & key2) {}

//#define JSON_HAS_KEY(json, key) json.contains(key)

//#define JSON_CONV_STR(json_val) (json_val.isString() ? json_val.toString() : QString::number((qint64)json_val.toDouble()))

//#define JSON_STR_CAT(json, key1, separator, key2) QString(JSON_STR(json, key1) % separator % JSON_STR(json, key2))
///*
//#define JSON_ARR_STR_CAT(json, key, separator) \
//    QString cat_str; \
//    for(QJsonArray::Iterator item = json.begin(); item != json.end(); item++) { \
//        QJsonObject item_obj = (*item).toObject(); \
//        cat_str = cat_str % (cat_str.isEmpty() ? QString() : separator) % JSON_STR(item_obj, key); \
//    }\
//    cat_str
//*/

//#define JSON_VAL(json, key) json.value(key)

//#define JSON_CSTR(json, key) JSON_CONV_STR(json.value(key))
//#define JSON_STR(json, key) json.value(key).toString()
//#define JSON_STR_DEF(json, key, def) json.value(key).toString(def)

//#define JSON_INT(json, key) (qint64)json.value(key).toDouble()
//#define JSON_BOOL(json, key) json.value(key).toBool()
//#define JSON_OBJ(json, key) json.value(key).toObject()
//#define JSON_ARR(json, key) json.value(key).toArray()

////#define JSON_INT(json, key1, key2) JSON_INT(JSON_OBJ(json, key1), key2)
//#define JSON_STR2(json, key1, key2) JSON_STR(JSON_OBJ(json, key1), key2)
//#define JSON_CSTR2(json, key1, key2) JSON_CSTR(JSON_OBJ(json, key1), key2)
//#define JSON_OBJ2(json, key1, key2) JSON_OBJ(JSON_OBJ(json, key1), key2)
//#define JSON_ARR2(json, key1, key2) JSON_ARR(JSON_OBJ(json, key1), key2)
