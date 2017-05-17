#ifndef JSON_ARR_H
#define JSON_ARR_H

#include "json.h"
#include <qjsonarray.h>

class JSONSHARED_EXPORT JsonArr : public Json, public QJsonArray {
public:
    static JsonArr fromJsonStr(const QByteArray & text);
    static JsonArr fromJsonStr(const QByteArray & text, QString & error);
    static JsonArr fromJsonStr(const QString & text);
    static JsonArr fromJsonStr(const QString & text, QString & error);

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
    Json val(const int & index1, const int & index2);
    Json val(const int & index1, const QString & key2);

    JsonArr arr() const;
    JsonArr arr(const int & index);
    JsonArr arr(const int & index1, const int & index2);
    JsonArr arr(const int & index1, const QString & key2);
    JsonArr toArray() const;

    bool boolean(const int & index);
    bool boolean(const int & index1, const int & index2);
    bool boolean(const int & index1, const QString & key2);

    int integer(const int & index);
    int integer(const int & index1, const int & index2);
    int integer(const int & index1, const QString & key2);

    qint64 bigInt(const int & index);
    qint64 bigInt(const int & index1, const int & index2);
    qint64 bigInt(const int & index1, const QString & key2);

    double rational(const int & index1);
    double rational(const int & index1, const int & index2);
    double rational(const int & index1, const QString & key2);

    QString string(const int & index);
    QString string(const int & index1, const int & index2);
    QString string(const int & index1, const QString & key2);

    QString forceString(const int & index);
    QString forceString(const int & index1, const int & index2);
    QString forceString(const int & index1, const QString & key2);
};

#endif // JSON_ARR_H
