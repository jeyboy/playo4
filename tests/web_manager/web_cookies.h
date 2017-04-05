#ifndef WEB_COOKIES_H
#define WEB_COOKIES_H

#include "web_manager_global.h"

#include "qnetworkcookie.h"
#include "qnetworkcookiejar.h"

namespace Web {
    class WEBMANAGERSHARED_EXPORT Cookies : public QNetworkCookieJar {
    public:
        inline explicit Cookies(QObject * parent = 0) : QNetworkCookieJar(parent) {}
        inline QList<QNetworkCookie> allCookies() const { return QNetworkCookieJar::allCookies(); }
    };
}

#endif // WEB_COOKIES_H
