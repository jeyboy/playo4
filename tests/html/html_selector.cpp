#include "html_selector.h"

using namespace Html;

void Selector::addToken(const SState & state, QString & token, char & rel) {
    switch(state) {
        case attr: {
            QStringList parts = token.split(rel, QString::SkipEmptyParts);
            if (parts.length() > 1)
                _attrs.insert(parts.first(), QPair<char, QString>(rel, parts.last()));
            else
                _attrs.insert(parts.first(), QPair<char, QString>(attr_rel_eq, tkn_any_elem));
            rel = attr_rel_eq;
        break;}
        case klass: {
            klasses.append(token.split(' ', QString::SkipEmptyParts));
        break;}
        default:;
    }

    if (state == tag && token.isEmpty())
        token = tkn_any_elem;

    _tokens.insert(state, token);
    token.clear();
}

//TODO: add :3 - position limitation
Selector::Selector(const char * predicate) : turn(forward), prev(0), next(0) {
    SState state = Selector::tag;
    Selector * selector = this;
    const char * it = predicate;

//    char rel;
//    bool in_attr = false;

    while(*it) {
        switch(*it) {
            case attr_token_end:
            case type_token:
            case class_token:
            case id_token: {
                in_attr &= attr_token_end != *it;

                if (!in_attr) {
                    if (!token.isEmpty()) selector -> addToken(state, token, rel);
                    state = (SState)*it;
                } else token.append(*it);
            break;}

            case attr_token:
            case attr_separator: {
                in_attr |= attr_token == *it;
                selector -> addToken(state, token, rel);
                state = Selector::attr;
            break;}

            case attr_rel_eq:
            case attr_rel_begin:
            case attr_rel_end:
            case attr_rel_match:
            case attr_rel_not: {
                token.append((rel = *it));
            break;}

            case back_direct_token:
            case direct_token: {
                if (!token.isEmpty()) selector -> addToken(state, token, rel);
                selector = new Selector((SType)*it, selector);
                state = Selector::tag;
            break;}

            case space_token: {
                if (state != attr) {
                    if (!token.isEmpty())
                        selector -> addToken(state, token, rel);
                    selector = new Selector(forward, selector);
                    state = Selector::tag;
                }
            break;}

            case cont1_token:
            case cont2_token: break; // skipping

            default: token.append(*it);
        }

        it++;
    }

    if (!token.isEmpty()) selector -> addToken(state, token, rel);
}
