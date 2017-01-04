#include "json_obj.h"

JsonObj::JsonObj() : QJsonObject() {}

JsonObj JsonObj::fromText(const QString & text) { return JsonObj(); }

bool JsonObj::hasKey(const QString & key) { return contains(key); }


QString JsonObj::concatKeys(const QString & key1, const QString & key2, const QString & separator) {
   return string(key1) % separator % string(key2);
}
// concat key from array of objs
QString JsonObj::concatKeys(const QString & /*key*/, const QString & /*separator*/) { return QString(); }

Json JsonObj::operator[](const QString & key) { return reinterpret_cast<Json>(value(key)); }
Json JsonObj::val(const QString & key) { return reinterpret_cast<Json>(value(key)); }
Json JsonObj::val2(const QString & key1, const QString & key2) { return reinterpret_cast<Json>(JOBJ_KEY2(key1, key2)); }

Json JsonObj::operator[](const int & /*index*/) { return JsonObj(); }
Json JsonObj::val(const int & /*index*/) { return JsonObj(); }

bool JsonObj::boolean(const QString & key) { return value(key).toBool(); }
bool JsonObj::boolean2(const QString & key1, const QString & key2) { return JOBJ_KEY2(key1, key2).toBool();  }

int JsonObj::integer(const QString & key) { return value(key).toInt(); }
int JsonObj::integer2(const QString & key1, const QString & key2) { return JOBJ_KEY2(key1, key2).toInt(); }

qint64 JsonObj::bigInt(const QString & key) { return JOBJ_BINT(value(key)); }
qint64 JsonObj::bigInt2(const QString & key1, const QString & key2) { return JOBJ_BINT(JOBJ_KEY2(key1, key2)); }

QString JsonObj::string(const QString & key) { return value(key).toString(); }
QString JsonObj::string(const QString & key, const QString & default_val) { return value(key).toString(default_val); }
QString JsonObj::string2(const QString & key1, const QString & key2) { return JOBJ_KEY2(key1, key2).toString(); }

QString JsonObj::stringConv(const QString & key) {
    QJsonValue val = value(key);
    return val.isString() ? val.toString() : QString::number(JOBJ_BINT(val));
}
QString JsonObj::stringConv2(const QString & key1, const QString & key2) {
    QJsonValue val = JOBJ_KEY2(key1, key2);
    return val.isString() ? val.toString() : QString::number(JOBJ_BINT(val));
}
