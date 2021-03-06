#include "json.h"

#include <qjsondocument.h>
#include <qvariant.h>

#include "json_obj.h"
#include "json_arr.h"


Json Json::fromVariant(const QVariant & variant) { return QJsonValue::fromVariant(variant); }

Json Json::fromJsonStr(const QString & text) { return fromJsonStr(text.toUtf8()); }
Json Json::fromJsonStr(const QString & text, QString & error) { return fromJsonStr(text.toUtf8(), error); }
Json Json::fromJsonStr(const QByteArray & text) {
    QString error;
    return fromJsonStr(text, error);
}
Json Json::fromJsonStr(const QByteArray & text, QString & error) {
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(text, &err);
    if (err.error != QJsonParseError::NoError) {
        error = err.errorString();
        return Json();
    }
    return (Json)doc;
}

QByteArray Json::toJsonStr(const JsonFormat & format) {
    return (isArray() ? QJsonDocument(toArray()) : QJsonDocument(toObject())).toJson((QJsonDocument::JsonFormat)format);
}
QVariant Json::toVariant() const { return QJsonValue::toVariant(); }

Json::Json(const Json::Type & jtype) : QJsonValue(jtype) {}
Json::Json(const QJsonDocument & doc) : QJsonValue(doc.isArray() ? (QJsonValue)doc.array() : (QJsonValue)doc.object()) {}
Json::Json(const JsonObj & obj) : QJsonValue((QJsonObject)obj) {}
Json::Json(const QJsonObject & obj) : QJsonValue(obj) {}
Json::Json(const JsonArr & arr) : QJsonValue((QJsonArray)arr) {}
Json::Json(const QJsonArray & arr) : QJsonValue(arr) {}
Json::Json(const QJsonValueRef & ref) : QJsonValue(ref) {}

Json::Json(const QJsonValue & val) : QJsonValue(val) { }
Json & Json::operator=(const QJsonValue & x) { QJsonValue::operator=(x); return *this; }
Json & Json::operator=(const QJsonValueRef & x) { QJsonValue::operator=(x); return *this; }
Json::operator QJsonValue() { return (QJsonValue)*this; }

Json::~Json() {}

Json::Type Json::type() const { return QJsonValue::type(); }

int Json::size() { return isArray() ? QJsonValue::toArray().size() : QJsonValue::toObject().size(); }

bool Json::hasKey(const QString & key) { return QJsonValue::toObject().contains(key); }
bool Json::hasIndex(const int & index) { return QJsonValue::toArray().size() > index; }

// only object
QString Json::concatKeys(const QString & key1, const QString & key2, const QString & separator) {
    return ((JsonObj)toObject()).concatKeys(key1, key2, separator);
}

// only array
QString Json::concatKeys(const QString & key, const QString & separator) {
    return ((JsonArr)QJsonValue::toArray()).concatKeys(key, separator);
}

QString Json::concatKeys(const QString & separator) {
    return ((JsonArr)QJsonValue::toArray()).concatKeys(separator);
}

Json Json::operator[](const int & index) { return val(index); }
Json Json::operator[](const QString & key) { return val(key); }

Json Json::val(const int & index) { return QJsonValue::toArray().at(index); }
Json Json::val(const QString & key) { return QJsonValue::toObject().value(key); }

Json Json::val2(const int & index1, const int & index2) { return J_KEY2II(index1, index2); }
Json Json::val2(const QString & key1, const QString & key2) { return J_KEY2SS(key1, key2); }
Json Json::val2(const int & index1, const QString & key2) { return J_KEY2IS(index1, key2); }
Json Json::val2(const QString & key1, const int & index2) { return J_KEY2SI(key1, index2); }

JsonObj Json::obj() const { return QJsonValue::toObject(); }
JsonObj Json::toObject() const { return QJsonValue::toObject(); }
JsonObj Json::toObject(const QJsonObject & default_value) const { return QJsonValue::toObject(default_value); }

JsonArr Json::arr() const { return QJsonValue::toArray(); }
JsonArr Json::toArray() const { return QJsonValue::toArray(); }
JsonArr Json::toArray(const QJsonArray & default_value) const { return QJsonValue::toArray(default_value); }

bool Json::boolean() { return QJsonValue::toBool(); }
bool Json::boolean(const int & index) { return operator[](index).toBool(); }
bool Json::boolean(const QString & key) { return operator[](key).toBool(); }
bool Json::boolean2(const int & index1, const int & index2) { return val2(index1, index2).toBool(); }
bool Json::boolean2(const int & index1, const QString & key2) { return val2(index1, key2).toBool(); }
bool Json::boolean2(const QString & key1, const QString & key2) { return val2(key1, key2).toBool(); }
bool Json::boolean2(const QString & key1, const int & index2) { return val2(key1, index2).toBool(); }

int Json::integer() { return QJsonValue::toInt(); }
int Json::integer(const int & index) { return operator[](index).toInt(); }
int Json::integer(const QString & key) { return operator[](key).toInt(); }
int Json::integer2(const int & index1, const int & index2) { return val2(index1, index2).toInt(); }
int Json::integer2(const int & index1, const QString & key2) { return val2(index1, key2).toInt(); }
int Json::integer2(const QString & key1, const QString & key2) { return val2(key1, key2).toInt(); }
int Json::integer2(const QString & key1, const int & index2) { return val2(key1, index2).toInt(); }

qint64 Json::bigInt() { return JOBJ_BINT((*this)); }
qint64 Json::bigInt(const int & index) { return JOBJ_BINT(operator[](index)); }
qint64 Json::bigInt(const QString & key) { return JOBJ_BINT(operator[](key)); }
qint64 Json::bigInt2(const int & index1, const int & index2) { return JOBJ_BINT(val2(index1, index2)); }
qint64 Json::bigInt2(const int & index1, const QString & key2) { return JOBJ_BINT(val2(index1, key2)); }
qint64 Json::bigInt2(const QString & key1, const QString & key2) { return JOBJ_BINT(val2(key1, key2)); }
qint64 Json::bigInt2(const QString & key1, const int & index2) { return JOBJ_BINT(val2(key1, index2)); }

double Json::rational() { return QJsonValue::toDouble(); }
double Json::rational(const int & index) { return operator[](index).toDouble(); }
double Json::rational(const QString & key) { return operator[](key).toDouble(); }
double Json::rational2(const int & index1, const int & index2) { return val2(index1, index2).toDouble(); }
double Json::rational2(const int & index1, const QString & key2) { return val2(index1, key2).toDouble(); }
double Json::rational2(const QString & key1, const QString & key2) { return val2(key1, key2).toDouble(); }
double Json::rational2(const QString & key1, const int & index2) { return val2(key1, index2).toDouble(); }

QString Json::string() { return QJsonValue::toString(); }
QString Json::string(const int & index) { return operator[](index).toString(); }
QString Json::string(const QString & key) { return operator[](key).toString(); }
QString Json::string(const QString & key, const QString & default_val) { return val(key).toString(default_val); }
QString Json::string2(const int & index1, const int & index2) { return val2(index1, index2).toString(); }
QString Json::string2(const int & index1, const QString & key2) { return val2(index1, key2).toString(); }
QString Json::string2(const QString & key1, const QString & key2) { return val2(key1, key2).toString(); }
QString Json::string2(const QString & key1, const int & index2) { return val2(key1, index2).toString(); }

QString Json::forceString() { return J_STR((*this)); }
QString Json::forceString(const int & index) { return J_STR(operator[](index)); }
QString Json::forceString(const QString & key) { return J_STR(operator[](key)); }
QString Json::forceString2(const int & index1, const int & index2) { return J_STR(val2(index1, index2)); }
QString Json::forceString2(const int & index1, const QString & key2) { return J_STR(val2(index1, key2)); }
QString Json::forceString2(const QString & key1, const QString & key2) { return J_STR(val2(key1, key2)); }
QString Json::forceString2(const QString & key1, const int & index2) { return J_STR(val2(key1, index2)); }
