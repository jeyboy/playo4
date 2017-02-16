#ifndef HTML_PAGE_H
#define HTML_PAGE_H

#include "html_global.h"
#include "html_decoding.h"

#include "html_set.h"
#include "html_tag.h"
#include "html_selector.h"

#define INIT_ROOT_TAG (root = new Tag(HTML_ANY_TAG))

#define NAME_BUFF QByteArray(sname, (ename ? ename : pdata) - sname)
#define NBUFF_VALID ((pdata - sname) > 0)
#define NAME_BUFF_VALID (sname && NBUFF_VALID)
#define VAL_BUFF (sval == 0 ? QByteArray() : QByteArray(sval, pdata - sval))
#define VBUFF_VALID ((pdata - sval) > 0)
#define VAL_BUFF_VALID (sval && VBUFF_VALID)

class QIODevice;
class QDebug;

// Strict mode (http://www.w3schools.com/html/html_xhtml.asp)
    //Document Structure

    //    XHTML DOCTYPE is mandatory
    //    The xmlns attribute in <html> is mandatory
    //    <html>, <head>, <title>, and <body> are mandatory

    //XHTML Elements

    //    XHTML elements must be properly nested
    //    XHTML elements must always be closed
    //    XHTML elements must be in lowercase
    //    XHTML documents must have one root element

    //XHTML Attributes

    //    Attribute names must be in lower case
    //    Attribute values must be quoted
    //    Attribute minimization is forbidden
        //Wrong:
        //<input type="checkbox" name="vehicle" value="car" checked />

        //Correct:
        //<input type="checkbox" name="vehicle" value="car" checked="checked" />


namespace Html {
    class HTMLSHARED_EXPORT Page {
        enum StateFlags {
            sf_none = 0,
            sf_html = 1,
            sf_xml = 2,
            sf_has_errors = 4,
            sf_has_iframes = 8,
            //...
            sf_use_doc_charset = 64,
            sf_use_user_charset = 128
        };
        enum ParseFlags {
            pf_none = 0, pf_skip_text = 1, pf_skip_comment = 2, pf_skip_mnemonics_decoding = 4,
            pf_skip_content_decoding = 8, pf_skip_links_decoding = 16,

            pf_default = pf_skip_comment | pf_skip_mnemonics_decoding | pf_skip_content_decoding
        };

        enum PState {
            content = 1,
            tag = 2,
            attr = 4,
            in_attr = 8,
            val = 16,
            in_val = 32,
            comment = 64,
            code = 128,
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

        void parse(const char * data, Tag * root_tag);

        void checkCharset(Tag * tag);
        void proceedCharset(Tag * tag);

        Tag * root;
        ParseFlags pflags;
        StateFlags sflags;
        HtmlDecoding::CharsetType charset;

        Set iframes;
        friend class Tag;

        /////////////// REMOVE ME AFTER REFACTOR OF TAG // iframe tag should to store pointer on page and use it for parse
        Page(Tag * root_tag, const char * str_data, const HtmlDecoding::CharsetType & doc_charset = HtmlDecoding::charset_utf8, const ParseFlags & parse_flags = pf_default);
        Page(Tag * root_tag, const QByteArray & str, const HtmlDecoding::CharsetType & doc_charset = HtmlDecoding::charset_utf8, const ParseFlags & parse_flags = pf_default);
        Page(Tag * root_tag, const QString & str, const HtmlDecoding::CharsetType & doc_charset = HtmlDecoding::charset_utf8, const ParseFlags & parse_flags = pf_default);
        /////////////////////////////////////
    public:
        Page(QIODevice * device, const HtmlDecoding::CharsetType & doc_charset = HtmlDecoding::charset_utf8, const ParseFlags & parse_flags = pf_default);
        Page(const QString & str, const HtmlDecoding::CharsetType & doc_charset = HtmlDecoding::charset_utf8, const ParseFlags & parse_flags = pf_default);
        Page(const QByteArray & str, const HtmlDecoding::CharsetType & doc_charset = HtmlDecoding::charset_utf8, const ParseFlags & parse_flags = pf_default);
        Page(const char * str_data, const HtmlDecoding::CharsetType & doc_charset = HtmlDecoding::charset_utf8, const ParseFlags & parse_flags = pf_default);

        inline ~Page() { delete root; }

        inline HtmlDecoding::CharsetType charsetType() const { return charset; }

        inline bool isXml() { return sflags & sf_xml; }
        inline bool isHtml() { return sflags & sf_html; }

        inline QByteArray toByteArray() { return root -> toByteArray(); }

        inline bool hasIframes() const { return sflags & sf_has_iframes; }
        inline bool hasChildren(const char * predicate) const { return root -> hasChildren(predicate); }

        Tag * findFirst(const char * predicate) const;
        Set find(const char * predicate) const;
        Set find(const Selector * selector, const bool & findFirst = false) const;

        inline Set iframesList() const { return iframes; }

        void output();
    };
}
#endif // HTML_PAGE_H
