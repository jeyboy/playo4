#ifndef HTML_SELECTOR_H
#define HTML_SELECTOR_H

#include "html_global.h"

#include <qpair.h>
#include <qlist.h>
#include <qhash.h>

#define TOKEN_BUFF QByteArray(stoken, (etoken ? etoken : pdata) - stoken)
#define TBUFF_VALID ((pdata - stoken) > 0)
#define TOKEN_BUFF_VALID (stoken && TBUFF_VALID)
#define VAL_BUFF (sval == 0 ? QByteArray() : QByteArray(sval, pdata - sval))

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
            sel_attr_match2 = 42, // *
            sel_attr_type_token = 58, // :

            sel_rel_attr_match = 126, // ~ // ul ~ table // All <table> elements that are siblings of a <ul> element.
            sel_rel_parent = 62, // > // div > p // All <p> elements where the parent is a <div> element.
            sel_rel_any = 32,
            sel_rel_sibling = 43, // + // ul + h3 // The <h3> element that are next to each <ul> elements.
            sel_rel_back_parent = 60, // <
            sel_rel_back_sibling = 45, // -

            sel_cont1_token = 34, // "
            sel_cont2_token = 39 // '
        };
        enum STurn { any = sel_rel_any, parent = sel_rel_parent, sibling = sel_rel_sibling, parent_back = sel_rel_back_parent, sibling_back = sel_rel_back_sibling };
        enum SState { st_none = sel_attr_end, st_tag, st_limit, st_attr, st_attr_value, st_id = sel_id_token, st_class = sel_class_token, st_attr_type = sel_attr_type_token, st_in_name, st_in_val };

        Selector(const char * predicate);

        inline Selector(const STurn & turn = any, Selector * prev = 0)
            : _token(tkn_any_elem), turn(turn), pos_limit(-1), prev(prev)/*, next(0)*/
        {
//            if (prev) prev -> next = this;
            if (prev) prev -> next << this;
        }
        inline ~Selector() { qDeleteAll(next); }
        Selector operator= (const char * x) { return Selector(x); }

        void addPredicate(const SState & state, const QByteArray & token);
        void addAttr(const QByteArray & name, const QByteArray & val, const char & rel);

        inline bool isDirect() const { return turn == parent; }
        inline bool isBackward() const { return turn == parent_back || turn == sibling_back; }

        QList<QByteArray> _classes;
//        QHash<SState, QByteArray> _limitations;
//        QHash<SState, QByteArray> _tokens;
        QByteArray _token;
        QHash<QByteArray, QPair<char, QByteArray> > _attrs;
        STurn turn;
        int pos_limit;

        Selector * prev;
        QList<Selector *> next;
    };
}

#endif // HTML_SELECTOR_H
