#include "html_set.h"

#include "html_tag.h"
#include "html_selector.h"

using namespace Html;

QByteArray Set::link() { return (isEmpty()) ? QByteArray() : first() -> link(); }
QByteArray Set::text() { return (isEmpty()) ? QByteArray() : first() -> text(); }
QByteArray Set::value(const QByteArray & name) { return (isEmpty()) ? QByteArray() : first() -> value(name); }

Set Set::find(const char * predicate, const bool & find_first) const {
    Selector selector(predicate);
    return find(&selector, find_first);
}

Set & Set::find(const Selector * selector, Set & set, const bool & find_first) const {
    for(Set::ConstIterator tag = cbegin(); tag != cend(); tag++) {
        bool has_children = (*tag) -> hasChildren();

        if (!has_children && selector -> next) continue; // ignore leafs if selector has next segment

        if ((*tag) -> validTo(selector)) {
                if (selector -> next) {
                    if (selector -> next -> isBackward())
                        (*tag) -> backwardFind(selector -> next, set);
                    else if (has_children)
                        (*tag) -> children().find(selector -> next, set);
                }
                else {
                    set.append((*tag));
                    if (find_first) break;
                }
        }
        else if (!selector -> isDirect() && has_children)
            (*tag) -> children().find(selector, set);

        if (find_first && !set.isEmpty()) break;
    }

    return set;
}

//QHash<QString, QString> & Set::findLinks(const Selector * selector, QHash<QString, QString> & links) const {
//    for(Set::Iterator tag = begin(); tag != end(); tag++) {
//        if ((*tag) -> validTo(selector)) {
//            if (selector -> next) {
//                if (selector -> next -> isBackward())
//                    (*tag) -> backwardFindLinks(selector -> next, links);
//                else if (!(*tag) -> children().isEmpty())
//                    (*tag) -> children().findLinks(selector -> next, links);
//            } else if ((*tag) -> is_link())
//                links.insert((*tag) -> link(), (*tag) -> text());
//        }
//        else if (!selector -> isDirect() && !(*tag) -> children().isEmpty())
//            (*tag) -> children().findLinks(selector, links);
//    }

//    return links;
//}
