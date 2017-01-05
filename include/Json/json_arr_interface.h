#ifndef JSON_ARR_INTERFACE_H
#define JSON_ARR_INTERFACE_H

#include "json_global.h"

class Json;

class JSONSHARED_EXPORT JsonArrInterface {
public:
    virtual QString concatKeys(const QString & key, const QString & separator) = 0;

    virtual Json operator[](const int & index) = 0;
    virtual Json val(const int & index) = 0;

    virtual bool boolean(const int & index) = 0;
//    virtual bool boolean2(const QString & key1, const QString & key2) = 0;

    virtual int integer(const int & index) = 0;
//    virtual int integer2(const QString & key1, const QString & key2) = 0;

    virtual qint64 bigInt(const int & index) = 0;
//    virtual qint64 bigInt2(const QString & key1, const QString & key2) = 0;

    virtual QString string(const int & index) = 0;
//    virtual QString string(const QString & key, const QString & default_val) = 0;
//    virtual QString string2(const QString & key1, const QString & key2) = 0;

    virtual QString stringConv(const int & index) = 0;
//    virtual QString stringConv2(const QString & key1, const QString & key2) = 0;
};


#endif // JSON_ARR_INTERFACE_H
