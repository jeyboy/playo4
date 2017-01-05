#include "json_arr.h"
#include "json.h"

JsonArr JsonArr::fromText(const QString & text) { return Json::fromText(text).toArray(); }

JsonArr::JsonArr() : QJsonArray() {}
JsonArr::JsonArr(const QJsonArray &) {}
JsonArr & JsonArr::operator=(const QJsonArray & /*x*/) { return *this; }
JsonArr::operator QJsonArray() { return (QJsonArray) *this; }

QString JsonArr::concatKeys(const QString & key, const QString & separator) {}

Json JsonArr::operator[](const int & index) {}
Json JsonArr::val(const int & index) {}

bool JsonArr::boolean(const int & index) {}

int JsonArr::integer(const int & index) {}

qint64 JsonArr::bigInt(const int & index) {}

QString JsonArr::string(const int & index) {}

QString JsonArr::stringConv(const int & index) {}

