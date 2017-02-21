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
        QHash<QByteArray, QByteArray> _attrs;
        QHash<QByteArray, bool> * _classes;
        Set _tags;
        Tag * _parent;
    protected:
        const static QHash<QByteArray, bool> solo;
        const static QHash<QByteArray, int> restricted_solo_by_parent;
        const static QHash<QByteArray, int> restricted_solo_by_sibling;

        QByteArray selectValue() const;
        QByteArray radioValue() const;
        QByteArray textareaValue() const;
    public:
        enum FormSerializationFlags {
            fsf_none,
            fsf_append_vals_from_hash = 1,
            fsf_percent_encoding,
            fsf_ignore_empty
        };

        static Tag * stub() { return new Tag(HTML_ANY_TAG); }

        inline Tag(const QByteArray & tag, Tag * parent_tag = 0) : _level(parent_tag ? parent_tag -> _level + 1 : 0), _name(tag), _classes(0), _parent(parent_tag) {}
        inline ~Tag() {
            qDeleteAll(_tags);
            delete _classes;
        }

        inline int level() const { return _level; }
        inline QByteArray name() const { return _name; }
        inline QHash<QByteArray, QByteArray> attributes() const { return _attrs; }
        inline QByteArray data(const QByteArray & name) const { return value(QByteArrayLiteral("data-") + name); }

        inline QByteArray src() const { return _attrs.value(attr_src); }
        inline QByteArray link() const { return _attrs.value(attr_href); }
        inline QByteArray action() const { return _attrs.value(attr_action); }

        inline Set children() const { return _tags; }

        QByteArray value(const QByteArray & name = attr_default) const;
        QByteArray text() const;
        QByteArray texts() const;

        void proceedIFrameData(const QByteArray & data);
        void proceedIFrameData(const QString & data);
        void proceedIFrameData(const char * data);

        void serializeForm(QUrl & url, QByteArray & payload, const QHash<QString, QString> & vals = QHash<QString, QString>(), const FormSerializationFlags & flags = fsf_none, const QString & default_url = QString());
        QUrl serializeFormToUrl(const QHash<QString, QString> & vals = QHash<QString, QString>(), const FormSerializationFlags & flags = fsf_none, const QString & default_url = QString());
        QByteArray toByteArray() const;

//        static QByteArray & decodeMnemonics(QByteArray & val);
//        static QByteArray & decodeLink(QByteArray & val);
//        static QByteArray & decodeContent(QByteArray & val);

//        inline bool hasRelativeSrc() {
//            QByteArray elem_src = src();

//            if (elem_src.isEmpty()) return false;
//        }

        inline bool isSolo() { return solo.contains(name()); }
        bool isSoloOnParentClosing();
        bool isSoloOnNewTag(const QByteArray & tag);

        static inline bool isSolo(const QByteArray & tag_name) { return solo.contains(tag_name); }
        inline bool isClosableBy(const char * data) {
            return _name.startsWith(QByteArray(data, 2).toLower()) && '>' == *(data + _name.length());
        }

        inline bool isStub() { return _name == tkn_any_elem; }
        inline bool isText() { return _name == tkn_text_block; }
        inline bool isLink() { return _name == tag_a; }
        inline bool isBody() { return _name == tag_body; }
        inline bool isMeta() { return _name == tag_meta; }

        inline bool isHead() { return _name == tag_head; }
        inline bool isXmlHead() { return _name == tag_xml; }

        inline bool isFrame() { return _name == tag_iframe; }
        inline bool isFrameRequireInit() { return _name == tag_iframe && _tags.isEmpty(); }

        inline bool isScript() { return _name == tag_script; }
        inline bool isStyle() { return _name == tag_style; }
        inline bool isCodeBlock() { return _name == tag_script || _name == tag_style; }

        inline bool isFormProceable() const {
            if (hasAttr(attr_disabled)) return false;

            if (_name == tag_select || _name == tag_textarea) return true;

            if (_name == tag_input) {
                bool is_radio = _attrs.value(attr_type) == type_radio;
                bool is_checkbox = _attrs.value(attr_type) == type_checkbox;

                return (!is_radio && !is_checkbox) || hasAttr(attr_checked);
            }

            return false;
        }

        inline Tag * parent() { return _parent; }
        inline Tag * child(const int & pos) const { return pos < _tags.size() ? _tags[pos] : 0; }
        Tag * child(const QByteArray & name_predicate, const int & pos = 0) const;
        inline int childrenCount() { return _tags.size(); }

        QHash<QByteArray, bool> * classes();
        inline bool hasId(const QByteArray & id_name) { return _attrs[attr_id] == id_name; }
        inline bool hasClass(const QByteArray & class_name) {
            QHash<QByteArray, bool> * klasses = classes();
            return klasses && klasses -> contains(class_name);
        }
        inline bool hasAttr(const QByteArray & attr_name = attr_checked) const { return _attrs.contains(attr_name); }
        inline bool hasAttr(const QByteArray & attr_name, const QByteArray & attr_val) const { return _attrs[attr_name] == attr_val; }
        inline bool hasChildren(const char * predicate = 0) const { return !(predicate ? find(predicate).isEmpty() : _tags.isEmpty()); }

        Set find(const char * predicate) const;
        Tag * findFirst(const char * predicate) const;
        inline Set find(const Selector * selector) const { return _tags.find(selector); }
        Tag * findFirst(const Selector * selector) const;

        bool validTo(const Selector * selector);

        //TODO: rewrite
//        QHash<QString, QString> & findLinks(const Selector * selector, QHash<QString, QString> & links);

        inline void addAttr(const QByteArray & name, const QByteArray & val) { _attrs.insert(name.toLower(), val); }
        Tag * appendTag(const QByteArray & tname);
        void appendText(const QByteArray & val);
        void appendComment(const QByteArray & val);

        friend QDebug operator<< (QDebug debug, const Tag & c) {
            QString attrStr;
            QHash<QByteArray, QByteArray> vals = c.attributes();

            for (QHash<QByteArray, QByteArray>::iterator it = vals.begin(); it != vals.end(); ++it)
                attrStr.append(
                    '(' % it.key() %
                        (it.value().size() > 0 ?
                            QString(LSTR(": ") % (it.value().size() > DEBUG_LIMIT_OUTPUT ? QString(it.value().mid(0, DEBUG_LIMIT_OUTPUT / 2) % LSTR("...") % it.value().mid(it.value().size() - DEBUG_LIMIT_OUTPUT / 2, DEBUG_LIMIT_OUTPUT / 2)) : QString::fromUtf8(it.value())))
                            : QString()
                        ) % ')'

                );

            if (attrStr.isEmpty())
                qDebug("%s%s", QString(c.level() * 3, ' ').toUtf8().constData(), c.name().data());
            else
                qDebug("%s%s%s%s%s", QString(c.level() * 3, ' ').toUtf8().constData(), c.name().data(), "[", attrStr.toUtf8().constData(), "]");

            foreach(Tag * it, c.children())
                qDebug() << (*it);

            return debug;
        }
    };
}

#endif // HTML_TAG_H
