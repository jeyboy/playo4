#ifndef WEB_REQUEST_H
#define WEB_REQUEST_H

#include "web_manager_global.h"

#include "qnetworkrequest.h"

namespace Web {
    class Headers;
    class Manager;
    class Response;

    class WEBMANAGERSHARED_EXPORT Request : public QNetworkRequest {
    public:
        inline Request(Manager * manager, const QString & url_str) : QNetworkRequest(QUrl(url_str)), manager(manager) {}
        inline Request(Manager * manager, const QUrl & url = QUrl()) : QNetworkRequest(url), manager(manager) {}

        Request withHeaders(const Headers & headers);
        Response * viaGet(bool async = false);
        Response * viaPost(const QByteArray & data = QByteArray(), const QString & content_type = FORM_URLENCODE, bool async = false);
        Response * viaPut(const QByteArray & data = QByteArray(), const QString & content_type = FORM_URLENCODE, bool async = false);
        Response * viaForm(const QByteArray & data = QByteArray(), bool async = false);

        static QByteArray extractParams(QUrl & url) {
            QByteArray params = url.query().toUtf8();
            url.setQuery(QString());
            return params;
        }
    private:
        Manager * manager;
    };
}

#endif // WEB_REQUEST_H
