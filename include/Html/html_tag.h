#ifndef HTML_TAG_H
#define HTML_TAG_H

#include <html_global.h>
#include <html_set.h>

#include <qhash.h>
#include <qdebug.h>

#define DEBUG_LIMIT_OUTPUT 10000

class QUrl;
class QDebug;

namespace Html {
    class Selector;

    class HTMLSHARED_EXPORT Tag {
        int _level;
        QString _name;
        QHash<QString, QString> attrs;
        Set tags;
        Tag * parent;
    protected:
        static QHash<QString, bool> solo;
    public:
        enum FormSerializationFlags {
            fsf_none,
            fsf_append_vals_from_hash = 1,
            fsf_percent_encoding
        };

        inline Tag(QString tag, Tag * parent_tag = 0) : _level(parent_tag ? parent_tag -> level() + 1 : 0), _name(tag), parent(parent_tag) {}
        inline ~Tag() { qDeleteAll(tags); }

        inline QString name() const { return _name; }
        inline int level() const { return _level; }
        inline QHash<QString, QString> attributes() const { return attrs; }
        inline Set children() const { return tags; }
        inline QString data(const QString & name) const { return value(LSTR("data-") % name); }
        inline QString src() const { return value(attr_src); }
        inline QString link() const { return attrs.value(attr_href); }

        QString value(const QString & name = attr_default) const;
        QString text() const;
        void serializeForm(QUrl & url, QByteArray & payload, const QHash<QString, QString> & vals = QHash<QString, QString>(), const FormSerializationFlags & flags = fsf_none, const QString & default_url = QString());
        QUrl serializeFormToUrl(const QHash<QString, QString> & vals = QHash<QString, QString>(), const FormSerializationFlags & flags = fsf_none, const QString & default_url = QString());
        QString toText() const;
        QString toHtml() const;

        inline bool isSolo() { return solo.contains(name()); }
        static inline bool isSolo(const QString & tag_name) { return solo.contains(tag_name); }

        inline bool is_link() { return _name == tag_a; }
        inline bool is_script() { return _name == tag_script; }
        inline bool is_head() { return _name == tag_head; }
        inline bool is_meta() { return _name == tag_meta; }
        inline bool is_xml_head() { return _name == tag_xml; }

        inline Tag * parentTag() { return parent; }
        inline Tag * childTag(int pos) const { return tags[pos]; }
        Tag * childTag(const QString & name_predicate, const int & pos = 0) const;
        inline int childrenCount() { return tags.size(); }

        inline bool has(const char * predicate) const { return !find(predicate).isEmpty(); }
        inline Set find(const Selector * selector) const { return tags.find(selector); }
        Set find(const char * predicate) const;
        Tag * findFirst(const char * predicate) const;
        Tag * findFirst(const Selector * selector) const;

        //TODO: rewrite
//        QHash<QString, QString> & findLinks(const Selector * selector, QHash<QString, QString> & links);

        void addAttr(QString & name, QString & val);
        Tag * appendTag(QString & tname);
        void appendText(QString & val);
        void appendComment(QString & val);
        void appendService(QString & val);

        //TODO: store classes in hash
        inline bool hasClass(const QString & class_name) {
            return attrs[attr_class].split(tkn_split, QString::SkipEmptyParts).contains(class_name);
        }

        bool validTo(const Selector * selector);
        Set & backwardFind(Selector * selector, Set & set);
        QHash<QString, QString> & backwardFindLinks(Selector * selector, QHash<QString, QString> & links);

        friend QDebug operator<< (QDebug debug, const Tag & c) {
            QString attrStr;
            QHash<QString, QString> vals = c.attributes();

            for (QHash<QString, QString>::iterator it = vals.begin(); it != vals.end(); ++it)
                attrStr.append("(" + it.key() + " : " + (it.value().size() > DEBUG_LIMIT_OUTPUT ? (it.value().mid(0, DEBUG_LIMIT_OUTPUT / 2) % "..." % it.value().mid(it.value().size() - DEBUG_LIMIT_OUTPUT / 2, DEBUG_LIMIT_OUTPUT / 2)) : it.value()) + ")");

            if (attrStr.isEmpty())
                qDebug("%s%s", QString(c.level() * 3, ' ').toUtf8().constData(), c.name().toUtf8().constData());
            else
                qDebug("%s%s%s%s%s", QString(c.level() * 3, ' ').toUtf8().constData(), c.name().toUtf8().constData(), " ||| [", attrStr.toUtf8().constData(), "]");

            foreach(Tag * it, c.children())
                qDebug() << (*it);

            return debug;
        }
    };
}

#endif // HTML_TAG_H
