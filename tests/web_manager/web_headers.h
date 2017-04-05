#ifndef WEB_HEADERS
#define WEB_HEADERS

#include "web_manager_global.h"

#include <qhash.h>
#include <qregularexpression.h>

namespace Web {
    class WEBMANAGERSHARED_EXPORT Headers : public QHash<QString, QString> {
    public:
        inline Headers() : QHash<QString, QString>() {}
        #ifdef Q_COMPILER_INITIALIZER_LISTS
            inline Headers(std::initializer_list<std::pair<QString, QString> > list) : QHash<QString, QString>(list) {}
        #endif

        inline Headers(QHash<QString, QString> & hsh) {
            for(QHash<QString, QString>::ConstIterator it = hsh.constBegin(); it != hsh.constEnd(); it++)
                insert(it.key(), it.value());
        }

        static inline Headers extract(const QString & url) {
            QStringList heads = url.split(QRegularExpression("%0D%0A|\\r\\n"), QString::SkipEmptyParts);
            Headers res;
            if (heads.size() > 1) {
                const_cast<QString &>(url) = heads.takeFirst();

                while(!heads.isEmpty()) {
                    QStringList parts =  heads.takeLast().split(QStringLiteral(": "), QString::SkipEmptyParts);
                    res.insert(parts.first(), parts.last());
                }
            }

            return res;
        }
        static inline Headers extract(const QUrl & url) {
            QString urlStr = url.toString();
            Headers headers = Headers::extract(urlStr);
            if (!headers.isEmpty()) const_cast<QUrl &>(url) = QUrl(urlStr);
            return headers;
        }

        Headers & unite(const Headers & other) { return (Headers &) QHash<QString, QString>::unite((QHash<QString, QString>)other); }
    };
}

#endif // WEB_HEADERS
