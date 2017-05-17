#ifndef JSON_OBJ_H
#define JSON_OBJ_H

#include "json.h"

#include <qjsonobject.h>

class JSONSHARED_EXPORT JsonObj : public Json, public QJsonObject {
public:
    static JsonObj fromJsonStr(const QByteArray & text);
    static JsonObj fromJsonStr(const QByteArray & text, QString & error);
    static JsonObj fromJsonStr(const QString & text);
    static JsonObj fromJsonStr(const QString & text, QString & error);

    QByteArray toJsonStr(const JsonFormat & format = Compact);
    QVariant toVariant() const;

    JsonObj();
    JsonObj(const QJsonObject & oth);
    JsonObj & operator=(const QJsonObject & x);

    operator QJsonObject() const;
    operator Json() const;

    Json::Type type() const;

    inline bool isObject() const { return true; }

    int size();

    bool hasKey(const QString & key);

    QString concatKeys(const QString & key1, const QString & key2, const QString & separator);

    Json operator[](const QString & key);
    Json val(const QString & key);
    Json val(const QString & key1, const QString & key2);
    Json val(const QString & key1, const int & index2);

    JsonObj obj() const;
    JsonObj obj(const QString & key);
    JsonObj obj(const QString & key1, const QString & key2);
    JsonObj obj(const QString & key1, const int & index2);
    JsonObj toObject() const;

    bool boolean(const QString & key);
    bool boolean(const QString & key1, const QString & key2);
    bool boolean(const QString & key1, const int & index2);

    int integer(const QString & key);
    int integer(const QString & key1, const QString & key2);
    int integer(const QString & key1, const int & index2);

    qint64 bigInt(const QString & key);
    qint64 bigInt(const QString & key1, const QString & key2);
    qint64 bigInt(const QString & key1, const int & index2);

    double rational(const QString & key);
    double rational(const QString & key1, const QString & key2);
    double rational(const QString & key1, const int & index2);

    QString string(const QString & key);
    QString string(const QString & key, const QString & default_val);
    QString string(const QString & key1, const QString & key2);
    QString string(const QString & key1, const int & index2);

    QString forceString(const QString & key);
    QString forceString(const QString & key1, const QString & key2);
    QString forceString(const QString & key1, const int & index2);
};

#endif // JSON_OBJ_H
