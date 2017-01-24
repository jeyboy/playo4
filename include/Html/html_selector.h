#ifndef HTML_SELECTOR_H
#define HTML_SELECTOR_H

#include <html_global.h>

#include <qpair.h>
#include <qlist.h>
#include <qhash.h>

namespace Html {
    struct HTMLSHARED_EXPORT Selector {
        enum SToken {
            id_token = 35, // #
            class_token = 46, // .
            attr_token = 91, // [
            attr_separator = 44, // ,
            attr_rel_eq = 61, // =
            attr_rel_begin = 94, // ^
            attr_rel_end = 38, // &
            attr_rel_not = 33, // !
            attr_rel_match = 126, // ~
            attr_token_end = 93, // ]
            type_token = 58, // :
            direct_token = 62, // >
            back_direct_token = 60, // <
            space_token = 32,
            cont1_token = 34, // "
            cont2_token = 39 // '
        };
        enum SType { direct = direct_token, forward, backward = back_direct_token };
        enum SState { none = attr_token_end, tag, attr, id = id_token, klass = class_token, type = type_token };

        Selector(const char * predicate);

        inline Selector(const SType & selector_type = forward, Selector * prev_selector = 0) :
            sType(selector_type), prev(prev_selector), next(0)
        {
            if (prev_selector) prev_selector -> next = this;
        }
        inline ~Selector() { delete next; }
        Selector operator= (const char * x) { return Selector(x); }

        void addToken(const SState & tType, QString & token, char & rel);

        inline bool isDirect() const { return sType == direct; }
        inline bool isBackward() const { return sType == backward; }
//                bool validTo(int index) const;
//                bool skipable(int index) const;

        QStringList klasses;
        QHash<SState, QString> _tokens;
        QHash<QString, QPair<char, QString> > _attrs;
        SType sType;

        Selector * prev;
        Selector * next;
    };
}

#endif // HTML_SELECTOR_H
