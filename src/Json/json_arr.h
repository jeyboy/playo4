#ifndef JSON_ARR_H
#define JSON_ARR_H

#include "json.h"
#include <qjsonarray.h>

class JSONSHARED_EXPORT JsonArr : public Json, public QJsonArray {
public:
    static JsonArr fromJsonStr(const QByteArray & text);
    static JsonArr fromJsonStr(const QString & text);

    QByteArray toJsonStr(const JsonFormat & format = Compact);
    QVariant toVariant() const;

    JsonArr();
    JsonArr(const QJsonArray & oth);
    JsonArr & operator=(const QJsonArray & x);

    operator QJsonArray() const;
    operator Json() const;

    Json::Type type() const;

    inline bool isArray() const { return true; }

    int size();

    QString concatKeys(const QString & key, const QString & separator);
    QString concatKeys(const QString & separator);

    Json operator[](const int & index);
    Json val(const int & index);
    Json val2(const int & index1, const int & index2);
    Json val2(const int & index1, const QString & key2);

    JsonArr arr() const;
    JsonArr toArray() const;

    bool boolean(const int & index);
    bool boolean2(const int & index1, const int & index2);
    bool boolean2(const int & index1, const QString & key2);

    int integer(const int & index);
    int integer2(const int & index1, const int & index2);
    int integer2(const int & index1, const QString & key2);

    qint64 bigInt(const int & index);
    qint64 bigInt2(const int & index1, const int & index2);
    qint64 bigInt2(const int & index1, const QString & key2);

    double rational2(const int & index1);
    double rational2(const int & index1, const int & index2);
    double rational2(const int & index1, const QString & key2);

    QString string(const int & index);
    QString string2(const int & index1, const int & index2);
    QString string2(const int & index1, const QString & key2);

    QString forceString(const int & index);
    QString forceString2(const int & index1, const int & index2);
    QString forceString2(const int & index1, const QString & key2);
};

#endif // JSON_ARR_H
