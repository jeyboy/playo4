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

QNetworkReply * Manager::createRequest(Operation op, const QNetworkRequest & req, QIODevice * outgoingData) {
    QSslConfiguration config = req.sslConfiguration();
    config.setPeerVerifyMode(mode);
    config.setProtocol(protocol);
    (const_cast<QNetworkRequest &>(req)).setSslConfiguration(config);
    return QNetworkAccessManager::createRequest(op, req, outgoingData);
}
