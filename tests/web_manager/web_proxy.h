#ifndef WEB_PROXY_H
#define WEB_PROXY_H

#include "web_manager_global.h"

#include "country.h"
#include "qnetworkproxy.h"

namespace Web {
    class WEBMANAGERSHARED_EXPORT Proxy : public QNetworkProxy {
        QByteArray country;
        float response_time;
        float response_rate;
        bool encrypted;
    public:
        enum ManagerProxyType {
            pt_any = -1,

            pt_system = 0,
            pt_tor = 1,

            pt_ssl = 1 << 1,

            pt_http = 1 << 2,
            pt_https = 1 << 3 | pt_ssl,
            pt_socks5 = 1 << 4,
            pt_socks5s = 1 << 5 | pt_ssl,
        };

        Proxy(const ManagerProxyType & ptype = pt_system, const QString & hostName = QString(),
            quint16 port = 0, const QByteArray & country = QByteArray(),
            const float & response_time = 0, const float & response_rate = 0,
            const QString & user = QString(), const QString & password = QString()) :
                QNetworkProxy(HttpProxy, hostName, port, user, password), country(country),
                response_time(response_time), response_rate(response_rate), encrypted(ptype == pt_https || ptype == pt_socks5s) {}

        static Proxy * find(const ManagerProxyType & ptype = pt_any, const QByteArray & country = QByteArray());

    private:
        static Proxy * findinSource1(const ManagerProxyType & ptype = pt_any, const QByteArray & country = QByteArray());
        static Proxy * findinSource2(const ManagerProxyType & ptype = pt_any, const QByteArray & country = QByteArray());
        static Proxy * findinSource3(const ManagerProxyType & ptype = pt_any, const QByteArray & country = QByteArray());
        static Proxy * findinSource4(const ManagerProxyType & ptype = pt_any, const QByteArray & country = QByteArray());
        static Proxy * findinSource5(const ManagerProxyType & ptype = pt_any, const QByteArray & country = QByteArray());
    };
}

#endif // WEB_PROXY_H
