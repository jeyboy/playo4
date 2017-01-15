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

    Json operator[](const int & index);
    Json val(const int & index);

    JsonArr arr() const;
    JsonArr toArray() const;

    bool boolean(const int & index);

    int integer(const int & index);

    qint64 bigInt(const int & index);

    QString string(const int & index);

    QString forceString(const int & index);
};

#endif // JSON_ARR_H
