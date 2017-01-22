#include "html_tag.h"

using namespace Html;

//INFO: some servers very sensitive to params part and payload part separation ...
// appendable - appends inputs from vals, which not finded in form
// default_url - if form did not contains action, we should use source url
void Tag::serializeForm(QUrl & url, QByteArray & payload, const QHash<QString, QString> & vals, const FormSerializationFlags & flags, const QString & default_url) {
    QString action = value(attr_action);
    url = QUrl(action.isEmpty() ? default_url : action);

    Set inputs = find("input") << find("select");
    QHash<QString, QString> url_vals(vals);

    if (!inputs.isEmpty()) {
        QUrlQuery query = QUrlQuery();

        for(Set::Iterator input = inputs.begin(); input != inputs.end(); input++) {
            QString inp_name = (*input) -> value(attr_name);
            QString inp_val = url_vals.take(inp_name);
            if (inp_val.isEmpty()) inp_val = (*input) -> value();

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
//                QUrl Tag::serializeFormToUrl(const QHash<QString, QString> & vals, const FormSerializationFlags & flags, const QString & default_url) { // not full support of inputs
//                    QString action = value(attr_action);
//                    QUrl url = QUrl(action.isEmpty() ? default_url : action);

//                    Set inputs = find("input") << find("select");
//                    QHash<QString, QString> url_vals(vals);

//                    if (!inputs.isEmpty()) {
//                        QUrlQuery query = QUrlQuery(url.query());

//                        for(Set::Iterator input = inputs.begin(); input != inputs.end(); input++) {
//                            QString inp_name = (*input) -> value(attr_name);
//                            QString inp_val = url_vals.take(inp_name);
//                            if (inp_val.isEmpty()) inp_val = (*input) -> value();

//                            query.addQueryItem(inp_name, flags & fsf_percent_encoding ? QUrl::toPercentEncoding(inp_val) : inp_val);
//                        }

//                        if (flags & fsf_append_vals_from_hash && !url_vals.isEmpty())
//                            for(QHash<QString, QString>::Iterator it = url_vals.begin(); it != url_vals.end(); it++)
//                                query.addQueryItem(it.key(), flags & fsf_percent_encoding ? QUrl::toPercentEncoding(it.value()) : it.value());

//                        url.setQuery(query);
//                    }

//                    return url;
//                }
QUrl Tag::serializeFormToUrl(const QHash<QString, QString> & vals, const FormSerializationFlags & flags, const QString & default_url) { // not full support of inputs
    QUrl url;
    QByteArray payload;

    serializeForm(url, payload, vals, flags, default_url);
    url.setQuery(QUrlQuery(payload + '&' + url.query()));
    return url;
}
QString Tag::toText() const {
    if (_name == tkn_text_block)
        return attrs.value(tkn_text_block);
    else {
        QString result;

        for(Set::ConstIterator tag = tags.cbegin(); tag != tags.cend(); tag++)
            result += (*tag) -> toText();

        return result;
    }
//                    const Tag * text = (_name == tkn_text_block ? this : childTag(tkn_text_block));
//                    return text ? text -> attrs.value(tkn_text_block) : QString();
}
QString Tag::toHtml() const {
    if (_name == tkn_text_block)
        return attrs.value(tkn_text_block);
    else {
        QString result = QString(_level * 2, ' ') % '<' % _name;

        for(QHash<QString, QString>::ConstIterator attr = attrs.constBegin(); attr != attrs.constEnd(); attr++)
            result = result % ' ' % attr.key() % QStringLiteral("=\"") % attr.value() % '"';

        result = result % '>';

        for(Set::ConstIterator tag = tags.cbegin(); tag != tags.cend(); tag++)
            result += (*tag) -> toHtml();

        return Document::solo.contains(_name) && tags.isEmpty() ? result : QString(result % QStringLiteral("</") % _name % '>');
    }
}

bool Tag::validTo(const Selector * selector) {
    for(QHash<Selector::SState, QString>::ConstIterator it = selector -> _tokens.cbegin(); it != selector -> _tokens.cend(); it++) {
        switch(it.key()) {
            case Selector::tag: { if (!(it.value() == tkn_any_elem || _name == it.value())) return false; break; }
            case Selector::attr: {
                for(QHash<QString, QPair<char, QString> >::ConstIterator it = selector -> _attrs.cbegin(); it != selector -> _attrs.cend(); it++) {
                    QString tag_value = it.key() == QStringLiteral("text") ? text() : attrs.value(it.key());
                    QString selector_value = it.value().second;

                    switch(it.value().first) {
                        case Selector::attr_rel_eq: {
                            if (!(attrs.contains(it.key()) && (selector_value == tkn_any_elem || tag_value == selector_value)))
                                return false;
                            break;}
                        case Selector::attr_rel_begin: {
                            if (!tag_value.startsWith(selector_value))
                                return false;
                            break;}
                        case Selector::attr_rel_end: {
                            if (!tag_value.endsWith(selector_value))
                                return false;
                            break;}
                        case Selector::attr_rel_match: {
                            if (tag_value.indexOf(selector_value) == -1)
                                return false;
                            break;}
                        case Selector::attr_rel_not: {
                            if (tag_value.indexOf(selector_value) != -1)
                                return false;
                            break;}

                        default: qDebug() << "UNSUPPORTED PREDICATE " << it.value().first;
                    };
                }
                break;
            }
            case Selector::id:  { if (attrs[attr_id] != it.value()) return false; break; }
            case Selector::klass: { //TODO: optimisation needed
                QStringList node_klasses = attrs[attr_class].split(tkn_split, QString::SkipEmptyParts);
                if (node_klasses.isEmpty()) return false;

                for(QStringList::ConstIterator it = selector -> klasses.cbegin(); it != selector -> klasses.cend(); it++) {
                    bool finded = false;
                    for(QStringList::Iterator xit = node_klasses.begin(); xit != node_klasses.end(); xit++) // TODO: if list generated each time - remove finded classes for speed up of the proccess of search
                        if ((finded = (*xit) == (*it))) break;

                    if (!finded) return false;
                }
                break;
            }
            case Selector::type: {
                if (!((_name == tag_input || _name == tag_select) && attrs[attr_type] == it.value())) return false;
                break;
            }
            default: ;
        }
    }

    return true;
}

Set & Tag::backwardFind(Selector * selector, Set & set) {
    if (!parent) return set;

    if (parent -> validTo(selector))
        selector = selector -> next;

    if (!selector)
        set.append(parent);
    else
        if (selector -> isBackward()) {
            if (parent -> parent)
                parent -> backwardFind(selector, set);
        }
        else parent -> children().find(selector, set);

    return set;
}

QHash<QString, QString> & Tag::backwardFindLinks(Selector * selector, QHash<QString, QString> & links) {
    if (!parent) return links;

    if (parent -> validTo(selector))
        selector = selector -> next;

    if (!selector) {
        if (parent -> is_link())
            links.insert(parent -> link(), parent -> text());
    } else if (selector -> isBackward() && parent -> parent)
        parent -> backwardFindLinks(selector, links);

    return links;
}