#ifndef HTML_SET_H
#define HTML_SET_H

#include <html_global.h>

namespace Html {
    class Tag;
    class Selector;

    class HTMLSHARED_EXPORT Set : public QList<Tag *> {
    public:
        QString link();
        QString text();
        QString value(const QString & name = attr_default);

        inline Set find(const Selector * selector, bool findFirst = false) const {
            Set set;
            return find(selector, set, findFirst);
        }
        inline Set find(const char * predicate, bool findFirst = false) const {
            Selector selector(predicate);
            return find(&selector, findFirst);
        }
        inline Tag * findFirst(const char * predicate) const {
            Set set = find(predicate, true);
            return set.isEmpty() ? 0 : set.first();
        }
        inline Tag * findFirst(const Selector * selector) const {
            Set set = find(selector, true);
            return set.isEmpty() ? 0 : set.first();
        }

        QHash<QString, QString> & findLinks(const Selector * selector, QHash<QString, QString> & links);
        inline Set & operator <<(const Set & l) { *this += l; return *this; }
    private:
        Set & find(const Selector * selector, Set & set, bool findFirst = false) const;
        friend class Tag;
    };
}

#endif // HTML_SET_H
