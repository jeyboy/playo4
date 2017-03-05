#include "html_tag.h"

#include <qurl.h>
#include <qurlquery.h>

#include "html_selector.h"
#include "html_page.h"

using namespace Html;



QHash<QByteArray, int> Tag::list = QHash<QByteArray, int> {
    { HTML_ANY_TAG, Tag::tg_any }, { HTML_TEXT_BLOCK, Tag::tg_text },
    { QByteArrayLiteral("html"), Tag::tg_html }, { HTML_TAG_HEAD, Tag::tg_head },
    { HTML_TAG_BODY, Tag::tg_body }, { QByteArrayLiteral("colgroup"), Tag::tg_colgroup },
    { QByteArrayLiteral("caption"), Tag::tg_caption }, { QByteArrayLiteral("i"), Tag::tg_i },
    { QByteArrayLiteral("li"), Tag::tg_li }, { QByteArrayLiteral("dt"), Tag::tg_dt },
    { QByteArrayLiteral("dd"), Tag::tg_dd }, { QByteArrayLiteral("p"), Tag::tg_p },
    { QByteArrayLiteral("address"), Tag::tg_address }, { QByteArrayLiteral("article"), Tag::tg_article },
    { QByteArrayLiteral("aside"), Tag::tg_aside }, { QByteArrayLiteral("blockquote"), Tag::tg_blockquote },
    { QByteArrayLiteral("details"), Tag::tg_details }, { QByteArrayLiteral("div"), Tag::tg_div },
    { QByteArrayLiteral("dl"), Tag::tg_dl }, { QByteArrayLiteral("fieldset"), Tag::tg_fieldset },
    { QByteArrayLiteral("figcaption"), Tag::tg_figcaption }, { QByteArrayLiteral("figure"), Tag::tg_figure },
    { QByteArrayLiteral("footer"), Tag::tg_footer }, { QByteArrayLiteral("form"), Tag::tg_form },
    { QByteArrayLiteral("h1"), Tag::tg_h1 }, { QByteArrayLiteral("h2"), Tag::tg_h2 },
    { QByteArrayLiteral("h3"), Tag::tg_h3 }, { QByteArrayLiteral("h4"), Tag::tg_h4 },
    { QByteArrayLiteral("h5"), Tag::tg_h5 }, { QByteArrayLiteral("h6"), Tag::tg_h6 },
    { QByteArrayLiteral("header"), Tag::tg_header }, { QByteArrayLiteral("hr"), Tag::tg_hr },
    { QByteArrayLiteral("main"), Tag::tg_main }, { QByteArrayLiteral("menu"), Tag::tg_menu },
    { QByteArrayLiteral("nav"), Tag::tg_nav }, { QByteArrayLiteral("ol"), Tag::tg_ol },
    { QByteArrayLiteral("pre"), Tag::tg_pre }, { QByteArrayLiteral("section"), Tag::tg_section },
    { QByteArrayLiteral("table"), Tag::tg_table }, { QByteArrayLiteral("ul"), Tag::tg_ul },
    { HTML_TAG_A, Tag::tg_a }, { QByteArrayLiteral("audio"), Tag::tg_audio },
    { QByteArrayLiteral("del"), Tag::tg_del }, { QByteArrayLiteral("ins"), Tag::tg_ins },
    { QByteArrayLiteral("map"), Tag::tg_map }, { QByteArrayLiteral("noscript"), Tag::tg_noscript },
    { QByteArrayLiteral("video"), Tag::tg_video },
    { QByteArrayLiteral("rt"), Tag::tg_rt }, { QByteArrayLiteral("rp"), Tag::tg_rp },
    { QByteArrayLiteral("optgroup"), Tag::tg_optgroup }, { QByteArrayLiteral("option"), Tag::tg_option },
    { QByteArrayLiteral("thead"), Tag::tg_thead }, { QByteArrayLiteral("tbody"), Tag::tg_tbody },
    { QByteArrayLiteral("tfoot"), Tag::tg_tfoot }, { QByteArrayLiteral("tr"), Tag::tg_tr },
    { QByteArrayLiteral("td"), Tag::tg_td }, { QByteArrayLiteral("th"), Tag::tg_th },
    { HTML_TAG_BR, Tag::tg_br }, { HTML_TAG_META, Tag::tg_meta },
    { HTML_TAG_LINK, Tag::tg_link }, { HTML_TAG_IMG, Tag::tg_img },
    { HTML_TAG_DOCTYPE, Tag::tg_doctype }, { HTML_TAG_XML, Tag::tg_xml },
    { HTML_TAG_INPUT, Tag::tg_input }, { QByteArrayLiteral("base"), Tag::tg_base },
    { QByteArrayLiteral("embed"), Tag::tg_embed }, { QByteArrayLiteral("area"), Tag::tg_area },
    { QByteArrayLiteral("col"), Tag::tg_col }, { QByteArrayLiteral("command"), Tag::tg_command },
    { QByteArrayLiteral("keygen"), Tag::tg_keygen }, { QByteArrayLiteral("param"), Tag::tg_param },
    { QByteArrayLiteral("source"), Tag::tg_source }, { QByteArrayLiteral("track"), Tag::tg_track },
    { QByteArrayLiteral("wbr"), Tag::tg_wbr }, { QByteArrayLiteral("object"), Tag::tg_object },
    { QByteArrayLiteral("span"), Tag::tg_span }, { HTML_TAG_IFRAME, Tag::tg_iframe },
    { HTML_TAG_STYLE, Tag::tg_style }, { HTML_TAG_SCRIPT, Tag::tg_script },
    { HTML_TAG_SELECT, Tag::tg_select }, { HTML_TAG_TEXTAREA, Tag::tg_textarea }
};

const QHash<int, bool> Tag::solo = QHash<int, bool>{
    { Tag::tg_br, true },
    { Tag::tg_meta, true },
    { Tag::tg_link, true },
    { Tag::tg_img, true },
    { Tag::tg_hr, true },
    { Tag::tg_doctype, true },
    { Tag::tg_xml, true },
    { Tag::tg_input, true },
    { Tag::tg_base, true },
    { Tag::tg_embed, true },
    { Tag::tg_area, true },
    { Tag::tg_col, true },
    { Tag::tg_command, true },
    { Tag::tg_keygen, true },
    { Tag::tg_param, true },
    { Tag::tg_source, true },
    { Tag::tg_track, true },
    { Tag::tg_wbr, true }
};

//INFO: some elements missing?
const QHash<int, bool> Tag::acceptable_by_parent = QHash<int, bool>{
    { Tag::tg_colgroup, true },
    { Tag::tg_div, true },
    { Tag::tg_fieldset, true },
    { Tag::tg_menu, true },
    { Tag::tg_object, true },
    { Tag::tg_section, true },
    { Tag::tg_span, true }
};

//const QHash<QByteArray, bool> restricted_solo_by_parent = QHash<QByteArray, bool>{
//    {QByteArrayLiteral("li"), 1}, {QByteArrayLiteral("dd"), 2}, {QByteArrayLiteral("p"), 3},
//    {QByteArrayLiteral("rt"), 4}, {QByteArrayLiteral("rp"), 4}, {QByteArrayLiteral("optgroup"), 5},
//    {QByteArrayLiteral("option"), 6}, {QByteArrayLiteral("tbody"), 7}, {QByteArrayLiteral("tfoot"), 8},
//    {QByteArrayLiteral("tr"), 9}, {QByteArrayLiteral("td"), 10}, {QByteArrayLiteral("th"), 11}
//};
//const QHash<QByteArray, bool> restricted_solo_by_sibling = QHash<QByteArray, bool>{
//    {QByteArrayLiteral("html"), 1}, {QByteArrayLiteral("head"), 2}, {QByteArrayLiteral("body"), 3},
//    {QByteArrayLiteral("li"), 4}, {QByteArrayLiteral("dt"), 5}, {QByteArrayLiteral("dd"), 5},
//    {QByteArrayLiteral("p"), 6}, {QByteArrayLiteral("rt"), 7}, {QByteArrayLiteral("rp"), 7},
//    {QByteArrayLiteral("optgroup"), 8}, {QByteArrayLiteral("option"), 9}, {QByteArrayLiteral("colgroup"), 10},
//    {QByteArrayLiteral("caption"), 11}, {QByteArrayLiteral("thead"), 12}, {QByteArrayLiteral("tbody"), 13},
//    {QByteArrayLiteral("tfoot"), 14}, {QByteArrayLiteral("tr"), 15}, {QByteArrayLiteral("td"), 16},
//    {QByteArrayLiteral("th"), 17}
//};

// html -> immediately not comment
// body -> immediately not comment
// head -> immediately not comment or space
// colgroup -> immediately not comment or space
// caption -> immediately not comment or space

// i -> parent close ?
// li -> next li or parent close
// dt -> next dt or dd
// dd -> next dt or parent close

// p -> next is address, article, aside, blockquote, details, div, dl, fieldset, figcaption, figure, footer, form, h1, h2, h3, h4, h5, h6, header, hr, main, menu, nav, ol, p, pre, section, table, or ul
//      and parent not eql to a, audio, del, ins, map, noscript, video
//      parent close

// rt -> next rt or rp or parent close
// rp -> next rt or rp or parent close

// optgroup -> next optgroup or parent close
// option -> next option or optgroup or parent close

// thead -> next tbody or tfoot
// tbody -> next tbody or tfoot or parent close
// tfoot -> next tbody or parent close
// tr -> next tr or parent close
// td -> next td or th or parent close
// th -> next td or th or parent close

QByteArray Tag::selectValue() const {
    Html::Set options = find("option[selected]");
    return options.value();
}
QByteArray Tag::radioValue() const { return hasAttr(attr_checked) ? _attrs[attr_default] : QByteArray(); }
QByteArray Tag::textareaValue() const { return text(); }

QByteArray Tag::value(const QByteArray & name) const {
    bool is_default_val = name == attr_default;

    if (is_default_val) {
        if (_tag_id == tg_select)
            return selectValue();

        if (_tag_id == tg_textarea)
            return textareaValue();

        if (_attrs.value(attr_type) == type_radio)
            return radioValue();
    }

    return _attrs.value(name);
}

QByteArray Tag::text() const {
    const Tag * text = (_tag_id == tg_text ? this : child(tkn_text_block));
    return text ? text -> _attrs.value(tkn_text_block) : QByteArray();
}
QByteArray Tag::texts() const {
    if (_tag_id == tg_text)
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
    if (_tag_id == tg_text)
        return _attrs.value(tkn_text_block);
    else {
        QByteArray result;
        bool root = _tag_id == tg_any;


        if (!root) {
            result = '<' % name();

            for(QHash<QByteArray, QByteArray>::ConstIterator attr = _attrs.cbegin(); attr != _attrs.cend(); attr++)
                result = result % ' ' % attr.key() % (attr.value().isNull() ? QByteArray() : (QByteArray("=\"") % attr.value() % '"'));

            result = result % '>';
        }

        for(Set::ConstIterator tag = _tags.cbegin(); tag != _tags.cend(); tag++)
            result += (*tag) -> toByteArray();


        return root || (solo.contains(_tag_id) && _tags.isEmpty()) ? result : QByteArray(result % QByteArray("</") % name() % '>');
    }
}

Tag * Tag::child(const QByteArray & name_predicate, const int & pos) const {
    int i = 0, stag_id = tagId(name_predicate, false);

    if (stag_id == -1) return 0;

    for(Set::ConstIterator tag = _tags.cbegin(); tag != _tags.cend(); tag++) {
        if ((*tag) -> _tag_id == stag_id)
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
    QByteArray nname = tname.toLower().trimmed();
    int tag_id = tagId(nname);

    // if name of tag eql to child tag - append child to parent
    Tag * newTag = new Tag(
        tag_id, nname.length(),
        tag_id == _tag_id && !acceptable_by_parent.contains(tag_id) ? parent() : this
    );
    _tags.append(newTag);
    return newTag;
}
void Tag::appendText(const QByteArray & val) {
    Tag * newTag = appendTag(tkn_text_block);
    newTag -> addAttr(tkn_text_block, val.trimmed());
}
void Tag::appendComment(const QByteArray & val) {
    Tag * newTag = appendTag(tkn_comment_block);
    newTag -> addAttr(tkn_comment_block, val);
}

bool Tag::validTo(const Selector * selector) {    
    if (selector -> _token_id == -1 || !(selector -> _token_id == tg_any || selector -> _token_id == _tag_id))
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
