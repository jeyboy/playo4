#ifndef HTML_DECODING
#define HTML_DECODING

#include <qhash.h>

class HtmlDecoding {
public:
    enum CharsetType {
        charset_unknown,
        charset_ascii,
        charset_ansi, // cp1252 // ISO-8859-1
        charset_utf8,
        charset_cp1251
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

protected:
    const int cp1251_table[64] = {
      0x0402, 0x0403, 0x201A, 0x0453, 0x201E, 0x2026, 0x2020, 0x2021,
      0x20AC, 0x2030, 0x0409, 0x2039, 0x040A, 0x040C, 0x040B, 0x040F,
      0x0452, 0x2018, 0x2019, 0x201C, 0x201D, 0x2022, 0x2013, 0x2014,
      0x007F, 0x2122, 0x0459, 0x203A, 0x045A, 0x045C, 0x045B, 0x045F,
      0x00A0, 0x040E, 0x045E, 0x0408, 0x00A4, 0x0490, 0x00A6, 0x00A7,
      0x0401, 0x00A9, 0x0404, 0x00AB, 0x00AC, 0x00AD, 0x00AE, 0x0407,
      0x00B0, 0x00B1, 0x0406, 0x0456, 0x0491, 0x00B5, 0x00B6, 0x00B7,
      0x0451, 0x2116, 0x0454, 0x00BB, 0x0458, 0x0405, 0x0455, 0x0457
    };

    inline bool isUnicodeNonCharacter(const uint & ucs4) {
        // Unicode has a couple of "non-characters" that one can use internally,
        // but are not allowed to be used for text interchange.
        //
        // Those are the last two entries each Unicode Plane (U+FFFE, U+FFFF,
        // U+1FFFE, U+1FFFF, etc.) as well as the entries between U+FDD0 and
        // U+FDEF (inclusive)

        return (ucs4 & 0xfffe) == 0xfffe || (ucs4 - 0xfdd0U) < 16;
    }

    static void scanRuChar(QByteArray & val);
    static void scanUtf8Char(QByteArray & val);
};

#endif // HTML_DECODING
