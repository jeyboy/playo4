#ifndef WEBMANAGER_GLOBAL_H
#define WEBMANAGER_GLOBAL_H

#include <QtCore/qglobal.h>

#include <qbytearray.h>

#define REQUEST_DELAY 260 // ms
#define COOKIES_KEY QByteArrayLiteral("cookies")

#define JSON_ERR_FIELD QByteArrayLiteral("json_err")
#define DEF_JSON_FIELD QByteArrayLiteral("response")

#if defined(WEBMANAGER_LIBRARY)
#  define WEBMANAGERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define WEBMANAGERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // WEBMANAGER_GLOBAL_H
