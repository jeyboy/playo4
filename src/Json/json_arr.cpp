#include "json_arr.h"

JsonArr JsonArr::fromText(const QString & text) {

}

JsonArr::JsonArr() : QJsonArray() {}
JsonArr::JsonArr(const QJsonArray &) {}
JsonArr & JsonArr::operator=(const QJsonArray & /*x*/) { return *this; }
JsonArr::operator QJsonArray() { return QJsonArray(); }

QString JsonArrconcatKeys(const QString & key, const QString & separator) {}

Json JsonArr::operator[](const int & index) {}
Json JsonArr::val(const int & index) {}

bool JsonArr::boolean(const int & index) {}

int JsonArr::integer(const int & index) {}

qint64 JsonArr::bigInt(const int & index) {}

QString JsonArr::string(const int & index) {}

QString JsonArr::stringConv(const int & index) {}

