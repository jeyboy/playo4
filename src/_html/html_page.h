#ifndef HTML_PAGE_H
#define HTML_PAGE_H

#include <html_global.h>
#include <unicode_decoding.h>

#include <html_set.h>
#include <html_tag.h>
#include <html_selector.h>

class QIODevice;

namespace Html {
    class HTMLSHARED_EXPORT Page : public UnicodeDecoding {
        enum Flags { none = 0, skip_text = 1, skip_comment = 2, skip_service = 4 };

        enum PState {
            content = 1, tag = 2, attr = 4, /*in_attr = 8,*/ val = 16, in_val = 32, comment = 64, service = 128, attr_val = attr | val
        };

        enum PToken {
            open_tag = 60, // <
            close_tag_predicate = 47, // /
            close_tag = 62, // >
            space = 32,
            service_token = 33, // !
            comment_post_token = 45, // -
            attr_rel = 61, // =
            content_del1 = 34, // "
            content_del2 = 39, // '
            mean_sym = 92, /* \ */
            code_start = 38, // &
            code_unicode = 35, // #
            code_end = 59 // ;
        };

        inline bool isSolo(Tag * tag) { return solo.contains(tag -> name()); }
        inline bool isSolo(const QString & tag_name) { return solo.contains(tag_name); }

        void parse(QIODevice * device);
        QString parseCode(QIODevice * device, char * ch);

        void checkCharset(Tag * tag);
        void proceedCharset(Tag * tag);

        Tag * root;
        Flags flags;
        CharsetType charset;
        bool charset_finded, using_default_charset;
        QString text;

    public:
        Page(QIODevice * device, const CharsetType & doc_charset = charset_utf8, const Flags & parse_flags = skip_comment);
        Page(const QString & str, const CharsetType & doc_charset = charset_utf8, const Flags & parse_flags = skip_comment);

        inline ~Page() { delete root; }

        bool isXml();

        //FIXME: output of tags without close pair
        inline QString toHtml() { return root -> toHtml(); }

        inline bool has(const char * predicate) const { return root -> has(predicate); }
        inline bool hasStr(const QString & str) { return text.contains(str, Qt::CaseInsensitive); }

        Set find(const Selector * selector, bool findFirst = false) const;
        Set find(const char * predicate) const;
        Tag * findFirst(const char * predicate) const;

//        void dump();

        inline void output() { qDebug() << (*root); }

        static QHash<QString, bool> solo;
#endif // HTML_PAGE_H
