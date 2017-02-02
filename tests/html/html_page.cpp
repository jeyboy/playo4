#include "html_page.h"

#include <qdebug.h>

using namespace Html;

Page::Page(QIODevice * device, const CharsetType & doc_charset, const ParseFlags & parse_flags)
    : flags(parse_flags), charset(doc_charset), charset_finded(false), using_default_charset(false)
{
    QByteArray data = device -> readAll();
    parse(data.constData());
}
Page::Page(const QString & str, const CharsetType & doc_charset, const ParseFlags & parse_flags)
    : flags(parse_flags), charset(doc_charset), charset_finded(false), using_default_charset(false)
{
    parse(QSTR_TO_CHAR(str));
}

Page::Page(const char * str_data, const CharsetType & doc_charset = charset_utf8, const ParseFlags & parse_flags = skip_comment)
    : flags(parse_flags), charset(doc_charset), charset_finded(false), using_default_charset(false)
{
    parse(str_data)
}

bool Page::isXml() {
    Tag * tag = root -> children().first();

    if (!tag) return false;

    QString name = tag -> name();
    return name.contains(tag_xml, Qt::CaseInsensitive);
}

Set Page::find(const Selector * selector, const bool & findFirst) const {
    return root -> children().find(selector, findFirst);
}
Set Page::find(const char * predicate) const {
    Selector selector(predicate);
    return find(&selector);
}
Tag * Page::findFirst(const char * predicate) const {
    Selector selector(predicate);
    Set set = find(&selector, true);
    return set.isEmpty() ? 0 : set.first();
}

void Page::parse(const char * data) {
    Tag * elem = (root = new Tag(tkn_any_elem));
    PState state = content;

    char *pdata = data, *sname = 0, *sval = 0;
//    QString name, value; name.reserve(1024); value.reserve(1024);

    while(pdata) {
        if (*pdata > 0 && *pdata < 32) continue; // skip not printable trash

        switch(state) {
            case content: {
                switch(*pdata) {
                    case open_tag: {
//                        if (last == close_tag_predicate && elem -> isScript())
//                            name.append(*pdata); // javascript comments
//                        else {
//                            if (!(flags & skip_text) && !name.isEmpty())
//                                elem -> appendText(name);
//                            state = tag;
//                        }

                        if (sname) {
                            if (!(flags & skip_text))
                                elem -> appendText(/*QString()*/);

                            sname = 0;
                        }

                        state = tag;

                        if (*(pdata + 1) == service_token) {
                            char chr = *(pdata + 2);

                            if (chr == service_start_token)
                                state = service;
                            else if (chr == comment_token)
                                state = comment;
                        }
                    break;}

//                    case code_start: {
//                        name.append(parseCode(pdata));
//                    break; } // &quot; and etc

//                    case space: if (!sname) continue;

//                    default: last = *pdata;
                }
            break;}

            case in_val:
            case val: {
                switch(*pdata) {
                    case content_del1:
                    case content_del2: {
                        switch(state) {
                            case val: {
                                state = in_val;
                            break;}
                            case in_val: {
                                if (*sval == *pdata) {
                                    elem -> addAttr(name, value);
                                    sname = 0; sval = 0;
                                    state = attr;
                                }
//                                else value.append(*pdata);
                            break;}
                            default: { qDebug() << "WRONG STATE" << state; return; }
                        }
                    break;}
//                    case code_start: { value.append(parseCode(pdata)); break; }
//                    default:
//                        if (*pdata > 0) value.append(*pdata);
//                        else toUtf8(charset, device, value, pdata[0]);
                }
            break;}

            case tag_closing: {
                switch(*pdata) {
                    case close_tag: {
            //                    if (!(charset_finded || using_default_charset))
            //                        checkCharset(elem);

            //                    if (!name.isEmpty()) {
            //                        if (state & attr_val) {
            //                            if (name[0] != '?') // ignore ?>
            //                                elem -> addAttr(name, value); // proceed attrs without value // if (isSolo(elem)) elem = elem -> parentTag();

            //                            if ((elem) -> isSolo()) elem = elem -> parentTag();
            //                        } else {
            //                            if (is_closed) {
            //                                if (elem -> name() == name) elem = elem -> parentTag();// add ignoring of the close tag for solo tags
            //                                name.clear(); is_closed = false;
            //                            } else {
            //                                if (last != close_tag_predicate && !Tag::isSolo(name)) elem = elem -> appendTag(name);
            //                                else elem -> appendTag(name);
            //                            }
            //                        }
            //                    } else {
            //                        if (elem -> isSolo() || last == close_tag_predicate) elem = elem -> parentTag();
            //                    }

                        state = content;
                    break;}
                }
            break;}

            case service: {
                switch(*pdata) {
                    case close_tag: {
                        if (*(pdata - 1) == service_end_token && *(pdata - 2) == service_end_token) {
                            // extract cdata from str
                            state = content;
                        }
                    break;}

                    default:;
            //                        if (*pdata > 0) name.append(*pdata);
            //                        else toUtf8(charset, device, name, pdata[0]);
                }
            break;}

            case comment: {
                switch(*pdata) {

                    case close_tag: {
                    if (*(pdata - 1) == comment_token && *(pdata - 2) == comment_token) {
                        if (!flags & skip_comment)
                            elem -> appendComment(name);

                        sname = 0;
                        state = content;
                    }


            //                        if (last == comment_post_token) {
            //                            if (flags & skip_comment) name.clear();
            //                            else elem -> appendComment(name);
            //                            state = content;
            //                            break;
            //                        }
                    }
                    default:;
            //                        if ((last = *pdata) > 0) name.append(*pdata);
            //                        else toUtf8(charset, device, name, pdata[0]);
                }
            break;}

            default: {
                switch(*pdata) {
                    case space: {
                        switch(state) {
                            case attr:
                            case val: {
                                if (sname) elem -> addAttr(name, value);
                                state = attr;
                            break; } // proceed attrs without value

                            case tag: {
                                if (*(pdata - 1) != close_tag_predicate) {
                                    elem = elem -> appendTag(name);
                                    sname = 0;
                                    state = attr;
                                }
                            break;}
                            default: /*continue*/; // else skip spaces
                        }
                    break;}

                    case attr_rel: {
                        state = val;
                        sval = pdata;
                    break;}

                    case close_tag_predicate: {
                        switch (state) {
                            case tag: {state = tag_closing; break;}
                            case attr: state = tag;
                            default: ;
                        }
                    break; }

                    default:;
                }
            }
        }

        pdata++;
    }
}

QString Page::parseCode(char * ch) {
    QString code;
    bool is_unicode = false;
    while(ch) {
        switch(*ch) {
            case code_unicode: { is_unicode = true; break;}
            case code_end: return QChar(is_unicode ? code.toInt() : html_entities.value(code));
            default:
                if (*ch < 123 && (*ch > 96 || (*ch < 58 && *ch > 47)))
//                    if ((*ch > 47 && *ch < 58) || (*ch > 96 && *ch < 123))
                    code.append(*ch);
                else { --ch; return code.prepend('&'); }
        }

        ch++;
    } else return code.prepend('&');
}

void Page::checkCharset(Tag * tag) {
    if (tag -> isMeta() || tag -> isXmlHead())
        proceedCharset(tag);
    else if (tag -> isBody())
        using_default_charset = true;
}

void Page::proceedCharset(Tag * tag) {
    if (tag -> isXmlHead()) {
        QString xml_encoding = tag -> value(tkn_encoding);
        if (!xml_encoding.isEmpty()) {
            charset = toCharsetType(xml_encoding);
            charset_finded = true;
        }
    } else {
        QString meta = tag -> value(tkn_charset);
        if (meta.isEmpty()) {
            if (tag -> value(tkn_http_equiv).toLower() == tkn_content_type) {
                meta = tag -> value(tkn_content);
                meta = meta.section(tkn_charset_attr, 1).section(' ', 0);
            }
        }

        if (!meta.isEmpty()) {
            charset = toCharsetType(meta);
            charset_finded = true;
        }
    }
}

void Page::output() { qDebug() << (*root); }
