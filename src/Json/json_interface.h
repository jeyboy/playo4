#ifndef JSON_INTERFACE_H
#define JSON_INTERFACE_H

#include "json_global.h"

class JSONSHARED_EXPORT JsonInterface {
public:
    bool hasKey(const QString & key);

    // concat keys from obj hash
    virtual QString concatKeys(const QString & key1, const QString & key2, const QString & separator) = 0;
    // concat key from array of objs
    virtual QString concatKeys(const QString & key, const QString & separator) = 0;

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
};

#endif // JSON_INTERFACE_H
