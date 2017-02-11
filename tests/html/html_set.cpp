#include "html_set.h"

#include "html_tag.h"
#include "html_selector.h"

using namespace Html;

QString Set::link() { return (isEmpty()) ? QString() : first() -> link(); }
QString Set::text() { return (isEmpty()) ? QString() : first() -> text(); }
QString Set::value(const QByteArray & name) { return (isEmpty()) ? QString() : first() -> value(name); }

Set Set::find(const char * predicate, const bool & find_first) const {
    Selector selector(predicate);
    return find(&selector, find_first);
}

Set & Set::find(const Selector * selector, Set & set, const bool & find_first) const {
    for(Set::ConstIterator tag = cbegin(); tag != cend(); tag++) {
        if ((*tag) -> validTo(selector)) {
                if (selector -> next) {
                    if (selector -> next -> isBackward()) {
                        (*tag) -> backwardFind(selector -> next, set);
                    } else if (!(*tag) -> hasChildren())
                        (*tag) -> children().find(selector -> next, set);

                    if (find_first) return set;
                }
                else {
                    set.append((*tag));
                    if (find_first) break;
                }
        }
        else if (!selector -> isDirect() && !(*tag) -> hasChildren())
            (*tag) -> children().find(selector, set);
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
