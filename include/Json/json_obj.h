#ifndef JSON_OBJ_H
#define JSON_OBJ_H

#include "json_interface.h"

#include <qjsonobject.h>

class Json;

class JSONSHARED_EXPORT JsonObj : public QJsonObject/*, public IJson*/ {
public:
    static JsonObj fromText(const QString & text);

    JsonObj();
    JsonObj(const QJsonObject &);
    JsonObj & operator=(const QJsonObject & x);
    operator QJsonObject();

    bool hasKey(const QString & key);

    QString concatKeys(const QString & key1, const QString & key2, const QString & separator);

    Json operator[](const QString & key);
    Json val(const QString & key);
    Json val2(const QString & key1, const QString & key2);

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

#endif // JSON_OBJ_H
