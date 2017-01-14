#ifndef JSON_H
#define JSON_H

#include "json_interface.h"

#include <qjsonvalue.h>

class QJsonDocument;
class JsonObj;
class QJsonObject;
class JsonArr;
class QJsonArray;
class QJsonValueRef;
class QJsonParseError;

#define J_KEY2SS(key1, key2) toObject().value(key1).toObject().value(key2)
#define J_KEY2II(index1, index2) toArray()[index1].toArray()[index2]
#define J_KEY2IS(index1, key2) toArray()[index1].toObject().value(key2)
#define J_KEY2SI(key1, index2) toObject().value(key1).toArray()[index2]

#define JOBJ_KEY2SS(key1, key2) value(key1).toObject().value(key2)
#define JOBJ_KEY2II(index1, index2) at(index1).toArray()[index2]
#define JOBJ_KEY2IS(index1, key2) at(index1).toObject().value(key2)
#define JOBJ_KEY2SI(key1, index2) value(key1).toArray()[index2]

#define JOBJ_BINT(val) (qint64)val.toDouble()
#define JOBJ_STR(jval) jval.isString() ? jval.toString() : QString::number(JOBJ_BINT(jval));

class JSONSHARED_EXPORT Json : public QJsonValue, public IJson {
public:
    static Json fromText(const QString & text);
    static Json fromText(const QString & text, QString & error);
    static Json fromText(const QByteArray & text);
    static Json fromText(const QByteArray & text, QString & error);

    Json(const Type & = Null);
    Json(const QJsonDocument & doc);
    Json(const QJsonObject & obj);
    Json(const JsonObj & obj);
    Json(const QJsonArray & arr);
    Json(const JsonArr & arr);
    Json(const QJsonValueRef & ref);

    Json(const QJsonValue &);
    Json & operator=(const QJsonValue & x);
    Json & operator=(const QJsonValueRef & x);
    operator QJsonValue();

    virtual ~Json();

    int size();

    bool hasKey(const QString & key);
    bool hasIndex(const int & index);

    // concat keys from obj hash
    QString concatKeys(const QString & key1, const QString & key2, const QString & separator);
    // concat key from array of objs
    QString concatKeys(const QString & key, const QString & separator);

    Json operator[](const int & index);
    Json operator[](const QString & key);
    Json val(const int & index);
    Json val(const QString & key);
    Json val2(const int & index1, const int & index2);
    Json val2(const QString & key1, const QString & key2);

    JsonObj obj();
    JsonArr arr();

    bool boolean(const int & index);
    bool boolean2(const int & index1, const int & index2);
    bool boolean(const QString & key);
    bool boolean2(const QString & key1, const QString & key2);

    int integer(const int & index);
    int integer2(const int & index1, const int & index2);
    int integer(const QString & key);
    int integer2(const QString & key1, const QString & key2);

    qint64 bigInt(const int & index);
    qint64 bigInt2(const int & index1, const int & index2);
    qint64 bigInt(const QString & key);
    qint64 bigInt2(const QString & key1, const QString & key2);

    QString string(const int & index);
    QString string2(const int & index1, const int & index2);
    QString string(const QString & key);
    QString string(const QString & key, const QString & default_val);
    QString string2(const QString & key1, const QString & key2);

    QString stringConv(const int & index);
    QString stringConv2(const int & index1, const int & index2);
    QString stringConv(const QString & key);
    QString stringConv2(const QString & key1, const QString & key2);
};

#endif // JSON_H
