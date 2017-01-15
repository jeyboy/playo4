#include "json_obj.h"
#include <qjsonarray.h>

JsonObj JsonObj::fromJsonStr(const QByteArray & text) { return Json::fromJsonStr(text).toObject(); }
JsonObj JsonObj::fromJsonStr(const QString & text) { return Json::fromJsonStr(text).toObject(); }

QByteArray JsonObj::toJsonStr(const JsonFormat & format) { return operator Json().toJsonStr(format); }

JsonObj::JsonObj() : QJsonObject() {}
JsonObj::JsonObj(const QJsonObject & oth_json) : QJsonObject(oth_json) {}

JsonObj & JsonObj::operator=(const QJsonObject & x) { QJsonObject::operator=(x); return *this; }
JsonObj::operator QJsonObject() { return (QJsonObject)*this; }
JsonObj::operator Json() { return Json(operator QJsonObject()); }

int JsonObj::size() { return QJsonObject::size(); }

bool JsonObj::hasKey(const QString & key) { return contains(key); }

QString JsonObj::concatKeys(const QString & key1, const QString & key2, const QString & separator) {
   return string(key1) % separator % string(key2);
}

Json JsonObj::operator[](const QString & key) { return value(key); }
Json JsonObj::val(const QString & key) { return value(key); }
Json JsonObj::val2(const QString & key1, const QString & key2) { return JOBJ_KEY2SS(key1, key2); }
Json JsonObj::val2(const QString & key1, const int & index2) { return JOBJ_KEY2SI(key1, index2); }

bool JsonObj::boolean(const QString & key) { return value(key).toBool(); }
bool JsonObj::boolean2(const QString & key1, const QString & key2) { return JOBJ_KEY2SS(key1, key2).toBool();  }

int JsonObj::integer(const QString & key) { return value(key).toInt(); }
int JsonObj::integer2(const QString & key1, const QString & key2) { return JOBJ_KEY2SS(key1, key2).toInt(); }

qint64 JsonObj::bigInt(const QString & key) { return JOBJ_BINT(value(key)); }
qint64 JsonObj::bigInt2(const QString & key1, const QString & key2) { return JOBJ_BINT(JOBJ_KEY2SS(key1, key2)); }

QString JsonObj::string(const QString & key) { return value(key).toString(); }
QString JsonObj::string(const QString & key, const QString & default_val) { return value(key).toString(default_val); }
QString JsonObj::string2(const QString & key1, const QString & key2) { return JOBJ_KEY2SS(key1, key2).toString(); }
QString JsonObj::string2(const QString & key1, const int & index2) { return JOBJ_KEY2SI(key1, index2).toString(); }

QString JsonObj::forceString(const QString & key) { return J_STR(value(key)); }
QString JsonObj::forceString2(const QString & key1, const QString & key2) { return J_STR(JOBJ_KEY2SS(key1, key2)); }
