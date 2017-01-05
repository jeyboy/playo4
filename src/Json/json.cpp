#include "json.h"

#include <qjsonvalue.h>
#include <qjsondocument.h>

#include "json_obj.h"
#include "json_arr.h"

Json::Json(const Type & jtype) : QJsonValue(jtype) {}
Json::Json(const QJsonDocument & doc) : QJsonValue(doc.isArray() ? (QJsonValue)doc.array() : (QJsonValue)doc.object()) {}
Json::Json(const QJsonObject & obj) : QJsonValue(obj) {}
Json::Json(const JsonObj & obj) : QJsonValue(obj) {}
Json::Json(const QJsonArray & arr) : QJsonValue(arr) {}
Json::Json(const JsonArr & arr) : QJsonValue(arr) {}
Json::Json(const QJsonValueRef & ref) : QJsonValue(ref) {}

Json::Json(const QJsonValue & val) : QJsonValue(val) { }
Json & Json::operator=(const QJsonValue & x) { QJsonValue::operator=(x); return *this; }
Json & Json::operator=(const QJsonValueRef & x) { QJsonValue::operator=(x); return *this; }
Json::operator QJsonValue() { return (QJsonValue)*this; }

Json::~Json() {}

Json Json::fromText(const QString & text) {
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(text.toUtf8(), &err);
    if (err.error == QJsonParseError::NoError) return Json();
    return (Json)doc;
}

bool Json::hasKey(const QString & key) { return toObject().contains(key); }

QString Json::concatKeys(const QString & key1, const QString & key2, const QString & separator) {
    return ((JsonObj)toObject()).concatKeys(key1, key2, separator);
}

QString Json::concatKeys(const QString & key, const QString & separator) {
    return ((JsonArr)toArray()).concatKeys(key, separator);
}

Json Json::operator[](const QString & key) { return val(key); }
Json Json::val(const QString & key) { return toObject().value(key); }
Json Json::val2(const QString & key1, const QString & key2) { return J_KEY2(key1, key2); }

Json Json::operator[](const int & index) { return val(index); }
Json Json::val(const int & index) { return toArray().at(index); }

JsonObj Json::obj() { return toObject(); }
JsonArr Json::arr() { return toArray(); }

bool Json::boolean(const int & index) { return this -> operator[](index).toBool(); }
bool Json::boolean(const QString & key) { return this -> operator[](key).toBool(); }
bool Json::boolean2(const QString & key1, const QString & key2) { return val2(key1, key2).toBool(); }

int Json::integer(const int & index) { return this -> operator[](index).toInt(); }
int Json::integer(const QString & key) { return this -> operator[](key).toInt(); }
int Json::integer2(const QString & key1, const QString & key2) { return val2(key1, key2).toInt(); }

qint64 Json::bigInt(const int & index) { return JOBJ_BINT(this -> operator[](index)); }
qint64 Json::bigInt(const QString & key) { return JOBJ_BINT(this -> operator[](key)); }
qint64 Json::bigInt2(const QString & key1, const QString & key2) { return JOBJ_BINT(val2(key1, key2)); }

QString Json::string(const int & index) { return this -> operator[](index).toString(); }
QString Json::string(const QString & key) { return this -> operator[](key).toString(); }
QString Json::string(const QString & key, const QString & default_val) { return val(key).toString(default_val); }
QString Json::string2(const QString & key1, const QString & key2) { return val2(key1, key2).toString(); }

QString Json::stringConv(const int & index) { return JOBJ_STR(this -> operator[](index)); }
QString Json::stringConv(const QString & key) { return JOBJ_STR(this -> operator[](key)); }
QString Json::stringConv2(const QString & key1, const QString & key2) { return JOBJ_STR(val2(key1, key2)); }

//#define JSON_HAS_KEY(json, key) json.contains(key)

//#define JSON_CONV_STR(json_val) (json_val.isString() ? json_val.toString() : QString::number((qint64)json_val.toDouble()))

//#define JSON_STR_CAT(json, key1, separator, key2) QString(JSON_STR(json, key1) % separator % JSON_STR(json, key2))

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
