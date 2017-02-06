#include "html_selector.h"

using namespace Html;

void Selector::addToken(const SState & state, const QByteArray & token, const char & rel) {
    switch(state) {
        case st_attr: {
            QList<QByteArray> parts = token.split(rel);
            if (parts.length() > 1)
                _attrs.insert(parts.first(), QPair<char, QByteArray>(rel, parts.last()));
            else
                _attrs.insert(parts.first(), QPair<char, QByteArray>(sel_attr_eq, tkn_any_elem));
        break;}
        case st_class: {
            _classes.append(token.split(' '));
        break;}
        case st_tag: {
            _token = token;
        break;}
        case st_attr_type: {
            _attrs.insert(token, QPair<char, QByteArray>(sel_attr_eq, tkn_any_elem));
        }
        default:;
    }
}

//TODO: add :3 - position limitation
Selector::Selector(const char * predicate) : _token(tkn_any_elem), turn(any), pos_limit(-1), prev(0)/*, next(0)*/ {
    SState state = st_tag;
    Selector * selector = this;
    const char * pdata = predicate, * stoken = pdata, *etoken = 0, * rel = 0;
    bool in_attr = false;

    //> *:active:3[name='Loop' top] div p.loop #id.tool .yopt ['piza to'=123] p[text='sdfsdf \'ssda'],a:active > .sos

    while(*pdata) {
        switch(state) {
            case st_in_text: {
                if (*stoken == *pdata && *(pdata - 1) != '/') {
                    // save

                    state = st_attr;
                }
            break;}

            default: {
                switch(*pdata) {
                    case sel_id_token:
                    case sel_class_token: {
                        if (TOKEN_BUFF_VALID) {
                            selector -> addToken(state, TOKEN_BUFF, *rel);
                            stoken = pdata + 1;
                        }

                        state = (SState)*pdata;
                    break;}


                    case sel_attr_eq:
                    case sel_attr_begin:
                    case sel_attr_begin2:
                    case sel_attr_end:
                    case sel_attr_not: {
                        // write me
                    break;}


                    case sel_attr_token_end: {
                        in_attr = false;
                        if (TOKEN_BUFF_VALID) {
                            selector -> addToken(state, TOKEN_BUFF, *rel);
                            stoken = pdata + 1;
                        }
                        state = st_tag;
                    break;}

                    case sel_attr_token: {
                        in_attr = true;
                    }

                    case sel_attr_match2:
                    case sel_attr_type_token: {
                        // write me

                        if (TOKEN_BUFF_VALID)
                            selector -> addToken(state, TOKEN_BUFF, *rel);

                        stoken = pdata + 1;
                        state = (SState)*pdata;
                    break;}

                    case sel_cont1_token:
                    case sel_cont2_token: {
                        // save
                        stoken = pdata + 1;
                        state = st_in_text;
                    break;}

                    case sel_rel_any: {
                        if (!in_attr && state == st_tag) {
                            pdata++;
                            continue;
                        }
                    }

                    case sel_rel_attr_match:
                    case sel_rel_back_parent:
                    case sel_rel_back_sibling:
                    case sel_rel_sibling:
                    case sel_rel_parent: {
                        if (!in_attr) {
                            selector = new Selector((STurn)*pdata, selector);
                            stoken = pdata + 1;
                            state = st_tag;
                        }
                    break;}

                    case sel_attr_separator: {
                        selector = new Selector(selector -> turn, selector -> prev);
                        stoken = pdata + 1;
                        state = st_tag;
                    break;}

                    default:;
                }
            }
        }

        pdata++;
    }

//    if (!token.isEmpty()) selector -> addToken(state, token, rel);
}
