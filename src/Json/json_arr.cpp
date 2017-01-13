#include "json_arr.h"
#include "json.h"

JsonArr JsonArr::fromText(const QString & text) { return Json::fromText(text).toArray(); }

JsonArr::JsonArr() : QJsonArray() {}
JsonArr::JsonArr(const QJsonArray &) {}
JsonArr & JsonArr::operator=(const QJsonArray & /*x*/) { return *this; }
JsonArr::operator QJsonArray() { return (QJsonArray) *this; }

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

QString JsonArr::stringConv(const int & index) { return JOBJ_STR(val(index)); }

