#include "html_page.h"

#include <qbuffer.h>
#include <qdebug.h>

using namespace Html;

QHash<QString, bool> Page::solo = {
    {tag_br, true}, {tag_meta, true}, {tag_link, true}, {tag_img, true}, {tag_doctype, true}, {tag_xml, true}, {tag_input, true}
};

Page::Page(QIODevice * device, const CharsetType & doc_charset, const Flags & parse_flags)
    : flags(parse_flags), charset(doc_charset), charset_finded(false), using_default_charset(false)
{
    parse(device);
}
Page::Page(const QString & str, const CharsetType & doc_charset, const Flags & parse_flags)
    : flags(parse_flags), charset(doc_charset), charset_finded(false), using_default_charset(false)
{
    QByteArray ar = str.toUtf8();
    QBuffer stream(&ar);
    stream.open(QIODevice::ReadOnly);
    parse((QIODevice *)&stream);
    stream.close();
}

bool Page::isXml() {
    Tag * tag = root -> children().first();

    if (!tag) return false;

    QString name = tag -> name();
    return name.contains(tag_xml, Qt::CaseInsensitive);
}

Set Page::find(const Selector * selector, bool findFirst) const {
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

//void Page::dump() {
//    QString p = QCoreApplication::applicationDirPath() % '/' % QDateTime::currentDateTime().toString("yyyy.MM.dd_hh.mm.ss.zzz") % QStringLiteral(".html");
//    QFile f(p);
//    if (f.open(QFile::WriteOnly)) {
//        QString;


//        f.write(readAll());
//        f.close();
//    }
//}

void Page::parse(QIODevice * device) {
    PState state = content;
    char * ch = new char[2](), last = 0, del = 0;
    QString name, value; name.reserve(1024); value.reserve(1024);
    Tag * elem = (root = new Tag(tkn_any_elem));
    bool is_closed = false;

    while(true) {
        if (device -> getChar(ch)) {
            if (*ch > 0 && *ch < 32) continue; // skip not printable trash
            text.push_back(*ch);

            switch (state) {
                case val:
                case in_val: {
                    switch(*ch) {
                        case content_del1:
                        case content_del2: {
                            switch(state) {
                                case val: { state = in_val; del = *ch; break;}
                                case in_val: {
                                    if (del == *ch) {
                                        elem -> addAttr(name, value);
                                        state = attr;
                                    }
                                    else value.append(*ch);
                                break;}
                                default: { qDebug() << "WRONG STATE" << state; return; }
                            }
                        break;}
                        case code_start: { value.append(parseCode(device, ch)); break; }
                        default:
                            if (*ch > 0) value.append(*ch);
                            else toUtf8(charset, device, value, ch[0]);
                    }
                break;}

                case content: {
                    switch(*ch) {
                        case open_tag: {
                            if (last == close_tag_predicate && elem -> is_script())
                                name.append(*ch); // javascript comments
                            else {
                                if (!(flags & skip_text) && !name.isEmpty()) elem -> appendText(name);
                                state = tag;
                            }
                        break;}
                        case code_start: { name.append(parseCode(device, ch)); break; } // &quot; and etc
                        case space: if (name.isEmpty()) continue;
                        default:
                            if ((last = *ch) > 0) name.append(*ch);
                            else toUtf8(charset, device, name, ch[0]);
                    }
                break;}

                case service: {
                    switch(*ch) {
                        case close_tag: {
                            // block closing on > in middle of text
                            bool closed_correctly = last == ']';
                            bool started_correctly = name[0] == '[';

                            if (started_correctly == closed_correctly) { // <![CDATA[ */ @import url(/css/al/ie6.css?26); /* ]]>
                                if (flags & skip_service) name.clear();
                                else elem -> appendService(name);
                                state = content; // need to check
                                continue;
                            }
                        }
                        default:
                            if (*ch > 0) name.append(*ch);
                            else toUtf8(charset, device, name, ch[0]);
                    }
                    last = *ch;
                break;}

                case comment: {
                    switch(*ch) {
//                                        case comment_post_token: break; // skip -
                        case close_tag: {
                            if (last == comment_post_token) {
                                if (flags & skip_comment) name.clear();
                                else elem -> appendComment(name);
                                state = content;
                                break;
                            }
                        }
                        default:
                            if ((last = *ch) > 0) name.append(*ch);
                            else toUtf8(charset, device, name, ch[0]);
                    }
                break;}

                default: switch(*ch) {
                    case space: {
                        switch(state) {
                            case attr:
                            case val: { if (!name.isEmpty()) elem -> addAttr(name, value); state = attr; break; } // proceed attrs without value
                            case tag: {
                                if (last != close_tag_predicate) {
                                    elem = elem -> appendTag(name);
                                    state = attr;
                                }
                            break;}
                            default: /*continue*/; // else skip spaces
                        }
                    break;}

                    case attr_rel: state = val; break;

                    case close_tag_predicate: {
                        last = *ch;
                        switch (state) {
                            case tag: is_closed = true; break;
                            case attr: state = tag;
                            default: ;
                        }
                    break; }

                    case close_tag: {
                        if (!(charset_finded || using_default_charset))
                            checkCharset(elem);

                        if (!name.isEmpty()) {
                            if (state & attr_val) {
                                if (name[0] != '?') // ignore ?>
                                    elem -> addAttr(name, value); // proceed attrs without value // if (isSolo(elem)) elem = elem -> parentTag();

                                if (isSolo(elem)) elem = elem -> parentTag();
                            } else {
                                if (is_closed) {
                                    if (elem -> name() == name) elem = elem -> parentTag();// add ignoring of the close tag for solo tags
                                    name.clear(); is_closed = false;
                                } else {
                                    if (last != close_tag_predicate && !isSolo(name)) elem = elem -> appendTag(name);
                                    else elem -> appendTag(name);
                                }
                            }
                        } else {
                            if (isSolo(elem) || last == close_tag_predicate) elem = elem -> parentTag();
                        }

                        state = content;

                        break;}

                    default: {
                        if (state == tag && last == service_token) {
                            name.clear();
                            state = (*ch == comment_post_token) ? comment : service;
                            name.append((last = *ch));
                        continue;}

                        name.append((last = *ch));
                    }
                }
            }
        } else break;
    }
    delete ch;
}

QString Page::parseCode(QIODevice * device, char * ch) {
    QString code;
    bool is_unicode = false;
    while(true) {
        if (device -> getChar(ch)) {
            switch(*ch) {
                case code_unicode: { is_unicode = true; break;}
                case code_end:
                    return is_unicode ? QChar(code.toInt()) : html_entities.value(code);
                default:
                    if ((*ch > 47 && *ch < 58) || (*ch > 96 && *ch < 123))
                        code.append(*ch);
                    else { device -> ungetChar(*ch); return code.prepend('&'); }
            }
        } else return code.prepend('&');
    }
}

void Page::checkCharset(Tag * tag) {
    if (tag -> is_meta() || tag -> is_xml_head())
        proceedCharset(tag);
    else if (tag -> is_head())
        using_default_charset = true;
}

void Page::proceedCharset(Tag * tag) {
    if (tag -> is_xml_head()) {
        QString xml_encoding = tag -> value(tkn_encoding);
        qDebug() << xml_encoding;
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
            qDebug() << meta;
            charset = toCharsetType(meta);
            charset_finded = true;
        }
    }
}

void Page::output() { qDebug() << (*root); }
