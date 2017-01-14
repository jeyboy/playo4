#ifndef JSON_OBJ_INTERFACE_H
#define JSON_OBJ_INTERFACE_H

#include "json_global.h"

class Json;

#define JOBJ_KEY2SS(key1, key2) value(key1).toObject().value(key2)
#define JOBJ_KEY2II(index1, index2) at(index1).toArray()[index2]
#define JOBJ_KEY2IS(index1, key2) at(index1).toObject().value(key2)
#define JOBJ_KEY2SI(key1, index2) value(key1).toArray()[index2]

class JSONSHARED_EXPORT IJson {
public:
    virtual int size() = 0;

    virtual bool hasKey(const QString & key) = 0;
    virtual bool hasIndex(const int & index) = 0;

    virtual QString concatKeys(const QString & key1, const QString & key2, const QString & separator) = 0;

    virtual Json operator[](const QString & key) = 0;
    virtual Json val(const QString & key) = 0;
    virtual Json val2(const QString & key1, const QString & key2) = 0;

    virtual bool boolean(const QString & key) = 0;
    virtual bool boolean2(const QString & key1, const QString & key2) = 0;

    virtual int integer(const QString & key) = 0;
    virtual int integer2(const QString & key1, const QString & key2) = 0;

    virtual qint64 bigInt(const QString & key) = 0;
    virtual qint64 bigInt2(const QString & key1, const QString & key2) = 0;

    virtual QString string(const QString & key) = 0;
    virtual QString string(const QString & key, const QString & default_val) = 0;
    virtual QString string2(const QString & key1, const QString & key2) = 0;

    virtual QString stringConv(const QString & key) = 0;
    virtual QString stringConv2(const QString & key1, const QString & key2) = 0;


    virtual QString concatKeys(const QString & key, const QString & separator) = 0;

    virtual Json operator[](const int & index) = 0;
    virtual Json val(const int & index) = 0;

    virtual bool boolean(const int & index) = 0;
    virtual bool boolean2(const int & index1, const int & index2) = 0;

    virtual int integer(const int & index) = 0;
    virtual int integer2(const int & index1, const int & index2) = 0;

    virtual qint64 bigInt(const int & index) = 0;
    virtual qint64 bigInt2(const int & index1, const int & index2) = 0;

    virtual QString string(const int & index) = 0;
//    virtual QString string(const QString & key, const QString & default_val) = 0;
    virtual QString string2(const int & index1, const int & index2) = 0;

    virtual QString stringConv(const int & index) = 0;
    virtual QString stringConv2(const int & index1, const int & index2) = 0;
};

#endif // JSON_OBJ_INTERFACE_H
