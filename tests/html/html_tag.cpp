#include "html_tag.h"

#include <qurl.h>
#include <qurlquery.h>

#include "html_selector.h"
#include "html_page.h"

using namespace Html;

const QHash<QByteArray, bool> Tag::solo = QHash<QByteArray, bool>{
    {HTML_BR_TAG, true}, {HTML_META_TAG, true}, {HTML_LINK_TAG, true},
    {HTML_IMG_TAG, true}, {HTML_HR_TAG, true}, {HTML_DOCTYPE_TAG, true},
    {HTML_XML_TAG, true}, {HTML_INPUT_TAG, true}, {HTML_BASE_TAG, true}
};

const QHash<QByteArray, bool> restricted_solo_by_parent = QHash<QByteArray, bool>{
    {QByteArrayLiteral("li"), 1}, {QByteArrayLiteral("dd"), 2}, {QByteArrayLiteral("p"), 3},
    {QByteArrayLiteral("rt"), 4}, {QByteArrayLiteral("rp"), 4}, {QByteArrayLiteral("optgroup"), 5},
    {QByteArrayLiteral("option"), 6}, {QByteArrayLiteral("tbody"), 7}, {QByteArrayLiteral("tfoot"), 8},
    {QByteArrayLiteral("tr"), 9}, {QByteArrayLiteral("td"), 10}, {QByteArrayLiteral("th"), 11}
};
const QHash<QByteArray, bool> restricted_solo_by_sibling = QHash<QByteArray, bool>{
    {QByteArrayLiteral("html"), 1}, {QByteArrayLiteral("head"), 2}, {QByteArrayLiteral("body"), 3},
    {QByteArrayLiteral("li"), 4}, {QByteArrayLiteral("dt"), 5}, {QByteArrayLiteral("dd"), 5},
    {QByteArrayLiteral("p"), 6}, {QByteArrayLiteral("rt"), 7}, {QByteArrayLiteral("rp"), 7},
    {QByteArrayLiteral("optgroup"), 8}, {QByteArrayLiteral("option"), 9}, {QByteArrayLiteral("colgroup"), 10},
    {QByteArrayLiteral("caption"), 11}, {QByteArrayLiteral("thead"), 12}, {QByteArrayLiteral("tbody"), 13},
    {QByteArrayLiteral("tfoot"), 14}, {QByteArrayLiteral("tr"), 15}, {QByteArrayLiteral("td"), 16},
    {QByteArrayLiteral("th"), 17}
};

//An html element’s start tag may be omitted if the first thing inside the html element is not a comment.

//An html element’s end tag may be omitted if the html element is not immediately followed by a comment.

//A head element’s start tag may be omitted if the element is empty, or if the first thing inside the head element is an element.

//A head element’s end tag may be omitted if the head element is not immediately followed by a space character or a comment.

//A body element’s start tag may be omitted if the element is empty, or if the first thing inside the body element is not a space character or a comment, except if the first thing inside the body element is a meta, link, script, style, or template element.

//A body element’s end tag may be omitted if the body element is not immediately followed by a comment.


//An li element’s end tag may be omitted if the li element is immediately followed by another li element or if there is no more content in the parent element.

//A dt element’s end tag may be omitted if the dt element is immediately followed by another dt element or a dd element.

//A dd element’s end tag may be omitted if the dd element is immediately followed by another dd element or a dt element, or if there is no more content in the parent element.

//A p element’s end tag may be omitted if the p element is immediately followed by an address, article, aside, blockquote, details, div, dl, fieldset, figcaption, figure, footer, form, h1, h2, h3, h4, h5, h6, header, hr, main, menu, nav, ol, p, pre, section, table, or ul element, or if there is no more content in the parent element and the parent element is an HTML element that is not an a, audio, del, ins, map, noscript, or video element.

//An rt element’s end tag may be omitted if the rt element is immediately followed by an rt or rp element, or if there is no more content in the parent element.

//An rp element’s end tag may be omitted if the rp element is immediately followed by an rt or rp element, or if there is no more content in the parent element.

//An optgroup element’s end tag may be omitted if the optgroup element is immediately followed by another optgroup element, or if there is no more content in the parent element.

//An option element’s end tag may be omitted if the option element is immediately followed by another option element, or if it is immediately followed by an optgroup element, or if there is no more content in the parent element.

//A colgroup element’s start tag may be omitted if the first thing inside the colgroup element is a col element, and if the element is not immediately preceded by another colgroup element whose end tag has been omitted. (It can’t be omitted if the element is empty.)

//A colgroup element’s end tag may be omitted if the colgroup element is not immediately followed by a space character or a comment.

//A caption element’s end tag may be omitted if the caption element is not immediately followed by a space character or a comment.

//A thead element’s end tag may be omitted if the thead element is immediately followed by a tbody or tfoot element.

//A tbody element’s start tag may be omitted if the first thing inside the tbody element is a tr element, and if the element is not immediately preceded by a tbody, thead, or tfoot element whose end tag has been omitted. (It can’t be omitted if the element is empty.)

//A tbody element’s end tag may be omitted if the tbody element is immediately followed by a tbody or tfoot element, or if there is no more content in the parent element.

//A tfoot element’s end tag may be omitted if the tfoot element is immediately followed by a tbody element, or if there is no more content in the parent element.

//A tr element’s end tag may be omitted if the tr element is immediately followed by another tr element, or if there is no more content in the parent element.

//A td element’s end tag may be omitted if the td element is immediately followed by a td or th element, or if there is no more content in the parent element.

//A th element’s end tag may be omitted if the th element is immediately followed by a td or th element, or if there is no more content in the parent element.


bool Tag::isSoloOnParentClosing() {

}
bool Tag::isSoloOnNewTag(const QByteArray & tag) {

}



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

void Tag::proceedIFrameData(const QByteArray & data) { Page(this, data); }
void Tag::proceedIFrameData(const QString & data) { Page(this, data); }
void Tag::proceedIFrameData(const char * data) { Page(this, data); }

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

            if (data - sdata > 0)
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
            bool text_required = attr_key == tkn_text_block;

            if (!text_required && !_attrs.contains(attr_key))
                return false;

            QByteArray tag_value = text_required ? text() : _attrs.value(attr_key);
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

        for(QList<QPair<char, QByteArray> >::ConstIterator selector_class = selector -> _classes.cbegin(); selector_class != selector -> _classes.cend(); selector_class++) {
            switch((*selector_class).first) {
                case Selector::sel_attr_eq: {
                    if (!tag_classes -> contains((*selector_class).second))
                        return false;
                    break;}
                case Selector::sel_attr_begin:
                case Selector::sel_attr_begin2: {
                    bool res = false;
                    for(QHash<QByteArray, bool>::Iterator tag_class = tag_classes -> begin(); tag_class != tag_classes -> end(); tag_class++)
                        if (tag_class.key().startsWith((*selector_class).second)) {
                            res = true;
                            break;
                        }
                    if (!res) return false;
                break;}
                case Selector::sel_attr_end: {
                    bool res = false;
                    for(QHash<QByteArray, bool>::Iterator tag_class = tag_classes -> begin(); tag_class != tag_classes -> end(); tag_class++)
                        if (tag_class.key().endsWith((*selector_class).second)) {
                            res = true;
                            break;
                        }
                    if (!res) return false;
                break;}
                case Selector::sel_rel_attr_match:
                case Selector::sel_attr_match2: {
                    bool res = false;
                    for(QHash<QByteArray, bool>::Iterator tag_class = tag_classes -> begin(); tag_class != tag_classes -> end(); tag_class++)
                        if (tag_class.key().indexOf((*selector_class).second) != -1) {
                            res = true;
                            break;
                        }
                    if (!res) return false;
                break;}
                case Selector::sel_attr_not: {
                    for(QHash<QByteArray, bool>::Iterator tag_class = tag_classes -> begin(); tag_class != tag_classes -> end(); tag_class++)
                        if (tag_class.key().indexOf((*selector_class).second) != -1)
                            return false;
                break;}

                default: qDebug() << "UNSUPPORTED PREDICATE " << (*selector_class).first;
            };
        }
    }

    return true;
}
