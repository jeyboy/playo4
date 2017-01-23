#include "unicode_decoding.h"

#include <qregularexpression.h>
#include <qiodevice.h>
#include <qdebug.h>

QHash<QString, QChar> UnicodeDecoding::html_entities = {
    { QStringLiteral("nbsp"), ' ' },
    { QStringLiteral("amp"), '&' },
    { QStringLiteral("lt"), '<' },
    { QStringLiteral("gt"), '>' },
    { QStringLiteral("quot"), '"' }
};

void UnicodeDecoding::toUtf8(const CharsetType & charset, QIODevice * io, QString & result, char & in) {
    switch(charset) {
        case charset_utf8: { scanUtf8Char(io, result, in); break;}
        case charset_cp1251: { scanRuChar(io, result, in); break;}
        default: result.append(in);
    }
}

void UnicodeDecoding::scanRuChar(QIODevice * /*io*/, QString & result, char & in) {
    int uc = in < 0 ? in + 256 : in;

    if (uc < 192)
        uc = cp1251_table[uc - 128];
    else
        uc = uc + 848;

    result.append(QChar(uc));
}

void UnicodeDecoding::scanUtf8Char(QIODevice * io, QString & result, char & in) {
    int need;
    uint min_uc, uc;

    if ((in & 0xe0) == 0xc0) {
        uc = in & 0x1f;
        need = 1;
        min_uc = 0x80;
    } else if ((in & 0xf0) == 0xe0) {
        uc = in & 0x0f;
        need = 2;
        min_uc = 0x800;
    } else if ((in&0xf8) == 0xf0) {
        uc = in & 0x07;
        need = 3;
        min_uc = 0x10000;
    } else {
        qDebug() << "BLIA " << in;
        result.append(in);
        return;
    }

//        if (io -> bytesAvailable() < need) { result.append(ch); return;}

    for (int i = 0; i < need; ++i) {
        io -> getChar(&in);
        if ((in & 0xc0) != 0x80) { qDebug() << "PIPEC" << in; return; }
        uc = (uc << 6) | (in & 0x3f);
    }

    if (isUnicodeNonCharacter(uc) || uc >= 0x110000 || (uc < min_uc) || (uc >= 0xd800 && uc <= 0xdfff)) {
        qDebug() << "UNEBABLE"; return;
    }

    if (QChar::requiresSurrogates(uc)) {
        result.append(QChar::highSurrogate(uc));
        result.append(QChar::lowSurrogate(uc));
    }
    else result.append(QChar(uc));
}

//    void UnicodeDecoding::scanUtf8Char(char * io, QString & result) { // not worked
//        int need;
//        uint min_uc, uc;

//        if (((*io) & 0xe0) == 0xc0) {
//            uc = (*io) & 0x1f;
//            need = 1;
//            min_uc = 0x80;
//        } else if (((*io) & 0xf0) == 0xe0) {
//            uc = (*io) & 0x0f;
//            need = 2;
//            min_uc = 0x800;
//        } else if (((*io)&0xf8) == 0xf0) {
//            uc = (*io) & 0x07;
//            need = 3;
//            min_uc = 0x10000;
//        } else {
//            qDebug() << "BLIA " << (*io);
//            result.append((*io));
//            return;
//        }

////        if (io -> bytesAvailable() < need) { result.append(ch); return;}

//        for (int i = 0; i < need; ++i, io++) {
//            if (((*io)&0xc0) != 0x80) { qDebug() << "PIPEC" << (*io); return; }
//            uc = (uc << 6) | ((*io) & 0x3f);
//        }

//        if (isUnicodeNonCharacter(uc) || uc >= 0x110000 || (uc < min_uc) || (uc >= 0xd800 && uc <= 0xdfff)) {
//            qDebug() << "UNEBABLE"; return;
//        }

//        if (QChar::requiresSurrogates(uc)) { result.append(QChar::highSurrogate(uc)); result.append(QChar::lowSurrogate(uc)); }
//        else result.append(QChar(uc));
//    }

CharsetType UnicodeDecoding::toCharsetType(const QString & ch_name) {
    QString l_name = ch_name.toLower();

    if (l_name == QStringLiteral("utf-8"))
        return charset_utf8;
    else if (l_name == QStringLiteral("windows-1251"))
        return charset_cp1251;

    return charset_unknown;
}

QString UnicodeDecoding::decodeHtmlEntites(const QString & string) {
    QRegularExpression reg("&([#\\w]+);");
    QRegularExpressionMatch match;
    int index = 0;

    while(true) {
        index = string.indexOf(reg, index, &match);
        if (index == -1) break;

        int sel_start = match.capturedStart(1);
        int sel_length = match.capturedLength(1);

        QString entity = string.mid(sel_start, sel_length);
        QChar res;

        if (entity.startsWith('#'))
            res = QChar(entity.mid(1).toInt());
        else {
            if (!html_entities.contains(entity)) {
                res = ' ';
                qDebug() << "HTML ENTITY NOT EXISTS" << entity;
            } else
                res = html_entities[entity];
        }

        string.replace(match.capturedStart(0), match.capturedLength(0), res);
    }

    return string;
}
