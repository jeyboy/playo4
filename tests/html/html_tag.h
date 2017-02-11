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
//        bool proceeded;
    protected:
        const static QHash<QByteArray, bool> solo;

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
        inline Set children() const { return _tags; }
        inline QByteArray data(const QByteArray & name) const { return value("data-" % name); }
        inline QByteArray src() const { return value(attr_src); }
        inline QByteArray link() const { return _attrs.value(attr_href); }

        QByteArray value(const QByteArray & name = attr_default) const;
        QByteArray text() const;
        QByteArray texts() const;

        void serializeForm(QUrl & url, QByteArray & payload, const QHash<QString, QString> & vals = QHash<QString, QString>(), const FormSerializationFlags & flags = fsf_none, const QString & default_url = QString());
        QUrl serializeFormToUrl(const QHash<QString, QString> & vals = QHash<QString, QString>(), const FormSerializationFlags & flags = fsf_none, const QString & default_url = QString());
        QByteArray toByteArray() const;

        inline bool isSolo() { return solo.contains(name()); }
        static inline bool isSolo(const QByteArray & tag_name) { return solo.contains(tag_name); }
        inline bool isClosableBy(const char * data) {
            return _name[0] == *data && _name[1] == *(data + 1) && '>' == *(data + _name.length());
        }

        inline bool isStub() { return _name == tkn_any_elem; }
        inline bool isLink() { return _name == tag_a; }
        inline bool isBody() { return _name == tag_body; }
        inline bool isMeta() { return _name == tag_meta; }

        inline bool isHead() { return _name == tag_head; }
        inline bool isXmlHead() { return _name == tag_xml; }

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
        inline Tag * child(const int & pos) const { return _tags.size() < pos ? _tags[pos] : 0; }
        Tag * child(const QByteArray & name_predicate, const int & pos = 0) const;
        inline int childrenCount() { return _tags.size(); }

        inline QHash<QByteArray, bool> * classes() {
            if (!_classes) {
                QByteArray klasses = _attrs.take(attr_class);
                if (!klasses.isEmpty()) {
                    _classes = new QHash<QByteArray, bool>();
                    const char * data = klasses.constData(), * sdata = data;
                    while(true) {
                        switch(*data) {
                            case 32: {
                                _classes -> insert(QByteArray(sdata, data - sdata), true);
                            break;}
                            case 0: {
                                _classes -> insert(QByteArray(sdata, data - sdata), true);
                                break;
                            }
                            default:;
                        }

                        data++;
                    }
                }
            }

            return _classes;
        }
        inline bool hasClass(const QByteArray & class_name) {
            return classes() -> contains(class_name);
        }
        inline bool hasAttr(const QByteArray & attr_name = attr_checked) const { return _attrs.contains(attr_name); }
        inline bool hasChildren(const char * predicate = 0) const { return !(predicate ? find(predicate).isEmpty() : _tags.isEmpty()); }

        inline Set find(const Selector * selector) const { return _tags.find(selector); }
        Set find(const char * predicate) const;
        Set & backwardFind(Selector * selector, Set & set);
        Tag * findFirst(const char * predicate) const;
        Tag * findFirst(const Selector * selector) const;

        bool validTo(const Selector * selector);

        //TODO: rewrite
//        QHash<QString, QString> & findLinks(const Selector * selector, QHash<QString, QString> & links);
//        QHash<QString, QString> & backwardFindLinks(Selector * selector, QHash<QString, QString> & links);

        inline void addAttr(const QByteArray & name, const QByteArray & val) { _attrs.insert(name, val); }
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
