#include "web_manager.h"

#include "web_connection.h"

#include <qeventloop.h>

using namespace Web;

//////////////////////////     WEB_MANAGER     /////////////////////////////

QHash<QObject *, Manager *> Manager::managers = QHash<QObject *, Manager *>();
Cookies * Manager::cookies = new Cookies(QApplication::instance());

void Manager::loadCookies(const QJsonObject & store) {
    QJsonArray arr = store.value(COOKIES_KEY).toArray();
    for(QJsonValue const & cookie: arr) {
        QList<QNetworkCookie> items = QNetworkCookie::parseCookies(cookie.toString().toUtf8());
        for(QNetworkCookie & item: items)
            cookies -> insertCookie(item);
    }
}

void Manager::saveCookies(QJsonObject & store, const QUrl & url) {
    QList<QNetworkCookie> cookiesList = url.isEmpty() ? cookies -> allCookies() : cookies -> cookiesForUrl(url);
    QJsonArray cookiesArray;
    for(auto const & cookie: cookiesList)
        cookiesArray << QJsonValue::fromVariant(cookie.toRawForm());

    store.insert(COOKIES_KEY, cookiesArray);
}

Manager * Manager::prepare() {
    QThread * thread = QThread::currentThread();
    if (!managers.contains(thread)) {
        qDebug() << "!!!!!!!!!!!!!!!!!!!! REGISTRATE MANAGER";
        managers.insert(thread, new Manager());

        if (thread != QApplication::instance() -> thread())
            connect(thread, SIGNAL(finished()), new ManagerController(), SLOT(disconnectThread()));
    }
    return managers[thread];
}

Manager::Manager(QObject * parent, QSsl::SslProtocol protocol, QSslSocket::PeerVerifyMode mode)
    : QNetworkAccessManager(parent), extract_params_to_payload(true) {
    this -> protocol = protocol;
    this -> mode = mode;
    this -> setCookieJar(Manager::cookies);
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

QNetworkReply * Manager::createRequest(Operation op, const QNetworkRequest & req, QIODevice * outgoingData) {
    QSslConfiguration config = req.sslConfiguration();
    config.setPeerVerifyMode(mode);
    config.setProtocol(protocol);
    (const_cast<QNetworkRequest &>(req)).setSslConfiguration(config);
    return QNetworkAccessManager::createRequest(op, req, outgoingData);
}
