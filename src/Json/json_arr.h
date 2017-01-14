#ifndef JSON_ARR_H
#define JSON_ARR_H

#include "json.h"
#include <qjsonarray.h>

class JSONSHARED_EXPORT JsonArr : public Json, public QJsonArray {
public:
    static JsonArr fromText(const QString & text);

    JsonArr();
    JsonArr(const QJsonArray &);
    JsonArr & operator=(const QJsonArray & x);
    operator QJsonArray();

    QString concatKeys(const QString & key, const QString & separator);

    Json operator[](const int & index);
    Json val(const int & index);

    bool boolean(const int & index);

    int integer(const int & index);

    qint64 bigInt(const int & index);

    QString string(const int & index);

    QString stringConv(const int & index);
};

#endif // JSON_ARR_H
