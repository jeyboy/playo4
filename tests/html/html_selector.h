#ifndef HTML_SELECTOR_H
#define HTML_SELECTOR_H

#include "html_global.h"

#include <qpair.h>
#include <qlist.h>
#include <qhash.h>

namespace Html {
    struct HTMLSHARED_EXPORT Selector {
        enum SToken {
            sel_id_token = 35, // #
            sel_class_token = 46, // .

            sel_attr_token = 91, // [
            sel_attr_separator = 44, // ,
            sel_attr_token_end = 93, // ]
            sel_attr_eq = 61, // =
            sel_attr_begin = 94, // ^
            sel_attr_begin2 = 124, // |
            sel_attr_end = 38, // $
            sel_attr_not = 33, // !
            sel_attr_match = 126, // ~
            sel_attr_match2 = 42, // *
            sel_attr_type_token = 58, // :

            sel_rel_parent = 62, // >
            sel_rel_back_parent = 60, // <
            sel_rel_any = 32,
            sel_rel_sibling = 43, // +
            sel_rel_back_sibling = 45, // -

            sel_cont1_token = 34, // "
            sel_cont2_token = 39 // '
        };
        enum STurn { forward, backward };
        enum SState { none = sel_attr_end, tag, attr, id = sel_id_token, klass = sel_class_token, attr_type = sel_attr_type_token };

        Selector(const char * predicate);

        inline Selector(const QByteArray & turn = forward, Selector * prev = 0) :
            turn(turn), prev(prev), next(0) {

            if (prev_selector) prev_selector -> next = this;
        }
        inline ~Selector() { delete next; }
        Selector operator= (const char * x) { return Selector(x); }

        void addToken(const SState & state, QString & token, char & rel);

        inline bool isBackward() const { return turn == backward; }

        QList<QByteArray> _classes;
        QHash<SState, QByteArray> _tokens;
        QHash<QByteArray, QPair<char, QByteArray> > _attrs;
        STurn turn;

        Selector * prev;
        Selector * next;
    };
}

#endif // HTML_SELECTOR_H
