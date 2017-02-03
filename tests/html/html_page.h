#ifndef HTML_PAGE_H
#define HTML_PAGE_H

#include "html_global.h"
#include "unicode_decoding.h"

#include "html_set.h"
#include "html_tag.h"
#include "html_selector.h"

#define NAME_BUFF QByteArray(sname, (ename ? ename : pdata) - sname)
#define NAME_BUFF_VALID sname && (pdata - sname) > 1
#define VAL_BUFF (sval == 0 ? QByteArray() : QByteArray(sval, pdata - sval))
#define VAL_BUFF_VALID sval && (pdata - sval) > 1

class QIODevice;
class QDebug;

namespace Html {
    class HTMLSHARED_EXPORT Page : public UnicodeDecoding {
        enum StateFlags {
            sf_none = 0,
            sf_html = 1,
            sf_xml = 2,
            //...
            sf_use_doc_charset = 64,
            sf_use_user_charset = 128
        };
        enum ParseFlags { pf_none = 0, pf_skip_text = 1, pf_skip_comment = 2 };

        enum PState {
            content = 1,
            tag = 2,
            attr = 4,
//            in_attr = 8,
            val = 16,
            in_val = 32,
            comment = 64,
//            javascript = 128,
            raw_data = 256,
            tag_closing = 512,
            tag_exit = 1024,
            attr_val = attr | val
        };

        enum PToken {
            question_token = 63, // ?
            open_tag = 60, // <
            close_tag_predicate = 47, // /
            close_tag = 62, // >
            space = 32,
            service_token = 33, // !
            raw_data_token = 91, // [
            raw_data_end_token = 93, // ]
            comment_token = 45, // -
            attr_rel = 61, // =
            content_del1 = 34, // "
            content_del2 = 39, // '
            mean_sym = 92, /* \ */
            code_start = 38, // &
            code_unicode = 35, // #
            code_end = 59 // ;
        };

        void parse(const char * data);
        QString parseCode(char * ch);

        void checkCharset(Tag * tag);
        void proceedCharset(Tag * tag);

        Tag * root;
        ParseFlags pflags;
        StateFlags sflags;
        CharsetType charset;
//        bool charset_finded, using_default_charset; // use using_default_charset for determination of rule - finded charset or not
    public:
        Page(QIODevice * device, const CharsetType & doc_charset = charset_utf8, const ParseFlags & parse_flags = pf_skip_comment);
        Page(const QString & str, const CharsetType & doc_charset = charset_utf8, const ParseFlags & parse_flags = pf_skip_comment);
        Page(const char * str_data, const CharsetType & doc_charset = charset_utf8, const ParseFlags & parse_flags = pf_skip_comment);

        inline ~Page() { delete root; }

        inline CharsetType charsetType() const { return charset; }

        inline bool isXml() { return sflags & sf_xml; }
        inline bool isHtml() { return sflags & sf_html; }


//        bool Page::isXml() {
//            Tag * tag = root -> children().first();

//            if (!tag) return false;

//            QString name = tag -> name();
//            return name.contains(tag_xml, Qt::CaseInsensitive);
//        }



        //FIXME: output of tags without close pair
        inline QString toString() { return root -> toString(); }

        inline bool hasChilds(const char * predicate) const { return root -> hasChilds(predicate); }
//        inline bool hasStr(const QString & str) { return text.contains(str, Qt::CaseInsensitive); }

        Tag * findFirst(const char * predicate) const;
        Set find(const char * predicate) const;
        Set find(const Selector * selector, const bool & findFirst = false) const;

        void output();
    };
}
#endif // HTML_PAGE_H
