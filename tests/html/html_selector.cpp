#include "html_selector.h"
#include <qdebug.h>

using namespace Html;

void Selector::addPredicate(const SState & state, const QByteArray & token) {
    switch(state) {
        case st_tag: { _token = token; break;}
        case st_id: { _attrs.insert(attr_id, QPair<char, QByteArray>(sel_attr_eq, token)); break; }
        case st_class: { _classes.append(token.split(' ')); break;}
        case st_attr_type: {
            bool ok;
            int level = token.toInt(&ok, 10);
            if (ok)
                pos_limit = level;
            else
                _attrs.insert(token, QPair<char, QByteArray>(sel_attr_eq, tkn_any_elem));
        break;}
        default: qDebug() << "pipec";
    }
}

void Selector::addAttr(const QByteArray & name, const QByteArray & val, const char & rel) {
    if (val.isEmpty())
        _attrs.insert(name, QPair<char, QByteArray>(sel_attr_eq, tkn_any_elem));
    else
        _attrs.insert(name, QPair<char, QByteArray>(rel, val));
}

//TODO: add :3 - position limitation
Selector::Selector(const char * predicate) : _token(tkn_any_elem), turn(any), pos_limit(-1), prev(0)/*, next(0)*/ {
    SState state = st_tag;
    Selector * selector = this;
    const char * pdata = predicate, * stoken = pdata, * etoken = 0, * rel = 0, * sval = 0;
    bool in_attr = false;

    //> *:active:3[name='Loop' top] div p.loop #id.tool .yopt[gog loh] ['piza to'=123] p[text*'sdfsdf \'ssda'],a:active > .sos

    while(*pdata) {
        switch(state) {
            case st_in_name: {
                if (*stoken == *pdata && *(pdata - 1) != '/')
                    state = st_attr;
            break;}
            case st_in_val: {
                if (*sval == *pdata && *(pdata - 1) != '/')
                    state = st_attr;
            break;}

            default: {
                switch(*pdata) {
                    case sel_id_token:
                    case sel_class_token: {
                        if (TOKEN_BUFF_VALID) {
                            selector -> addPredicate(state, TOKEN_BUFF);
                            stoken = pdata + 1;
                        }

                        state = (SState)*pdata;
                    break;}

                    case sel_attr_match2:{
                        if (!in_attr) {
                            pdata++;
                            continue;
                        }
                    }
                    case sel_attr_eq:
                    case sel_attr_begin:
                    case sel_attr_begin2:
                    case sel_attr_end:
                    case sel_attr_not: {
                    attr_rel_mark:
                        state = st_attr_value;
                        etoken = pdata;
                        rel = pdata;
                        sval = pdata + 1;
                    break;}


                    case sel_attr_token_end: {
                        in_attr = false;
                        if (TOKEN_BUFF_VALID) {
                            selector -> addAttr(TOKEN_BUFF, VAL_BUFF, *rel);
                            stoken = pdata + 1;
                        }
                        state = st_tag;
                    break;}

                    case sel_attr_token: {
                        in_attr = true;

                        if (TOKEN_BUFF_VALID)
                            selector -> addPredicate(state, TOKEN_BUFF);

                        stoken = pdata + 1;
                        state = st_attr;
                    break;}


                    case sel_attr_type_token: {
                        if (in_attr) {
                            int y = 0;
                        }
                        else {
                            if (TOKEN_BUFF_VALID)
                                selector -> addPredicate(state, TOKEN_BUFF);

                            stoken = pdata + 1;
                            state = (SState)*pdata;
                        }
                    break;}

                    case sel_cont1_token:
                    case sel_cont2_token: {
                        if (state == st_attr_value)
                            state = st_in_val;
                        else
                            state = st_in_name;

                    break;}

                    case sel_rel_any: {
                        if (in_attr) {
                            if (TOKEN_BUFF_VALID) {
                                selector -> addAttr(TOKEN_BUFF, VAL_BUFF, rel);
                            }
                        } else {
                            if (stoken && !TBUFF_VALID/*!in_attr && state == st_tag*/) {
                                stoken = ++pdata;
                                continue;
                            }
                        }
                    }

                    case sel_rel_attr_match: {
                        if (in_attr) {
                            goto attr_rel_mark;
                        }
                    }
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
