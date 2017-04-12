#ifndef WEB_UTILS_H
#define WEB_UTILS_H

#include <qurl.h>
#include <qurlquery.h>

#include "web_manager_global.h"

namespace Web {
    class WEBMANAGERSHARED_EXPORT Utils {
    public:
        static inline QString paramVal(const QUrl & url, const QString & param) { return QUrlQuery(url).queryItemValue(param); }
        static QByteArray extractParams(QUrl & url) {
            QByteArray params = url.query().toUtf8();
            url.setQuery(QString());
            return params;
        }
    };
}

#endif // WEB_UTILS_H
