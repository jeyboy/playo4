#ifndef JSON_H
#define JSON_H

#include "json_interface.h"

#include <qjsonvalue.h>

class QJsonDocument;
class JsonObj;
class QJsonObject;
class JsonArr;
//class QJsonArray;

class JSONSHARED_EXPORT Json : public QJsonValue, public JsonInterface {
public:
    static Json fromText(const QString & text);

    Json(const Type & = Null);
    Json(const QJsonDocument & doc);
    Json(const QJsonObject & obj);
    Json(const JsonObj & obj);
    Json(const QJsonArray & arr);
//    Json(const JsonArr & arr);

    Json(const QJsonValue &);
    Json & operator=(const QJsonValue & x);
    operator QJsonValue();

    bool hasKey(const QString & key);

    // concat keys from obj hash
    QString concatKeys(const QString & key1, const QString & key2, const QString & separator);
    // concat key from array of objs
    QString concatKeys(const QString & key, const QString & separator);

    Json operator[](const QString & key);
    Json val(const QString & key);
    Json val2(const QString & key1, const QString & key2);

    Json operator[](const int & index);
    Json val(const int & index);

    bool boolean(const QString & key);
    bool boolean2(const QString & key1, const QString & key2);

    int integer(const QString & key);
    int integer2(const QString & key1, const QString & key2);

    qint64 bigInt(const QString & key);
    qint64 bigInt2(const QString & key1, const QString & key2);

    QString string(const QString & key);
    QString string(const QString & key, const QString & default_val);
    QString string2(const QString & key1, const QString & key2);

    QString stringConv(const QString & key);
    QString stringConv2(const QString & key1, const QString & key2);
};

#endif // JSON_H
