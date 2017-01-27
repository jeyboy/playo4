#ifndef UNICODE_DECODING
#define UNICODE_DECODING

#include <qhash.h>

class QIODevice;

class UnicodeDecoding {
public:
    enum CharsetType {
        charset_unknown,
        charset_utf8,
        charset_cp1251
    };

    static CharsetType toCharsetType(const QString & ch_name);

    static void decodeHtmlEntites(QString & string);
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

    static QHash<QString, QChar> html_entities;

    inline bool isUnicodeNonCharacter(uint ucs4) {
        // Unicode has a couple of "non-characters" that one can use internally,
        // but are not allowed to be used for text interchange.
        //
        // Those are the last two entries each Unicode Plane (U+FFFE, U+FFFF,
        // U+1FFFE, U+1FFFF, etc.) as well as the entries between U+FDD0 and
        // U+FDEF (inclusive)

        return (ucs4 & 0xfffe) == 0xfffe || (ucs4 - 0xfdd0U) < 16;
    }

    void toUtf8(const CharsetType & charset, QIODevice * io, QString & result, char & in);

    void scanRuChar(QIODevice * io, QString & result, char & in);
    void scanUtf8Char(QIODevice * io, QString & result, char & in);
};

#endif // UNICODE_DECODING
