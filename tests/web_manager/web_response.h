#ifndef WEB_RESPONSE_H
#define WEB_RESPONSE_H

#include "web_manager_global.h"

#include <qnetworkreply.h>

//#include "html_page.h"

#include <qjsonobject.h>
#include <qjsonarray.h>
#include <qjsondocument.h>
#include <qpixmap.h>

#define DEFAULT_ENCODING QByteArrayLiteral("utf-8")
#define RESPONSE_TYPE_PROPERTY QByteArrayLiteral("resp_type")
#define RESPONSE_ENCODING_PROPERTY QByteArrayLiteral("resp_enc")

namespace Web {
    class WEBMANAGERSHARED_EXPORT Response : public QNetworkReply {
        void initInfoFromContentHeader();
    public:
        enum ResponseType {
            rt_none = 0,
            rt_unknown,
            rt_html,
            rt_json,
            rt_js
        };

        static Response * fromReply(QNetworkReply * reply);

        inline int statusCode() const { return attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(); }
        inline bool hasErrors() { return error() != NoError; }
        inline void setUrl(const QUrl & url) { QNetworkReply::setUrl(url); }
        ResponseType reponseType();
        QByteArray encoding();

        Response * print();
        void printHeaders();
//        inline QString paramVal(const QString & param) { return QUrlQuery(url()).queryItemValue(param); }


        QUrl redirectUrl();
        Response * followByRedirect(QHash<QUrl, bool> prev_urls = QHash<QUrl, bool>());

        QUrlQuery toQuery(bool destroy = true);
        QByteArray toBytes(bool destroy = true);
        QString toText(bool destroy = true);
        QJsonObject toJson(const QString & wrap = QString(), bool destroy = true);
//        Html::Page toHtml(bool destroy = true);
        QPixmap toPixmap(bool destroy = true);
        QUrl toUrl(bool destroy = true);
        QUrl toRedirectUrl(bool destroy = true);
        QString toHeader(const QString & header_field, bool destroy = true) {
            QByteArray field_name = header_field.toUtf8();
            if (destroy) deleteLater();

            if (hasRawHeader(field_name))
                return QString(rawHeader(field_name));

            return QString();
        }
    protected:
        static QHash<QByteArray, ResponseType> response_predefined_types;
    };
}

#endif // WEB_RESPONSE_H
