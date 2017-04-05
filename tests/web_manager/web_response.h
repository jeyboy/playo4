#ifndef WEB_RESPONSE_H
#define WEB_RESPONSE_H

#include "web_manager_global.h"

#include <qnetworkreply.h>

#include "html_page.h"

#include <qjsonobject.h>
#include <qjsonarray.h>
#include <qjsondocument.h>
#include <qpixmap.h>

namespace Web {
    class WEBMANAGERSHARED_EXPORT Response : public QNetworkReply {
    public:
        static Response * fromReply(QNetworkReply * reply);

        void setUrl(const QUrl & url) { QNetworkReply::setUrl(url); }

        inline void printHeaders() {
            QList<RawHeaderPair> headers = rawHeaderPairs();

            qDebug() << "------------ HEADERS LIST ----------------";

            for(QList<RawHeaderPair>::ConstIterator it = headers.cbegin(); it != headers.cend(); it++)
                qDebug() << (*it).first << (*it).second;

            qDebug() << "------------ END OF LIST ----------------";
        }

        inline QByteArray encoding() {
            QString content_type = header(QNetworkRequest::ContentTypeHeader).toString();
            QStringList parts = content_type.split(QStringLiteral("charset="));

            if (parts.length() == 1)
                return QStringLiteral("utf-8").toUtf8();
            else
                return parts.last().toUtf8();
        }
        inline bool hasErrors() { return error() != NoError; }
        inline int status() { return attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(); }
        inline QUrl redirectUrl() {
            QVariant possibleRedirectUrl = attribute(QNetworkRequest::RedirectionTargetAttribute);
            if (possibleRedirectUrl.isValid()) {
                QUrl new_url = possibleRedirectUrl.toUrl();

                if (new_url.isRelative())
                    new_url = url().resolved(new_url);

                return new_url;

            } else return QUrl();
        }
        inline void appendHeaders(QUrl & url) {
            QString urlStr = QStringLiteral("%1\r\nReferer: %2").arg(url.toString(), QString(request().rawHeader("Referer")));
            url = QUrl(urlStr);
        }
        inline QString paramVal(const QString & param) { return QUrlQuery(url()).queryItemValue(param); }

        Response * followByRedirect(QHash<QUrl, bool> prev_urls = QHash<QUrl, bool>());
        QUrlQuery toQuery(bool destroy = true);
        QByteArray toBytes(bool destroy = true);
        QString toText(bool destroy = true);
        QJsonObject toJson(const QString & wrap = QString(), bool destroy = true);
        Html::Page toHtml(bool destroy = true);
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
        Response * output() {
            qDebug() << "-------------------------";
            qDebug() << "URL:" << toUrl(false);
            qDebug() << "REDIRECT URL:" << toRedirectUrl(false);
            qDebug() << "HEADERS:" << rawHeaderPairs();
            qDebug() << "-------------------------";

            return this;
        }
    };
}

#endif // WEB_RESPONSE_H
