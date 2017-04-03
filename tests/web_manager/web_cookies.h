#ifndef WEB_COOKIES_H
#define WEB_COOKIES_H

#include "qnetworkcookie.h"
#include "qnetworkcookiejar.h"

namespace Web {
    class Cookies : public QNetworkCookieJar {
    public:
        inline explicit Cookies(QObject * parent = 0) : QNetworkCookieJar(parent) {}
        inline QList<QNetworkCookie> allCookies() const { return QNetworkCookieJar::allCookies(); }
    };
}

#endif // WEB_COOKIES_H
