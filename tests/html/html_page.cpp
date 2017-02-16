#include "html_page.h"

#include <qdebug.h>


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





using namespace Html;

//// remove me later
Page::Page(Tag * root_tag, const char * str_data, const Decoding::CharsetType & doc_charset, const ParseFlags & parse_flags)
    : root(0), pflags(parse_flags), sflags(sf_none), charset(doc_charset)
{
    parse(str_data, root_tag);
}
Page::Page(Tag * root_tag, const QByteArray & str, const Decoding::CharsetType & doc_charset, const ParseFlags & parse_flags)
   : root(0), pflags(parse_flags), sflags(sf_none), charset(doc_charset)
{
   parse(str.constData(), root_tag);
}
Page::Page(Tag * root_tag, const QString & str, const Decoding::CharsetType & doc_charset, const ParseFlags & parse_flags)
    : root(0), pflags(parse_flags), sflags(sf_none), charset(doc_charset)
{
    parse(QSTR_TO_CHAR(str), root_tag);
}
//////////////////////////
//////////////////////////


Page::Page(QIODevice * device, const Decoding::CharsetType & doc_charset, const ParseFlags & parse_flags)
    : pflags(parse_flags), sflags(sf_none), charset(doc_charset)
{
    QByteArray data = device -> readAll();
    parse(data.constData(), INIT_ROOT_TAG);
}
Page::Page(const QByteArray & str, const Decoding::CharsetType & doc_charset, const ParseFlags & parse_flags)
    : pflags(parse_flags), sflags(sf_none), charset(doc_charset)
{
    parse(str.constData(), INIT_ROOT_TAG);
}
Page::Page(const QString & str, const Decoding::CharsetType & doc_charset, const ParseFlags & parse_flags)
    : pflags(parse_flags), sflags(sf_none), charset(doc_charset)
{
    parse(QSTR_TO_CHAR(str), INIT_ROOT_TAG);
}
Page::Page(const char * str_data, const Decoding::CharsetType & doc_charset, const ParseFlags & parse_flags)
    : pflags(parse_flags), sflags(sf_none), charset(doc_charset)
{
    parse(str_data, INIT_ROOT_TAG);
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

void Page::parse(const char * data, Tag * root_tag) {
    Tag * elem = root_tag;
    PState state = content;
    const char *pdata = data, *sname = 0, *sval = 0, *ename = 0;

    while(*pdata) {
        if (*pdata < 32 && *pdata > 0) { // skip not printable trash
            if (sname && !NBUFF_VALID) sname++;

            pdata++;
            continue;
        }

        switch(state) {
            case content: {
                switch(*pdata) {
                    case space: {
                        if (sname && !NBUFF_VALID) sname++;
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
                        if (*(pdata - 1) == close_tag_predicate || elem -> isSolo() || (sname && elem -> name() == NAME_BUFF)) {
                            if (elem -> isFrame()) {
                                iframes << elem;
                                sflags = (StateFlags)(sflags | sf_has_iframes);
                            }

                            elem = elem -> parent();

                            if (!elem) {
                                elem = root;
                                sflags = (StateFlags)(sflags | sf_has_errors);
                            }
                        } else {
                            sflags = (StateFlags)(sflags | sf_has_errors);
                            qDebug() << "IGNORE CLOSING OF TAG";
                        }

                        state = content;
                        sname = pdata + 1;
                    break;}
                }
            break;}

            case code: {
                switch(*pdata) {
                    case space: {
                        if (sname && !NBUFF_VALID) sname++;
                    break;}

                    case open_tag: {
                        if (*(pdata + 1) == close_tag_predicate && elem -> isClosableBy(pdata + 2)) {
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

                            elem = elem -> parent();

                            if (!elem) {
                                elem = root;
                                sflags = (StateFlags)(sflags | sf_has_errors);
                            }

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
                            case tag: {
                                if (*(pdata - 1) != open_tag) // <br/> ant etc
                                    elem = elem -> appendTag(NAME_BUFF);

                                state = tag_exit;
                                sname++;
                            break;}
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

void Page::checkCharset(Tag * tag) {
    if (tag -> isMeta() || tag -> isXmlHead())
        proceedCharset(tag);
    else if (tag -> isHead())
        sflags = (StateFlags)(sflags | sf_use_user_charset);
}

void Page::proceedCharset(Tag * tag) { // refactor me: use qbytearray except string
    if (tag -> isXmlHead()) {
        QByteArray xml_encoding = tag -> value(tkn_encoding);
        if (!xml_encoding.isEmpty()) {
            charset = Decoding::charsetType(xml_encoding);
            sflags = (StateFlags)(sflags | sf_use_doc_charset);
        }
    } else {
        QByteArray meta = tag -> value(tkn_charset);
        if (meta.isEmpty()) {
            if (tag -> value(tkn_http_equiv).toLower() == tkn_content_type) {
                meta = tag -> value(tkn_content);

                int start_index = meta.indexOf(tkn_charset_attr);

                if (start_index != -1) { // not tested
                    start_index += tkn_charset_attr.length();
                    int end_index = meta.indexOf(' ', start_index);
                    meta = meta.mid(start_index, end_index == -1 ? -1 : (end_index - start_index));
                } else meta.clear();
            }
        }

        if (!meta.isEmpty()) {
            charset = Decoding::charsetType(meta);
            sflags = (StateFlags)(sflags | sf_use_doc_charset);
        }
    }
}

void Page::output() { qDebug() << (*root); }
