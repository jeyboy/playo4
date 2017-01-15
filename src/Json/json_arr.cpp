#include "json_arr.h"
#include <qjsonobject.h>

JsonArr JsonArr::fromJsonStr(const QByteArray & text) { return Json::fromJsonStr(text).toArray(); }
JsonArr JsonArr::fromJsonStr(const QString & text) { return Json::fromJsonStr(text).toArray(); }

QByteArray JsonArr::toJsonStr(const JsonFormat & format) { return operator Json().toJsonStr(format); }

JsonArr::JsonArr() : QJsonArray() {}
JsonArr::JsonArr(const QJsonArray & oth_arr) : QJsonArray(oth_arr) {}
JsonArr & JsonArr::operator=(const QJsonArray & x) { QJsonArray::operator=(x); return *this; }
JsonArr::operator QJsonArray() { return (QJsonArray)*this; }
JsonArr::operator Json() { return Json(operator QJsonArray()); }

int JsonArr::size() { return QJsonArray::size(); }

QString JsonArr::concatKeys(const QString & key, const QString & separator) {
    QString cat_str;
    for(QJsonArray::Iterator item = begin(); item != end(); item++) {
        Json item_obj = *item;
        cat_str = cat_str % (cat_str.isEmpty() ? QString() : separator) % item_obj.string(key);
    }
    return cat_str;
}

Json JsonArr::operator[](const int & index) { return val(index); }
Json JsonArr::val(const int & index) { return this -> at(index); }

bool JsonArr::boolean(const int & index) { return val(index).toBool(); }

int JsonArr::integer(const int & index) { return val(index).toInt(); }

qint64 JsonArr::bigInt(const int & index) { return JOBJ_BINT(val(index)); }

QString JsonArr::string(const int & index) { return val(index).toString(); }

QString JsonArr::forceString(const int & index) { return J_STR(val(index)); }

