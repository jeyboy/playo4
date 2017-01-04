#ifndef JSON_OBJ_H
#define JSON_OBJ_H

#include "json_interface.h"
#include "json.h"

#include <qjsonobject.h>

#define JOBJ_KEY2(key1, key2) value(key1).toObject().value(key2)
#define JOBJ_BINT(val) (qint64)val.toDouble()

class JSONSHARED_EXPORT JsonObj : public QJsonObject, public JsonInterface {
public:
    static JsonObj fromText(const QString & text);

    JsonObj();
    JsonObj(const QJsonObject &);
    JsonObj & operator=(const QJsonObject & x);
    operator QJsonObject();

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

#endif // JSON_OBJ_H
