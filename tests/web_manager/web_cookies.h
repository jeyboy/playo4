#ifndef WEB_COOKIES_H
#define WEB_COOKIES_H

#include "web_manager_global.h"

#include "qnetworkcookie.h"
#include "qnetworkcookiejar.h"


#include <qdebug.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

namespace Web {
    class WEBMANAGERSHARED_EXPORT Cookies : public QNetworkCookieJar {
    public:
        static Cookies * loadCookies(const QJsonObject & store) {
            Cookies * cookies = new Cookies();

            QJsonArray arr = store.value(COOKIES_KEY).toArray();
            for(QJsonValue const & cookie: arr) {
                QList<QNetworkCookie> items = QNetworkCookie::parseCookies(cookie.toString().toUtf8());
                for(QNetworkCookie & item: items)
                    cookies -> insertCookie(item);
            }

            return cookies;
        }

        void saveCookies(QJsonObject & store, const QUrl & url = QUrl()) {
            QList<QNetworkCookie> cookiesList = url.isEmpty() ? allCookies() : cookiesForUrl(url);
            QJsonArray cookiesArray;
            for(auto const & cookie: cookiesList)
                cookiesArray << QJsonValue(QString(cookie.toRawForm()));

            store.insert(COOKIES_KEY, cookiesArray);
        }

        inline explicit Cookies(QObject * parent = 0) : QNetworkCookieJar(parent) {}
        inline QList<QNetworkCookie> allCookies() const { return QNetworkCookieJar::allCookies(); }

        void appendCookie(const QByteArray & cookies_data) {
            QList<QNetworkCookie> items = QNetworkCookie::parseCookies(cookies_data);
            for(QNetworkCookie & item: items)
                insertCookie(item);
        }

        void removeCookies(const QUrl & url = QUrl()) {
            const QList<QNetworkCookie> items = url.isEmpty() ? allCookies() : cookiesForUrl(url);
            for(QList<QNetworkCookie>::ConstIterator cookie = items.cbegin(); cookie != items.cend(); cookie++)
                deleteCookie(*cookie);
        }

        void print(const QUrl & url = QUrl()) {
//                qDebug() << "COOKIE" << cookies -> allCookies();

            qDebug() << " ----------------------- COOKIES LIST ----------------------------";

            const QList<QNetworkCookie> items = url.isEmpty() ? allCookies() : cookiesForUrl(url);
            for(QList<QNetworkCookie>::ConstIterator cookie = items.cbegin(); cookie != items.cend(); cookie++)
                qDebug() << (*cookie).toRawForm();

            qDebug() << " -----------------------------------------------------------------";
        }

        QByteArray asHeaderStr(const QUrl & url = QUrl(), const QHash<QByteArray, bool> & acceptable = QHash<QByteArray, bool>()) {
            QByteArray res;
            bool ignore_filter = acceptable.isEmpty();

            const QList<QNetworkCookie> items = url.isEmpty() ? allCookies() : cookiesForUrl(url);
            for(QList<QNetworkCookie>::ConstIterator cookie = items.cbegin(); cookie != items.cend(); cookie++) {
                QByteArray name = (*cookie).name();
                if (ignore_filter || acceptable.contains(name))
                    res = res + name + '=' + (*cookie).value() + ';' + ' ';
            }

            return QByteArrayLiteral("Cookie: ") + res;
        }
        QByteArray cookie(const QByteArray & name, const QUrl & url = QUrl()) {
            const QList<QNetworkCookie> items = url.isEmpty() ? allCookies() : cookiesForUrl(url);
            for(QList<QNetworkCookie>::ConstIterator cookie = items.cbegin(); cookie != items.cend(); cookie++)
                if ((*cookie).name() == name)
                    return (*cookie).value();

            return QByteArray();
        }
    };
}

#endif // WEB_COOKIES_H
