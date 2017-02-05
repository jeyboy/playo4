#include "html_page.h"

#include <qdebug.h>

using namespace Html;

Page::Page(QIODevice * device, const CharsetType & doc_charset, const ParseFlags & parse_flags)
    : pflags(parse_flags), sflags(sf_none), charset(doc_charset)
{
    QByteArray data = device -> readAll();
    parse(data.constData());
}
Page::Page(const QString & str, const CharsetType & doc_charset, const ParseFlags & parse_flags)
    : pflags(parse_flags), sflags(sf_none), charset(doc_charset)
{
    parse(QSTR_TO_CHAR(str));
}

Page::Page(const char * str_data, const CharsetType & doc_charset, const ParseFlags & parse_flags)
    : pflags(parse_flags), sflags(sf_none), charset(doc_charset)
{
    parse(str_data);
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
    Tag * elem = (root = new Tag(HTML_ANY_TAG));
    PState state = content;
    const char *pdata = data, *sname = 0, *sval = 0, *ename = 0;

    while(*pdata) {
        if (*pdata < 32 && *pdata > 0) { // skip not printable trash
            pdata++;

            if (sname && !NAME_BUFF_VALID) sname++;
            continue;
        }

        switch(state) {
            case content: {
                switch(*pdata) {
                    case space: {
                        if (sname && !NAME_BUFF_VALID) sname++;
                    break;}

                    case open_tag: {
                        if (NAME_BUFF_VALID) {
                            if (!(pflags & pf_skip_text))
                                elem -> appendText(NAME_BUFF);
                            sname = 0;
                        }

                        state = tag;
                        sname = pdata + 1;

                        if (*sname == service_token) {
                            char chr = *(pdata + 2);

                            if (chr == raw_data_token)
                                state = raw_data;
                            else if (chr == comment_token)
                                state = comment;
                            else
                                sflags = (StateFlags)(sflags | sf_html);
                        } else if (*sname == question_token) {
                            sflags = (StateFlags)(sflags | sf_xml);
                        }
                    break;}
                }
            break;}

            case val: {
                switch(*pdata) {
                    case close_tag:
                    case space: {
                        elem -> addAttr(NAME_BUFF, VAL_BUFF);
                        sname = 0; sval = 0; ename = 0;
                        state = attr;
                        continue;
                    break;}
                }
            break;}

            case in_val: {
                switch(*pdata) {
                    case content_del1:
                    case content_del2: {
                        if (*sval == *pdata) {
                            sval++;
                            elem -> addAttr(NAME_BUFF, VAL_BUFF);
                            sname = 0; sval = 0; ename = 0;
                            state = attr;
                        }
                    break;}
                }
            break;}

            case in_attr: {
                switch(*pdata) {
                    case content_del1:
                    case content_del2: {
                        if (*sname == *pdata) {
                            sname++;
                            ename = pdata;
                            state = attr;
                        }
                    break;}
                }
            break;}

            case tag_exit: {
                switch(*pdata) {
                    case close_tag: {
                        if (sflags < sf_use_doc_charset)
                            checkCharset(elem);

//                      use this check for strict verification (open tag is eql to close)
                        if (*(pdata - 1) == close_tag_predicate || elem -> isSolo() || (sname && elem -> name() == NAME_BUFF))
                            elem = elem -> parentTag();
                        else
                            qDebug() << "IGNORE CLOSING OF TAG";

                        state = content;
                        sname = pdata + 1;
                    break;}
                }
            break;}

            case code: {
                switch(*pdata) {
                    case space: {
                        if (sname && !NAME_BUFF_VALID) sname++;
                    break;}

                    case open_tag: {
                        if (*(pdata + 1) == close_tag_predicate && elem -> isClosableBy(pdata + 2) /**(pdata + 2) == 's' && *(pdata + 3) == 'c' && *(pdata + 4) == 'r'*/) {
                            if (NAME_BUFF_VALID) {
                                if (!(pflags & pf_skip_text))
                                    elem -> appendText(NAME_BUFF);
                            }

                            pdata += 2;
                            sname = pdata;
                            state = tag_exit;
                        }
                    }
                }
            break;}

            case raw_data: {
                switch(*pdata) {
                    case close_tag: {
                        if (*(pdata - 1) == raw_data_end_token && *(pdata - 2) == raw_data_end_token) {
                            // extract cdata from str
                            state = content;
                            sname = pdata + 1;
                        }
                    break;}

                    default:;
                }
            break;}

            case comment: {
                switch(*pdata) {
                    case close_tag: {
                        if (*(pdata - 1) == comment_token && *(pdata - 2) == comment_token) {
                            if (!(pflags & pf_skip_comment))
                                elem -> appendComment(NAME_BUFF);

                            sname = pdata + 1;
                            state = content;
                        }
                    }
                    default:;
                }
            break;}

            default: {
                switch(*pdata) {
                    case space: {
                        switch(state) {
                            case attr:
                            case val: {
                                if (NAME_BUFF_VALID)
                                    elem -> addAttr(NAME_BUFF, VAL_BUFF);

                                sval = 0; sname = 0; ename = 0;

                                if (*(pdata + 1) == content_del1 || *(pdata + 1) == content_del2) {
                                    state = in_attr;
                                    sname = ++pdata;
                                }
                                else {
                                    state = attr;
                                    sname = pdata + 1;
                                }
                            break; }

                            case tag: {
                                elem = elem -> appendTag(NAME_BUFF);
                                state = attr;
                                sname = pdata + 1;
                            break;}
                            default:;
                        }
                    break;}

                    case attr_rel: {                   
                        ename = pdata;
                        sval = pdata + 1;
                        if (*sval == content_del1 || *sval == content_del2) {
                            state = in_val;
                            pdata++;
                        }
                        else state = val;
                    break;}

                    case close_tag: {
                        switch(state) {
                            case attr:
                            case val: {
                                if (sname && *(pdata - 1) != question_token) // ignore ?>
                                    elem -> addAttr(NAME_BUFF, VAL_BUFF);

                                sname = 0; sval = 0; ename = 0;
                            break;}

                            case tag: {
                                elem = elem -> appendTag(NAME_BUFF);
                            break;}
                            default:;
                        }

                        state = content;

                        if (elem -> isSolo()) {
                            if (sflags < sf_use_doc_charset)
                                checkCharset(elem);

                            elem = elem -> parentTag();
                        } else if (elem -> isCodeBlock()) {
                            state = code;
                        }


                        sname = pdata + 1;
                    break;}

                    case close_tag_predicate: {
                        switch (state) {
                            case attr_val: {
                                elem -> addAttr(NAME_BUFF, VAL_BUFF);
                                sname = 0; sval = 0; ename = 0;
                            }
                            case tag: {state = tag_exit; sname++; break;}
                            case attr: state = tag_exit;
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

//QString Page::parseCode(char * ch) {
//    QString code;
//    bool is_unicode = false;
//    while(ch) {
//        switch(*ch) {
//            case code_unicode: { is_unicode = true; break;}
//            case code_end: return QChar(is_unicode ? code.toInt() : html_entities.value(code));
//            default:
//                if (*ch < 123 && (*ch > 96 || (*ch < 58 && *ch > 47)))
////                    if ((*ch > 47 && *ch < 58) || (*ch > 96 && *ch < 123))
//                    code.append(*ch);
//                else { --ch; return code.prepend('&'); }
//        }

//        ch++;
//    }

//    return code.prepend('&');
//}

void Page::checkCharset(Tag * tag) {
    if (tag -> isMeta() || tag -> isXmlHead())
        proceedCharset(tag);
    else if (tag -> isHead())
        sflags = (StateFlags)(sflags | sf_use_user_charset);
}

void Page::proceedCharset(Tag * tag) {
    if (tag -> isXmlHead()) {
        QString xml_encoding = tag -> value(tkn_encoding);
        if (!xml_encoding.isEmpty()) {
            charset = toCharsetType(xml_encoding);
            sflags = (StateFlags)(sflags | sf_use_doc_charset);
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
            sflags = (StateFlags)(sflags | sf_use_doc_charset);
        }
    }
}

void Page::output() { qDebug() << (*root); }
