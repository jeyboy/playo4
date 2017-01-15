#ifndef JSON_H
#define JSON_H

#include "json_global.h"
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

#define J_STR(jval) jval.isString() ? jval.toString() : QString::number(JOBJ_BINT(jval));

#define JOBJ_KEY2SS(key1, key2) value(key1).toObject().value(key2)
#define JOBJ_KEY2II(index1, index2) at(index1).toArray()[index2]
#define JOBJ_KEY2IS(index1, key2) at(index1).toObject().value(key2)
#define JOBJ_KEY2SI(key1, index2) value(key1).toArray()[index2]

#define JOBJ_BINT(val) (qint64)val.toDouble()

class JSONSHARED_EXPORT Json : public QJsonValue {
public:
    enum JsonFormat { Indented, Compact };

    static Json fromVariant(const QVariant & variant);

    static Json fromJsonStr(const QString & text);
    static Json fromJsonStr(const QString & text, QString & error);
    static Json fromJsonStr(const QByteArray & text);
    static Json fromJsonStr(const QByteArray & text, QString & error);

    virtual QVariant toVariant() const;
    virtual QByteArray toJsonStr(const JsonFormat & format = Compact);

    virtual bool isArray() const { return type() == Array; }
    virtual bool isObject() const { return type() == Object; }


//    inline bool isNull() const { return type() == Null; }
//    inline bool isBool() const { return type() == Bool; }
//    inline bool isDouble() const { return type() == Double; }
//    inline bool isString() const { return type() == String; }
//    inline bool isUndefined() const { return type() == Undefined; }

//    bool toBool(bool defaultValue = false) const;
//    int toInt(int defaultValue = 0) const;
//    double toDouble(double defaultValue = 0) const;
//    QString toString() const;
//    QString toString(const QString &defaultValue) const;


    Json(const Json::Type & = Null);
    Json(const QJsonDocument & doc);
    explicit Json(const JsonObj & obj);
    Json(const QJsonObject & obj);
    explicit Json(const JsonArr & arr);
    Json(const QJsonArray & arr);
    Json(const QJsonValueRef & ref);

    Json(const QJsonValue &);
    Json & operator=(const QJsonValue & x);
    Json & operator=(const QJsonValueRef & x);
    operator QJsonValue();

    virtual ~Json();

    virtual Json::Type type() const;


    virtual int size();

    virtual bool hasKey(const QString & key);
    virtual bool hasIndex(const int & index);

    // concat keys from obj hash
    virtual QString concatKeys(const QString & key1, const QString & key2, const QString & separator);
    // concat key from array of objs
    virtual QString concatKeys(const QString & key, const QString & separator);

    virtual Json operator[](const int & index);
    virtual Json operator[](const QString & key);
    virtual Json val(const int & index);
    virtual Json val(const QString & key);
    virtual Json val2(const int & index1, const int & index2);
    virtual Json val2(const int & index1, const QString & key2);
    virtual Json val2(const QString & key1, const QString & key2);
    virtual Json val2(const QString & key1, const int & index2);

    virtual JsonObj obj() const;
    virtual JsonObj toObject() const;
    virtual JsonObj toObject(const QJsonObject & default_value) const;

    virtual JsonArr arr() const;
    virtual JsonArr toArray() const;
    virtual JsonArr toArray(const QJsonArray & default_value) const;

    virtual bool boolean();
    virtual bool boolean(const int & index);
    virtual bool boolean(const QString & key);
    virtual bool boolean2(const int & index1, const int & index2);
    virtual bool boolean2(const int & index1, const QString & key2);
    virtual bool boolean2(const QString & key1, const QString & key2);
    virtual bool boolean2(const QString & key1, const int & index2);


    virtual int integer();
    virtual int integer(const int & index);
    virtual int integer(const QString & key);
    virtual int integer2(const int & index1, const int & index2);
    virtual int integer2(const int & index1, const QString & key2);
    virtual int integer2(const QString & key1, const QString & key2);
    virtual int integer2(const QString & key1, const int & index2);

    virtual qint64 bigInt();
    virtual qint64 bigInt(const int & index);
    virtual qint64 bigInt(const QString & key);
    virtual qint64 bigInt2(const int & index1, const int & index2);
    virtual qint64 bigInt2(const int & index1, const QString & key2);
    virtual qint64 bigInt2(const QString & key1, const QString & key2);
    virtual qint64 bigInt2(const QString & key1, const int & index2);

    virtual double rational();
    virtual double rational(const int & index);
    virtual double rational(const QString & key);
    virtual double rational2(const int & index1, const int & index2);
    virtual double rational2(const int & index1, const QString & key2);
    virtual double rational2(const QString & key1, const QString & key2);
    virtual double rational2(const QString & key1, const int & index2);

    virtual QString string();
    virtual QString string(const int & index);
    virtual QString string(const QString & key);
    virtual QString string(const QString & key, const QString & default_val);
    virtual QString string2(const int & index1, const int & index2);
    virtual QString string2(const int & index1, const QString & key2);
    virtual QString string2(const QString & key1, const QString & key2);
    virtual QString string2(const QString & key1, const int & index2);

    virtual QString forceString();
    virtual QString forceString(const int & index);
    virtual QString forceString(const QString & key);
    virtual QString forceString2(const int & index1, const int & index2);
    virtual QString forceString2(const int & index1, const QString & key2);
    virtual QString forceString2(const QString & key1, const QString & key2);
    virtual QString forceString2(const QString & key1, const int & index2);
};

#endif // JSON_H
