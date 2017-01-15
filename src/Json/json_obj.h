#ifndef JSON_OBJ_H
#define JSON_OBJ_H

#include "json.h"

#include <qjsonobject.h>

class JSONSHARED_EXPORT JsonObj : public Json, public QJsonObject {
public:
    static JsonObj fromJsonStr(const QByteArray & text);
    static JsonObj fromJsonStr(const QString & text);

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
    Json val2(const QString & key1, const QString & key2);
    Json val2(const QString & key1, const int & index2);

    JsonObj obj() const;
    JsonObj toObject() const;

    bool boolean(const QString & key);
    bool boolean2(const QString & key1, const QString & key2);

    int integer(const QString & key);
    int integer2(const QString & key1, const QString & key2);

    qint64 bigInt(const QString & key);
    qint64 bigInt2(const QString & key1, const QString & key2);

    QString string(const QString & key);
    QString string(const QString & key, const QString & default_val);
    QString string2(const QString & key1, const QString & key2);
    QString string2(const QString & key1, const int & index2);

    QString forceString(const QString & key);
    QString forceString2(const QString & key1, const QString & key2);
};

#endif // JSON_OBJ_H
