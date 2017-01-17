#include "json_arr.h"
#include <qjsonobject.h>
#include <qvariant.h>

JsonArr JsonArr::fromJsonStr(const QByteArray & text) { return Json::fromJsonStr(text).toArray(); }
JsonArr JsonArr::fromJsonStr(const QString & text) { return Json::fromJsonStr(text).toArray(); }

QByteArray JsonArr::toJsonStr(const JsonFormat & format) { return operator Json().toJsonStr(format); }
QVariant JsonArr::toVariant() const { return operator Json().toVariant(); }

JsonArr::JsonArr() : QJsonArray() {}
JsonArr::JsonArr(const QJsonArray & oth_arr) : QJsonArray(oth_arr) {}
JsonArr & JsonArr::operator=(const QJsonArray & x) { QJsonArray::operator=(x); return *this; }

JsonArr::operator QJsonArray() const { return (QJsonArray)*this; }
JsonArr::operator Json() const { return Json(operator QJsonArray()); }

Json::Type JsonArr::type() const { return Json::Array; }

int JsonArr::size() { return QJsonArray::size(); }

QString JsonArr::concatKeys(const QString & key, const QString & separator) {
    QString cat_str;
    for(QJsonArray::Iterator item = begin(); item != end(); item++) {
        Json item_obj = *item;
        cat_str = cat_str % (cat_str.isEmpty() ? QString() : separator) % item_obj.string(key);
    }
    return cat_str;
}

QString JsonArr::concatKeys(const QString & separator) {
    QString cat_str;
    for(QJsonArray::Iterator item = begin(); item != end(); item++) {
        Json item_obj = *item;
        cat_str = cat_str % (cat_str.isEmpty() ? QString() : separator) % item_obj.forceString();
    }
    return cat_str;
}

Json JsonArr::operator[](const int & index) { return val(index); }
Json JsonArr::val(const int & index) { return this -> at(index); }
Json JsonArr::val2(const int & index1, const int & index2) { return J_KEY2II(index1, index2); }
Json JsonArr::val2(const int & index1, const QString & key2) { return J_KEY2IS(index1, key2); }

JsonArr JsonArr::arr() const { return *this; }
JsonArr JsonArr::toArray() const { return *this; }

bool JsonArr::boolean(const int & index) { return val(index).toBool(); }
bool JsonArr::boolean2(const int & index1, const int & index2) { return val2(index1, index2).toBool(); }
bool JsonArr::boolean2(const int & index1, const QString & key2) { return val2(index1, key2).toBool(); }

int JsonArr::integer(const int & index) { return val(index).toInt(); }
int JsonArr::integer2(const int & index1, const int & index2) { return val2(index1, index2).toInt(); }
int JsonArr::integer2(const int & index1, const QString & key2) { return val2(index1, key2).toInt(); }

qint64 JsonArr::bigInt(const int & index) { return JOBJ_BINT(val(index)); }
qint64 JsonArr::bigInt2(const int & index1, const int & index2) { return JOBJ_BINT(val2(index1, index2)); }
qint64 JsonArr::bigInt2(const int & index1, const QString & key2) { return JOBJ_BINT(val2(index1, key2)); }

double JsonArr::rational2(const int & index) { return val(index).toDouble(); }
double JsonArr::rational2(const int & index1, const int & index2) { return val2(index1, index2).toDouble(); }
double JsonArr::rational2(const int & index1, const QString & key2) { return val2(index1, key2).toDouble(); }

QString JsonArr::string(const int & index) { return val(index).toString(); }
QString JsonArr::string2(const int & index1, const int & index2) { return val2(index1, index2).toString(); }
QString JsonArr::string2(const int & index1, const QString & key2) { return val2(index1, key2).toString(); }

QString JsonArr::forceString(const int & index) { return J_STR(val(index)); }
QString JsonArr::forceString2(const int & index1, const int & index2) { return J_STR(val2(index1, index2)); }
QString JsonArr::forceString2(const int & index1, const QString & key2) { return J_STR(val2(index1, key2)); }
