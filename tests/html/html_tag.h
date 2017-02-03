#ifndef HTML_TAG_H
#define HTML_TAG_H

#include "html_global.h"
#include "html_set.h"

#include <qhash.h>
#include <qdebug.h>

#define DEBUG_LIMIT_OUTPUT 10000

class QUrl;
class QDebug;

namespace Html {
    class Selector;

    class HTMLSHARED_EXPORT Tag {
        int _level;
        QByteArray _name;
        QHash<QByteArray, QByteArray> attrs;
        Set tags;
        Tag * parent;
//        bool proceeded;
    protected:
        const static QHash<QByteArray, bool> solo;

        QString selectValue() const;
        QString radioValue() const;
        QString textareaValue() const;
    public:
        enum FormSerializationFlags {
            fsf_none,
            fsf_append_vals_from_hash = 1,
            fsf_percent_encoding,
            fsf_ignore_empty
        };

        static Tag * stub() { return new Tag(HTML_ANY_TAG); }

        inline Tag(const QByteArray & tag, Tag * parent_tag = 0) : _level(parent_tag ? parent_tag -> level() + 1 : 0), _name(tag), parent(parent_tag) {}
        inline ~Tag() { qDeleteAll(tags); }

        inline int level() const { return _level; }
        inline QByteArray name() const { return _name; }
        inline QHash<QByteArray, QByteArray> attributes() const { return attrs; }
        inline Set children() const { return tags; }
        inline QString data(const QString & name) const { return value(LSTR("data-") % name); }
        inline QString src() const { return value(attr_src); }
        inline QString link() const { return attrs.value(attr_href); }

        QString value(const QString & name = attr_default) const;
        QString text() const;

        void serializeForm(QUrl & url, QByteArray & payload, const QHash<QString, QString> & vals = QHash<QString, QString>(), const FormSerializationFlags & flags = fsf_none, const QString & default_url = QString());
        QUrl serializeFormToUrl(const QHash<QString, QString> & vals = QHash<QString, QString>(), const FormSerializationFlags & flags = fsf_none, const QString & default_url = QString());
        QString toText() const;
        QString toString() const;

        inline bool isSolo() { return solo.contains(name()); }
        static inline bool isSolo(const QByteArray & tag_name) { return solo.contains(tag_name); }

        inline bool isStub() { return _name == tkn_any_elem; }
        inline bool isLink() { return _name == tag_a; }
        inline bool isScript() { return _name == tag_script; }
        inline bool isHead() { return _name == tag_head; }
        inline bool isBody() { return _name == tag_body; }
        inline bool isMeta() { return _name == tag_meta; }
        inline bool isXmlHead() { return _name == tag_xml; }

        inline bool isFormProceable() const {
            if (hasAttr(attr_disabled)) return false;

            if (_name == tag_select || _name == tag_textarea) return true;

            if (_name == tag_input) {
                bool is_radio = attrs.value(attr_type) == type_radio;
                bool is_checkbox = attrs.value(attr_type) == type_checkbox;

                return (!is_radio && !is_checkbox) || hasAttr(attr_checked);
            }

            return false;
        }

        inline Tag * parentTag() { return parent; }
        inline Tag * childTag(int pos) const { return tags[pos]; }
        Tag * childTag(const QString & name_predicate, const int & pos = 0) const;
        inline int childrenCount() { return tags.size(); }

        //TODO: store classes in hash
        inline bool hasClass(const QByteArray & class_name) {
            return attrs[attr_class].split(tkn_split).contains(class_name);
        }
        inline bool hasAttr(const QByteArray & attr_name = attr_checked) const { return attrs.contains(attr_name); }
        inline bool hasChilds(const char * predicate) const { return !find(predicate).isEmpty(); }

        inline Set find(const Selector * selector) const { return tags.find(selector); }
        Set find(const char * predicate) const;
        Set & backwardFind(Selector * selector, Set & set);
        Tag * findFirst(const char * predicate) const;
        Tag * findFirst(const Selector * selector) const;

        bool validTo(const Selector * selector);

        //TODO: rewrite
//        QHash<QString, QString> & findLinks(const Selector * selector, QHash<QString, QString> & links);
//        QHash<QString, QString> & backwardFindLinks(Selector * selector, QHash<QString, QString> & links);

        inline void addAttr(const QByteArray & name, const QByteArray & val) { attrs.insert(name, val); }
        Tag * appendTag(const QByteArray & tname);
        void appendText(const QByteArray & val);
        void appendComment(const QByteArray & val);
        void appendService(const QByteArray & val);

        friend QDebug operator<< (QDebug debug, const Tag & c) {
            QString attrStr;
            QHash<QByteArray, QByteArray> vals = c.attributes();

            for (QHash<QByteArray, QByteArray>::iterator it = vals.begin(); it != vals.end(); ++it)
                attrStr.append("(" + it.key() + " : " + (it.value().size() > DEBUG_LIMIT_OUTPUT ? (it.value().mid(0, DEBUG_LIMIT_OUTPUT / 2) % "..." % it.value().mid(it.value().size() - DEBUG_LIMIT_OUTPUT / 2, DEBUG_LIMIT_OUTPUT / 2)) : it.value()) + ")");

            if (attrStr.isEmpty())
                qDebug("%s%s", QString(c.level() * 3, ' ').toUtf8().constData(), c.name().data());
            else
                qDebug("%s%s%s%s%s", QString(c.level() * 3, ' ').toUtf8().constData(), c.name().data(), " ||| [", attrStr.toUtf8().constData(), "]");

            foreach(Tag * it, c.children())
                qDebug() << (*it);

            return debug;
        }
    };
}

#endif // HTML_TAG_H
