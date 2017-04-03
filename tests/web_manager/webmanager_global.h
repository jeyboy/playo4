#ifndef WEBMANAGER_GLOBAL_H
#define WEBMANAGER_GLOBAL_H

#include <QtCore/qglobal.h>

#include <qbytearray.h>


#ifdef Q_OS_WIN
    #define DEFAULT_AGENT QByteArrayLiteral("Mozilla/5.0 (Windows NT 6.1; WOW64; rv:48.0) Gecko/20100101 Firefox/48.0")
#elif Q_OS_MAC // there should be agent for mac
    #define DEFAULT_AGENT QByteArrayLiteral("Mozilla/5.0 (X11; Ubuntu; Linux i686; rv:43.0) Gecko/20100101 Firefox/50.0")
#else
    #define DEFAULT_AGENT QByteArrayLiteral("Mozilla/5.0 (X11; Ubuntu; Linux i686; rv:43.0) Gecko/20100101 Firefox/50.0")
#endif

#define REQUEST_DELAY 260 // ms
#define COOKIES_KEY QByteArrayLiteral("cookies")

#define JSON_ERR_FIELD QByteArrayLiteral("json_err")
#define DEF_JSON_FIELD QByteArrayLiteral("response")
#define USER_AGENT_HEADER_NAME QByteArrayLiteral("User-Agent")
#define FORM_URLENCODE QByteArrayLiteral("application/x-www-form-urlencoded")

#if defined(WEBMANAGER_LIBRARY)
#  define WEBMANAGERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define WEBMANAGERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // WEBMANAGER_GLOBAL_H
