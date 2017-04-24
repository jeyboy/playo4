#ifndef WEB_MANAGER_H
#define WEB_MANAGER_H

//#include <QtNetwork>

#include "qnetworkaccessmanager.h"
//#include "qnetworkproxy.h"

#include "web_request_params.h"
#include "web_request.h"
#include "web_response.h"

#define SERIALIZE_JSON(json) (json.isArray() ? QJsonDocument(json.toArray()) : QJsonDocument(json.toObject())).toJson(QJsonDocument::Compact)

namespace Web {
    class ManagerController;

    class WEBMANAGERSHARED_EXPORT Manager : public QNetworkAccessManager {
        Q_OBJECT

        QSsl::SslProtocol protocol;
        QSslSocket::PeerVerifyMode mode;

        static QThread * main_thread;
        static Cookies * default_cookies;
        static QHash<QObject *, Manager *> managers;

        friend class ManagerController;

        enum requestType {
            rt_custom = 0,
            rt_head,
            rt_get,
            rt_delete,
            rt_post,
            rt_put
        };
    protected:
        QHash<QUrl, Func> asyncRequests;

        Manager(QObject * parent = 0, QSsl::SslProtocol protocol = QSsl::TlsV1SslV3, QSslSocket::PeerVerifyMode mode = QSslSocket::VerifyNone);
        QNetworkReply * createRequest(Operation op, const QNetworkRequest & req, QIODevice * outgoingData = 0);

        Response * synchronizeRequest(QNetworkReply * m_http);

        void setup(const requestType & rtype, const Request & request, const RequestParams & params);
        Response * sendSimple(const requestType & rtype, const RequestParams & params);
        Response * sendData(const requestType & rtype, const RequestDataParams & params);
    public:
//        QApplication::instance() -> thread()
        static setMainThreadSync(QThread * main) { main_thread = main; }

        static Manager * prepare();

//        inline QJsonObject jsonGet(const QUrl & url, const QString & wrap) { return getFollowed(url) -> toJson(wrap); }
//        inline QJsonObject jsonGet(const QUrl & url, bool wrap = false) { return getFollowed(url) -> toJson(wrap ? DEF_JSON_FIELD : QString()); }
//        inline QJsonObject jsonGet(const QUrl & url, const Headers & headers, const QString & wrap) { return getFollowed(url, headers) -> toJson(wrap); }
//        inline QJsonObject jsonGet(const QUrl & url, const Headers & headers, bool wrap = false) { return getFollowed(url, headers) -> toJson(wrap ? DEF_JSON_FIELD : QString()); }
//        inline QJsonObject jsonPost(const QUrl & url, const QString & wrap) { return postFollowed(url) -> toJson(wrap); }
//        inline QJsonObject jsonPost(const QUrl & url, bool wrap = false) { return postFollowed(url) -> toJson(wrap ? DEF_JSON_FIELD : QString()); }
//        inline QJsonObject jsonPost(const QUrl & url, const Headers & headers, const QString & wrap) { return postFollowed(url, headers) -> toJson(wrap); }
//        inline QJsonObject jsonPost(const QUrl & url, const Headers & headers, bool wrap = false) { return postFollowed(url, headers) -> toJson(wrap ? DEF_JSON_FIELD : QString()); }
//        inline QJsonObject jsonPost(const QUrl & url, const Headers & headers, const QString & content_type, const QByteArray & payload, bool wrap = false) {
//            return postFollowed(url, headers, content_type, payload)
//                -> toJson(wrap ? DEF_JSON_FIELD : QString());
//        }
//        inline QJsonObject jsonPost(const QUrl & url, const Headers & headers, const QJsonValue & payload, bool wrap = false) {
//            return postFollowed(url, headers, QStringLiteral("application/json"), SERIALIZE_JSON(payload))
//                -> toJson(wrap ? DEF_JSON_FIELD : QString());
//        }

//        inline QPixmap pixmapGet(const QUrl & url) { return getFollowed(url) -> toPixmap(); }
//        inline Response * pixmapGetAsync(const QUrl & url, const Func & response) {
//            Response * resp = requestTo(url).viaGet(true) -> followByRedirect();
//            connect(resp, SIGNAL(finished()), this, SLOT(pixmapRequestFinished()));
//            asyncRequests.insert(resp -> url(), response);
//            return resp;
//        }

//        inline Response * getFollowed(const QUrl & url) { return requestTo(url).viaGet() -> followByRedirect(); }
//        inline Response * getFollowed(const QUrl & url, const Headers & headers) { return requestTo(url).withHeaders(headers).viaGet() -> followByRedirect(); }
//        inline Response * getFollowedAsync(const QUrl & url, const Func & response) {
//            Response * resp = requestTo(url).viaGet(true);
//            connect(resp, SIGNAL(finished()), this, SLOT(requestFinished()));
//            asyncRequests.insert(resp -> url(), response);
//            return resp;
//        }

//        inline Response * postFollowed(const QUrl & url, const QString & content_type = FORM_URLENCODE, const QByteArray & payload = QByteArray()) {
//            return requestTo(url).viaPost(payload, content_type) -> followByRedirect();
//        }
//        inline Response * postFollowed(const QUrl & url, const Headers & headers, const QString & content_type = FORM_URLENCODE, const QByteArray & payload = QByteArray()) {
//            return requestTo(url).withHeaders(headers).viaPost(payload, content_type) -> followByRedirect();
//        }
//        inline Response * postFollowedAsync(const QUrl & url, const Func & response, const Headers & headers, const QString & content_type = FORM_URLENCODE, const QByteArray & payload = QByteArray()) {
//            Response * resp = requestTo(url).withHeaders(headers).viaPost(payload, content_type, true);
//            connect(resp, SIGNAL(finished()), this, SLOT(requestFinished()));
//            asyncRequests.insert(resp -> url(), response);
//            return resp;
//        }

//        inline Response * putFollowed(const QUrl & url, const QByteArray & data = QByteArray(), const QString & content_type = FORM_URLENCODE) {
//            return requestTo(url).viaPut(data, content_type) -> followByRedirect();
//        }
//        inline Response * putFollowed(const QUrl & url, const Headers & headers, const QByteArray & data = QByteArray(), const QString & content_type = FORM_URLENCODE) {
//            return requestTo(url).withHeaders(headers).viaPut(data, content_type) -> followByRedirect();
//        }

//        inline Response * form(const QUrl & url) { return requestTo(url).viaForm(); }
//        inline Response * form(const QUrl & url, const Headers & headers) { return requestTo(url).withHeaders(headers).viaForm(); }
//        inline Response * form(const QUrl & url, const QByteArray & data) { return requestTo(url).viaForm(data); }
//        inline Response * form(const QUrl & url, const QByteArray & data, const Headers & headers) { return requestTo(url).withHeaders(headers).viaForm(data); }

//        inline Response * formFollowed(const QUrl & url) { return requestTo(url).viaForm() -> followByRedirect(); }
//        inline Response * formFollowed(const QUrl & url, const QByteArray & data) { return requestTo(url).viaForm(data) -> followByRedirect(); }
//        inline Response * formFollowed(const QUrl & url, const Headers & headers) { return requestTo(url).withHeaders(headers).viaForm() -> followByRedirect(); }
//        inline Response * formFollowed(const QUrl & url, const QByteArray & data, const Headers & headers) { return requestTo(url).withHeaders(headers).viaForm(data) -> followByRedirect(); }

    public slots:
//        inline void sendGet(const QString & url) { getFollowed(url) -> deleteLater(); }

        Response * sendHead(const RequestParams & params) { return sendSimple(rt_head, params); }
        Response * sendGet(const RequestParams & params) { return sendSimple(rt_get, params); }
        Response * sendDelete(const RequestParams & params) { return sendSimple(rt_delete, params); }

        Response * sendPost(const RequestDataParams & params) { return sendSimple(rt_post, params); }
        Response * sendPut(const RequestDataParams & params) { return sendSimple(rt_put, params); }
//        Response * sendCustom(const RequestParams & params) { return sendSimple(rt_custom, params); }

    protected slots:
        inline void requestFinished() {
            Response * source = Response::fromReply((QNetworkReply *)sender());
            Func func = asyncRequests.take(source -> url());
            QUrl new_url = source -> redirectUrl();

            if (!new_url.isEmpty()) {
                source -> appendHeaders(new_url);
                getFollowedAsync(new_url, func);
            } else QMetaObject::invokeMethod(func.obj, func.slot, Q_ARG(Response *, source), Q_ARG(void *, func.user_data));
        }

//        inline void pixmapRequestFinished() {
//            Response * source = (Response *)sender();
//            Func func = asyncRequests.take(source -> url());
//            QMetaObject::invokeMethod(func.obj, func.slot, Q_ARG(QPixmap, source -> toPixmap()));
//        }
    };

    class WEBMANAGERSHARED_EXPORT ManagerController : public QObject {
        Q_OBJECT
    protected slots:
        inline void disconnectThread() {
            qDebug() << "!!!!!!!!!!!!!!!!!!!! UNREGISTRATE MANAGER";
            Manager * tmanager = Manager::managers.take(sender());
            if (tmanager) tmanager -> deleteLater();
            deleteLater();
        }
    };
}

#endif // WEB_MANAGER_H
