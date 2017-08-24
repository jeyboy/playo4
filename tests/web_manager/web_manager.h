#ifndef WEB_MANAGER_H
#define WEB_MANAGER_H

//#include <QtNetwork>

#include "qnetworkaccessmanager.h"
#include "variant_ptr.h"

#include "web_request_params.h"
#include "web_request.h"
#include "web_response.h"
#include "web_proxy.h"

#define MANAGER_PROPERTY_NAME "settings"
//#define SERIALIZE_JSON(json) (json.isArray() ? QJsonDocument(json.toArray()) : QJsonDocument(json.toObject())).toJson(QJsonDocument::Compact)
#define ERROR_OUTPUT(source) qCritical() << "IOERROR" << source -> error() << source -> url();

namespace Web {
    class ManagerController;

    class WEBMANAGERSHARED_EXPORT Manager : public QNetworkAccessManager {
        Q_OBJECT

        QSsl::SslProtocol protocol;
        QSslSocket::PeerVerifyMode mode;

        static QThread * main_thread;
        static Cookies default_cookies;
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
        Manager(QObject * parent = 0, QSsl::SslProtocol protocol = QSsl::TlsV1SslV3, QSslSocket::PeerVerifyMode mode = QSslSocket::VerifyNone);
        QNetworkReply * createRequest(Operation op, const QNetworkRequest & req, QIODevice * outgoingData = 0);

        Response * setupCallback(QNetworkReply * m_http, RequestParams * params);
        Response * proceed(QNetworkReply * m_http, RequestParams * params);
        Response * synchronizeRequest(QNetworkReply * m_http);
        void setup(const requestType & rtype, const Request & request, RequestParams * params);
        Response * sendSimple(const requestType & rtype, RequestParams * params);
        Response * sendData(const requestType & rtype, RequestDataParams * params);
    public:
        void setCookieJar(Cookies * cookieJar) {
            QNetworkAccessManager::setCookieJar(cookieJar);
            cookieJar -> setParent(0);
        }

//        qApp -> thread()
        static void setMainThreadSync(QThread * main) { main_thread = main; }

        static Manager * prepare();

        static Response * procHead(const QUrl & url, const bool & async = true) { return procHead(RequestParams::buildDefaultParams(url, async)); }
        static Response * procGet(const QUrl & url, const bool & async = true) { return procGet(RequestParams::buildDefaultParams(url, async)); }
        static Response * procDelete(const QUrl & url, const bool & async = true) { return procDelete(RequestParams::buildDefaultParams(url, async)); }

        static Response * procHead(RequestParams * params) { return prepare() -> sendSimple(rt_head, params); }
        static Response * procGet(RequestParams * params) { return prepare() -> sendSimple(rt_get, params); }
        static Response * procDelete(RequestParams * params) { return prepare() -> sendSimple(rt_delete, params); }

        static Response * procPost(RequestDataParams * params) { return prepare() -> sendData(rt_post, params); }
        static Response * procPut(RequestDataParams * params) { return prepare() -> sendData(rt_put, params); }
//       static Response * procCustom(RequestDataParams * params) { return prepare() -> sendSimple(rt_custom, params); }

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

        Response * sendHead(RequestParams * params) { return sendSimple(rt_head, params); }
        Response * sendGet(RequestParams * params) { return sendSimple(rt_get, params); }
        Response * sendDelete(RequestParams * params) { return sendSimple(rt_delete, params); }

        Response * sendPost(RequestDataParams * params) { return sendSimple(rt_post, params); }
        Response * sendPut(RequestDataParams * params) { return sendSimple(rt_put, params); }
//        Response * sendCustom(RequestParams * params) { return sendSimple(rt_custom, params); }

    protected slots:
        void requestFinished();

    signals:
        void requestCompleted(Response *);
    };

    class WEBMANAGERSHARED_EXPORT ManagerController : public QObject {
        Q_OBJECT
    protected slots:
        inline void disconnectThread() {
            qDebug() << "!!!!!!!!!!!!!!!!!!!! UNREGISTRATE MANAGER";
            Manager * tmanager = Manager::managers.take(sender());

//            // INFO: if last manager is closed then we removing all static data
//            if (Manager::managers.isEmpty()) {
//                Manager::default_cookies -> deleteLater();
//            }

            if (tmanager) tmanager -> deleteLater();
            deleteLater();
        }
    };
}

#endif // WEB_MANAGER_H

// #ifdef _WIN32 // Windows #include <winsock2.h> #include <ws2tcpip.h> #define MSG_NOSIGNAL 0 #else // Linuc + Max #include <sys/types.h> #include <sys/socket.h> #include <netinet/in.h> #include <arpa/inet.h> #include <unistd.h> #include <string.h> #include <netdb.h> #include <errno.h> #include <err.h> #define SOCKET_ERROR -1 #define INVALID_SOCKET -1 typedef int SOCKET; typedef sockaddr SOCKADDR; typedef sockaddr_in SOCKADDR_IN; #define closesocket close #ifdef __APPLE__ #define MSG_NOSIGNAL 0 #endif #endif #include <iostream> int main() { std::cout << " [*] C++ Tor Exmaple " << std::endl; std::cout << " [*] By Yaseen Eltii " << std::endl; std::cout << " [*] Connecting " << std::endl; SOCKET Socket; SOCKADDR_IN SocketAddr; Socket = socket(AF_INET, SOCK_STREAM, 0); SocketAddr.sin_family = AF_INET; SocketAddr.sin_port = htons(9050); SocketAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); connect(Socket, (SOCKADDR*)&SocketAddr, sizeof(SOCKADDR_IN)); char Req1[3] = { 0x05, // SOCKS 5 0x01, // One Authentication Method 0x00 // No AUthentication }; send(Socket, Req1, 3, MSG_NOSIGNAL); char Resp1[2]; recv(Socket, Resp1, 2, 0); if(Resp1[1] != 0x00) { std::cout << " [*] Error Authenticating " << std::endl; return(-1); // Error } #ifdef IPV4_TEST char* IpAddr = "104.236.192.175"; int IpAddrInt = inet_addr(IpAddr); short Port = htons(80); char Req2[10] = { 0x05, // SOCKS5 0x01, // CONNECT 0x00, // RESERVED 0x01, // IPV4 }; // Copy the IP memcpy(Req2+4, &IpAddrInt, 4); // Copy The Port memcpy(Req2+4+4, &Port, 2); // Send send(Socket, Req2, 10, 0); #else char* Domain = "facebookcorewwwi.onion"; char DomainLen = (char)strlen(Domain); short Port = htons(80); char TmpReq[4] = { 0x05, // SOCKS5 0x01, // CONNECT 0x00, // RESERVED 0x03, // DOMAIN }; char* Req2 = new char[4 + 1 + DomainLen + 2]; memcpy(Req2, TmpReq, 4); // 5, 1, 0, 3 memcpy(Req2 + 4, &DomainLen, 1); // Domain Length memcpy(Req2 + 5, Domain, DomainLen); // Domain memcpy(Req2 + 5 + DomainLen, &Port, 2); // Port send(Socket, (char*)Req2, 4 + 1 + DomainLen + 2, MSG_NOSIGNAL); delete[] Req2; #endif char Resp2[10]; recv(Socket, Resp2, 10, 0); if(Resp2[1] != 0x00) { std::cout << " [*] Error : " << Resp2[1] << std::endl; return(-1); // ERROR } std::cout << " [*] Connected " << std::endl; // Here you can normally use send and recv // Testing With a HTTP GET Request std::cout << " [*] Testing with GET Request \n" << std::endl; send(Socket, "GET / \n\r\n\r", strlen("GET / \n\r\n\r"), MSG_NOSIGNAL); char RecvBuffer[2048]; size_t Rcved = recv(Socket, RecvBuffer, 2048, 0); std::cout.write(RecvBuffer, Rcved); std::cout << std::endl; return(0); }
