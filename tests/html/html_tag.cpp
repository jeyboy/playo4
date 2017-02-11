#include "html_tag.h"

#include <qurl.h>
#include <qurlquery.h>

#include "html_selector.h"

using namespace Html;

const QHash<QByteArray, bool> Tag::solo = QHash<QByteArray, bool>{
    {HTML_BR_TAG, true}, {HTML_META_TAG, true}, {HTML_LINK_TAG, true}, {HTML_IMG_TAG, true},
    {HTML_DOCTYPE_TAG, true}, {HTML_XML_TAG, true}, {HTML_INPUT_TAG, true}, {HTML_BASE_TAG, true},
    {HTML_DOCTYPE_TAG.toLower(), true}, {HTML_HR_TAG, true}
};

QByteArray Tag::selectValue() const {
    Html::Set options = find("option[selected]");
    return options.value();
}
QByteArray Tag::radioValue() const { return hasAttr(attr_checked) ? _attrs[attr_default] : QByteArray(); }
QByteArray Tag::textareaValue() const { return text(); }

QByteArray Tag::value(const QByteArray & name) const {
    bool is_default_val = name == attr_default;

    if (is_default_val) {
        if (_name == tag_select)
            return selectValue();

        if (_name == tag_textarea)
            return textareaValue();

        if (_attrs.value(attr_type) == type_radio)
            return radioValue();
    }

    return _attrs.value(name);
}

QByteArray Tag::text() const {
    const Tag * text = (_name == tkn_text_block ? this : child(tkn_text_block));
    return text ? text -> _attrs.value(tkn_text_block) : QByteArray();
}
QByteArray Tag::texts() const {
    if (_name == tkn_text_block)
        return _attrs.value(tkn_text_block);
    else {
        QByteArray result;

        for(Set::ConstIterator tag = _tags.cbegin(); tag != _tags.cend(); tag++)
            result += (*tag) -> texts();

        return result;
    }
}

//INFO: some servers very sensitive to params part and payload part separation ...
// appendable - appends inputs from vals, which not finded in form
// default_url - if form did not contains action, we should use source url
void Tag::serializeForm(QUrl & url, QByteArray & payload, const QHash<QString, QString> & vals, const FormSerializationFlags & flags, const QString & default_url) {
    QString action = value(attr_action);
    url = QUrl(action.isEmpty() ? default_url : action);

    Set inputs = find("input") << find("select") << find("textarea");
    QHash<QString, QString> url_vals(vals);

    if (!inputs.isEmpty()) {
        QUrlQuery query = QUrlQuery();

        for(Set::Iterator input = inputs.begin(); input != inputs.end(); input++) {
            QString inp_name = (*input) -> value(attr_name);
            if (inp_name.isEmpty()) continue;

            if (!(*input) -> isFormProceable()) continue; // ignore disabled and not checked inputs

            QString inp_val = url_vals.take(inp_name);
            if (inp_val.isEmpty()) inp_val = (*input) -> value();

            if (flags & fsf_ignore_empty && inp_val.isEmpty()) continue;

            query.addQueryItem(
                inp_name,
                flags & fsf_percent_encoding ? QUrl::toPercentEncoding(inp_val) : inp_val
            );
        }

        if (flags & fsf_append_vals_from_hash && !url_vals.isEmpty())
            for(QHash<QString, QString>::Iterator it = url_vals.begin(); it != url_vals.end(); it++)
                query.addQueryItem(
                    it.key(),
                    flags & fsf_percent_encoding ? QUrl::toPercentEncoding(it.value()) : it.value()
                );

        payload = query.toString().toUtf8();
    }
}

QUrl Tag::serializeFormToUrl(const QHash<QString, QString> & vals, const FormSerializationFlags & flags, const QString & default_url) { // not full support of inputs
    QUrl url;
    QByteArray payload;

    serializeForm(url, payload, vals, flags, default_url);
    url.setQuery(QUrlQuery(payload + '&' + url.query()));
    return url;
}

QByteArray Tag::toByteArray() const {
    if (_name == tkn_text_block)
        return _attrs.value(tkn_text_block);
    else {
        QByteArray result;
        bool root = _name == tkn_any_elem;


        if (!root) {
            result = '<' % _name;

            for(QHash<QByteArray, QByteArray>::ConstIterator attr = _attrs.cbegin(); attr != _attrs.cend(); attr++)
                result = result % ' ' % attr.key() % (attr.value().isNull() ? QByteArray() : (QByteArray("=\"") % attr.value() % '"'));

            result = result % '>';
        }

        for(Set::ConstIterator tag = _tags.cbegin(); tag != _tags.cend(); tag++)
            result += (*tag) -> toByteArray();


        return root || (solo.contains(_name) && _tags.isEmpty()) ? result : QByteArray(result % QByteArray("</") % _name % '>');
    }
}

Tag * Tag::child(const QByteArray & name_predicate, const int & pos) const {
    int i = 0;
    for(Set::ConstIterator tag = _tags.cbegin(); tag != _tags.cend(); tag++) {
        if ((*tag) -> _name == name_predicate)
            if (i++ == pos) return (*tag);
    }

    return 0;
}

QHash<QByteArray, bool> * Tag::classes() {
    if (!_classes) {
        QByteArray klasses = _attrs.take(attr_class);
        if (!klasses.isEmpty()) {
            _classes = new QHash<QByteArray, bool>();
            const char * data = klasses.constData(), * sdata = data;
            while(*data) {
                switch(*data) {
                    case 32: {
                        if (data - sdata > 0)
                            _classes -> insert(QByteArray(sdata, data - sdata), true);
                        sdata = data + 1;
                    break;}
                    default:;
                }

                data++;
            }

            _classes -> insert(QByteArray(sdata, data - sdata), true);
        }
    }

    return _classes;
}

Set Tag::find(const char * predicate) const {
    Selector selector(predicate);
    return _tags.find(&selector);
}
Tag * Tag::findFirst(const char * predicate) const {
    Selector selector(predicate);
    return findFirst(&selector);
}
Tag * Tag::findFirst(const Selector * selector) const {
    Set set = _tags.find(selector, true);
    return set.isEmpty() ? 0 : set.first();
}

//QHash<QString, QString> & Tag::findLinks(const Selector * selector, QHash<QString, QString> & links) {
//    return tags.findLinks(selector, links);
//}

Tag * Tag::appendTag(const QByteArray & tname) {
    Tag * newTag = new Tag(tname.toLower(), this);
    _tags.append(newTag);
    return newTag;
}
void Tag::appendText(const QByteArray & val) {
    Tag * newTag = appendTag(tkn_text_block);
    newTag -> addAttr(tkn_text_block, val);
}
void Tag::appendComment(const QByteArray & val) {
    Tag * newTag = appendTag(tkn_comment_block);
    newTag -> addAttr(tkn_comment_block, val);
}

bool Tag::validTo(const Selector * selector) {
    if (!(selector -> _token == tkn_any_elem || selector -> _token == _name))
        return false;

    if (selector -> pos_limit != -1) {
        if (!_parent || _parent -> child(selector -> pos_limit) != this)
            return false;
    }

    if (!selector -> _attrs.isEmpty()) {
        for(QHash<QByteArray, QPair<char, QByteArray> >::ConstIterator attr = selector -> _attrs.cbegin(); attr != selector -> _attrs.cend(); attr++) {
            QByteArray attr_key = attr.key();
            if (!_attrs.contains(attr_key))
                return false;

            QByteArray tag_value = attr_key == tkn_text_block ? text() : _attrs.value(attr_key);
            QByteArray selector_value = attr.value().second;
            char rel = attr.value().first;

            switch(rel) {
                case Selector::sel_attr_eq: {
                    if (!((selector_value == tkn_any_elem || tag_value == selector_value)))
                        return false;
                    break;}
                case Selector::sel_attr_begin:
                case Selector::sel_attr_begin2: {
                    if (!tag_value.startsWith(selector_value))
                        return false;
                    break;}
                case Selector::sel_attr_end: {
                    if (!tag_value.endsWith(selector_value))
                        return false;
                    break;}
                case Selector::sel_rel_attr_match:
                case Selector::sel_attr_match2: {
                    if (tag_value.indexOf(selector_value) == -1)
                        return false;
                    break;}
                case Selector::sel_attr_not: {
                    if (tag_value.indexOf(selector_value) != -1)
                        return false;
                    break;}

                default: qDebug() << "UNSUPPORTED PREDICATE " << rel;
            };
        }
    }

    if (!selector -> _classes.isEmpty()) {
        QHash<QByteArray, bool> * tag_classes = classes();
        if (!tag_classes) return false;

        for(QList<QByteArray>::ConstIterator selector_class = selector -> _classes.cbegin(); selector_class != selector -> _classes.cend(); selector_class++) {
            if (!tag_classes -> contains(*selector_class))
                return false;
        }
    }

    return true;
}

Set & Tag::backwardFind(Selector * selector, Set & set) {
    if (!_parent) return set;

    if (_parent -> validTo(selector))
        selector = selector -> prev/*next*/;

    if (!selector)
        set.append(_parent);
    else
        if (selector -> isBackward()) {
            if (_parent -> _parent)
                _parent -> backwardFind(selector, set);
        }
        else _parent -> children().find(selector, set);

    return set;
}

//QHash<QString, QString> & Tag::backwardFindLinks(Selector * selector, QHash<QString, QString> & links) {
//    if (!parent) return links;

//    if (parent -> validTo(selector))
//        selector = selector -> next;

//    if (!selector) {
//        if (parent -> isLink())
//            links.insert(parent -> link(), parent -> text());
//    } else if (selector -> isBackward() && parent -> parent)
//        parent -> backwardFindLinks(selector, links);

//    return links;
//}
