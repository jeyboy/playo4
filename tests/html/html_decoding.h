#ifndef HTML_DECODING
#define HTML_DECODING

#include <qhash.h>

#include "unicode.h"

// use for siquence replacement
//QByteArray & QByteArray::replace(int pos, int len, const QByteArray & after)

namespace Html {
    class Decoding {
    public:
        enum CharsetType {
            charset_utf8 = 0,
            charset_ascii = 1,
            charset_cp1251 = 2,
            charset_ansi = 4, // cp1252 // ISO-8859-1

            charset_max = 8,
        };

        enum DecodingFlags {
            decode_none = 0,
            decode_content = charset_max * 2,
            decode_mnemo = decode_content * 2
        };

        static QHash<QByteArray, int> html_entities;

        static CharsetType charsetType(const QByteArray & val);

        static QByteArray & decodeMnemonics(QByteArray & val);
        static QByteArray & decodeContent(const CharsetType & charset, QByteArray & val);
        static QByteArray & decodeUrl(QByteArray & url, QByteArray * base_url = 0);

        //QString Page::parseCode(char * ch) {
        //    QString code;
        //    bool is_unicode = false;
        //    while(ch) {
        //        switch(*ch) {
        //            case code_unicode: { is_unicode = true; break;}
        //            case code_end: return QChar(is_unicode ? code.toInt() : html_entities.value(code));
        //            default:
        //                if (*ch < 123 && (*ch > 96 || (*ch < 58 && *ch > 47)))
        ////                    if ((*ch > 47 && *ch < 58) || (*ch > 96 && *ch < 123))
        //                    code.append(*ch);
        //                else { --ch; return code.prepend('&'); }
        //        }

        //        ch++;
        //    }

        //    return code.prepend('&');
        //}
    };
}

#endif // HTML_DECODING
