#ifndef HTML_TAG_H
#define HTML_TAG_H

#include <html_global.h>

namespace Html {
    class Set;

    class HTMLSHARED_EXPORT Tag {
        int _level;
        QString _name;
        QHash<QString, QString> attrs;
        Set tags;
        Tag * parent;
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
        inline QString data(const QString & name) const { return value(QStringLiteral("data-") % name); }
        inline QString value(const QString & name = attr_default) const {
            if (name != attr_default || (name == attr_default && _name != tag_select))
                return attrs.value(name);
            else {
                Html::Set options = find("option[selected]");
                return options.value();
            }
        }
        inline QString text() const {
            const Tag * text = (_name == tkn_text_block ? this : childTag(tkn_text_block));
            return text ? text -> attrs.value(tkn_text_block) : QString();
        }
        inline QString src() const { return value(attr_src); }
        inline QString link() const { return attrs.value(attr_href); }

        void serializeForm(QUrl & url, QByteArray & payload, const QHash<QString, QString> & vals = QHash<QString, QString>(), const FormSerializationFlags & flags = fsf_none, const QString & default_url = QString());
        QUrl serializeFormToUrl(const QHash<QString, QString> & vals = QHash<QString, QString>(), const FormSerializationFlags & flags = fsf_none, const QString & default_url = QString());
        QString toText() const;
        QString toHtml() const;

        inline bool is_link() { return _name == tag_a; }
        inline bool is_script() { return _name == tag_script; }
        inline bool is_head() { return _name == tag_head; }
        inline bool is_meta() { return _name == tag_meta; }
        inline bool is_xml_head() { return _name == tag_xml; }

        inline Tag * parentTag() { return parent; }
        inline Tag * childTag(int pos) const { return tags[pos]; }
        inline Tag * childTag(const QString & name_predicate, int pos = 0) const {
            Set::ConstIterator tag = tags.cbegin();
            for(int i = 0; tag != tags.cend(); tag++) {
                if ((*tag) -> name() == name_predicate)
                    if (i++ == pos) return (*tag);
            }

            return 0;
        }
        inline int childrenCount() { return tags.size(); }

        inline bool has(const char * predicate) const { return !find(predicate).isEmpty(); }
        inline Set find(const Selector * selector) const { return tags.find(selector); }
        inline Set find(const char * predicate) const {
            Selector selector(predicate);
            return tags.find(&selector);
        }
        inline Tag * findFirst(const char * predicate) const {
            Selector selector(predicate);
            return findFirst(&selector);
        }
        inline Tag * findFirst(const Selector * selector) const {
            Set set = tags.find(selector, true);
            return set.isEmpty() ? 0 : set.first();
        }

        inline QHash<QString, QString> & findLinks(const Selector * selector, QHash<QString, QString> & links) {
            return tags.findLinks(selector, links);
        }

        inline void addAttr(QString & name, QString & val) { attrs.insert(name, val);  name.clear(); val.clear(); }
        inline Tag * appendTag(QString & tname) {
            Tag * newTag = new Tag(tname, this); tname.clear();
            tags.append(newTag);
            return newTag;
        }
        inline void appendText(QString & val) {
            QString tnm(tkn_text_block);
            Tag * newTag = appendTag(tnm);
            QString nm(tkn_text_block);
            newTag -> addAttr(nm, val); val.clear();
        }
        inline void appendComment(QString & val) {
            QString tnm(tkn_comment_block);
            Tag * newTag = appendTag(tnm);
            QString nm(tkn_comment_block);
            val = val.mid(2, val.length() - 4);
            newTag -> addAttr(nm, val); val.clear();
        }

        inline void appendService(QString & val) {
            QString tnm(tkn_service_block);
            Tag * newTag = appendTag(tnm);
            QString nm(tkn_service_block);
            newTag -> addAttr(nm, val); val.clear();
        }

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
