#include "web_manager.h"

#include "web_connection.h"

#include <qeventloop.h>

using namespace Web;

//////////////////////////     WEB_MANAGER     /////////////////////////////
QThread * Manager::main_thread = 0;
QHash<QObject *, Manager *> Manager::managers = QHash<QObject *, Manager *>();
Cookies * Manager::default_cookies = new Cookies();

Manager * Manager::prepare() {
    QThread * thread = QThread::currentThread();
    if (!managers.contains(thread)) {
        qDebug() << "!!!!!!!!!!!!!!!!!!!! REGISTRATE MANAGER";
        managers.insert(thread, new Manager());

        if (thread != main_thread)
            connect(thread, SIGNAL(finished()), new ManagerController(), SLOT(disconnectThread()));
    }
    return managers[thread];
}

Manager::Manager(QObject * parent, QSsl::SslProtocol protocol, QSslSocket::PeerVerifyMode mode) : QNetworkAccessManager(parent) {
    this -> protocol = protocol;
    this -> mode = mode;
//    this -> setCookieJar(Manager::default_cookies);
}

Response * Manager::synchronizeRequest(QNetworkReply * m_http) {
//            QTimer timer;
//            timer.setSingleShot(true);

    QEventLoop loop;
//            connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
    connect(m_http, SIGNAL(finished()), &loop, SLOT(quit()));
//            timer.start(10000);   // 10 secs. timeout
    loop.exec();

    //    if(timer.isActive()) {
    //        timer.stop();
    //        if(m_http -> error() > 0) {
    //          ... // handle error
    //        }
    //        else {
    //          int v = m_http -> attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    //          if (v >= 200 && v < 300) {  // Success
    //            ...
    //          }
    //        }
    //    } else {
    //       // timeout
    //       disconnect(m_http, SIGNAL(finished()), &loop, SLOT(quit()));

    //       m_http -> abort();
    //    }

    if (m_http -> error() == Response::HostNotFoundError)
        WebConnection::obj().check();

    return Response::fromReply(m_http);
}

void Manager::setup(const requestType & rtype, const Request & request, RequestParams * params) {
    Cookies * curr_cookies = params -> cookies ? params -> cookies : default_cookies;
    setCookieJar(curr_cookies);

    if (params -> isPrintParams()) {
        QByteArray rtype_name;

        switch(rtype) {
            case rt_head: { rtype_name = QByteArrayLiteral("HEAD"); break;}
            case rt_get: { rtype_name = QByteArrayLiteral("GET"); break;}
            case rt_delete: { rtype_name = QByteArrayLiteral("DELETE"); break;}
            case rt_post: { rtype_name = QByteArrayLiteral("POST"); break;}
            case rt_put: { rtype_name = QByteArrayLiteral("PUT"); break;}
            default: rtype_name = QByteArrayLiteral("CUSTOM");
        }

        qInfo()
            << "*** " << rtype_name << (params -> isAsync() ? QByteArrayLiteral("ASYNC") : QByteArrayLiteral("")) << params -> url.toString() << QByteArrayLiteral("\r\n")
            << "*** H:" << request.headersStr();
        curr_cookies -> print(params -> url);
    }
}

Response * Manager::setupCallback(QNetworkReply * m_http, RequestParams * params) {
//    asyncRequests.insert(params -> url(), params);
    connect(m_http, SIGNAL(finished()), this, SLOT(requestFinished()));
    return Response::fromReply(m_http);
}

Response * Manager::proceed(QNetworkReply * m_http, RequestParams * params) {
    m_http -> setProperty(MANAGER_PROPERTY_NAME, VariantPtr<RequestParams>::asQVariant(params));

    if (params -> isAsync())
        return setupCallback(m_http, params);
    else {
        Response * resp = synchronizeRequest(m_http);
        return params -> isFollowed() ? resp -> followByRedirect() : resp;
    }
}

Response * Manager::sendSimple(const requestType & rtype, RequestParams * params) {
    Request request(params);
    setup(rtype, request, params);

    QNetworkReply * m_http;

    switch(rtype) {
        case rt_get: { m_http = QNetworkAccessManager::get(request); break; }
        case rt_delete: { m_http = QNetworkAccessManager::deleteResource(request); break; }
        default: m_http = QNetworkAccessManager::head(request);
    }

    return proceed(m_http, params);
}
Response * Manager::sendData(const requestType & rtype, RequestDataParams * params) {
    Request request(params);
    setup(rtype, request, params);

    QNetworkReply * m_http;

    switch(rtype) {
        case rt_post: { m_http = QNetworkAccessManager::post(request, params -> data); break; }
        case rt_put: { m_http = QNetworkAccessManager::put(request, params -> data); break; }
        default: return 0; //m_http = QNetworkAccessManager::head(request);
    }

    return proceed(m_http, params);
}

QNetworkReply * Manager::createRequest(Operation op, const QNetworkRequest & req, QIODevice * outgoingData) {
    QSslConfiguration config = req.sslConfiguration();
    config.setPeerVerifyMode(mode);
    config.setProtocol(protocol);
    (const_cast<QNetworkRequest &>(req)).setSslConfiguration(config);
    return QNetworkAccessManager::createRequest(op, req, outgoingData);
}
