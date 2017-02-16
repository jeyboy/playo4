#include "html_decoding.h"
#include <defines.h>

//#include <qregularexpression.h>
#include <qdebug.h>

// &forall; &#9830; &#x2666;

QHash<QByteArray, int> HtmlDecoding::html_entities = {
    { QByteArrayLiteral("quot"), 34 },
    { QByteArrayLiteral("amp"), 38 },
    { QByteArrayLiteral("apos"), 39 },
    { QByteArrayLiteral("lt"), 60 },
    { QByteArrayLiteral("gt"), 62 },

    { QByteArrayLiteral("nbsp"), 32 }, // 160
    { QByteArrayLiteral("iexcl"), 161 },
    { QByteArrayLiteral("cent"), 162 },
    { QByteArrayLiteral("pound"), 163 },
    { QByteArrayLiteral("curren"), 164 },
    { QByteArrayLiteral("yen"), 165 },
    { QByteArrayLiteral("brvbar"), 166 },
    { QByteArrayLiteral("sect"), 167 },
    { QByteArrayLiteral("uml"), 168 },
    { QByteArrayLiteral("copy"), 169 },
    { QByteArrayLiteral("ordf"), 170 },
    { QByteArrayLiteral("laquo"), 171 },
    { QByteArrayLiteral("not"), 172 },
    { QByteArrayLiteral("shy"), 173 },
    { QByteArrayLiteral("reg"), 174 },
    { QByteArrayLiteral("macr"), 175 },
    { QByteArrayLiteral("deg"), 176 },
    { QByteArrayLiteral("plusmn"), 177 },
    { QByteArrayLiteral("sup2"), 178 },
    { QByteArrayLiteral("sup3"), 179 },
    { QByteArrayLiteral("acute"), 180 },
    { QByteArrayLiteral("micro"), 181 },
    { QByteArrayLiteral("para"), 182 },
    { QByteArrayLiteral("middot"), 183 },
    { QByteArrayLiteral("cedil"), 184 },
    { QByteArrayLiteral("sup1"), 185 },
    { QByteArrayLiteral("ordm"), 186 },
    { QByteArrayLiteral("raquo"), 187 },
    { QByteArrayLiteral("frac14"), 188 },
    { QByteArrayLiteral("frac12"), 189 },
    { QByteArrayLiteral("frac34"), 190 },
    { QByteArrayLiteral("iquest"), 191 },
    { QByteArrayLiteral("Agrave"), 192 },
    { QByteArrayLiteral("Aacute"), 193 },
    { QByteArrayLiteral("Acirc"), 194 },
    { QByteArrayLiteral("Atilde"), 195 },
    { QByteArrayLiteral("Auml"), 196 },
    { QByteArrayLiteral("Aring"), 197 },
    { QByteArrayLiteral("AElig"), 198 },
    { QByteArrayLiteral("Ccedil"), 199 },
    { QByteArrayLiteral("Egrave"), 200 },
    { QByteArrayLiteral("Eacute"), 201 },
    { QByteArrayLiteral("Ecirc"), 202 },
    { QByteArrayLiteral("Euml"), 203 },
    { QByteArrayLiteral("Igrave"), 204 },
    { QByteArrayLiteral("Iacute"), 205 },
    { QByteArrayLiteral("Icirc"), 206 },
    { QByteArrayLiteral("Iuml"), 207 },
    { QByteArrayLiteral("ETH"), 208 },
    { QByteArrayLiteral("Ntilde"), 209 },
    { QByteArrayLiteral("Ograve"), 210 },
    { QByteArrayLiteral("Oacute"), 211 },
    { QByteArrayLiteral("Ocirc"), 212 },
    { QByteArrayLiteral("Otilde"), 213 },
    { QByteArrayLiteral("Ouml"), 214 },
    { QByteArrayLiteral("times"), 215 },
    { QByteArrayLiteral("Oslash"), 216 },
    { QByteArrayLiteral("Ugrave"), 217 },
    { QByteArrayLiteral("Uacute"), 218 },
    { QByteArrayLiteral("Ucirc"), 219 },
    { QByteArrayLiteral("Uuml"), 220 },
    { QByteArrayLiteral("Yacute"), 221 },
    { QByteArrayLiteral("THORN"), 222 },
    { QByteArrayLiteral("szlig"), 223 },
    { QByteArrayLiteral("agrave"), 224 },
    { QByteArrayLiteral("aacute"), 225 },
    { QByteArrayLiteral("acirc"), 226 },
    { QByteArrayLiteral("atilde"), 227 },
    { QByteArrayLiteral("auml"), 228 },
    { QByteArrayLiteral("aring"), 229 },
    { QByteArrayLiteral("aelig"), 230 },
    { QByteArrayLiteral("ccedil"), 231 },
    { QByteArrayLiteral("egrave"), 232 },
    { QByteArrayLiteral("eacute"), 233 },
    { QByteArrayLiteral("ecirc"), 234 },
    { QByteArrayLiteral("euml"), 235 },
    { QByteArrayLiteral("igrave"), 236 },
    { QByteArrayLiteral("iacute"), 237 },
    { QByteArrayLiteral("icirc"), 238 },
    { QByteArrayLiteral("iuml"), 239 },
    { QByteArrayLiteral("eth"), 240 },
    { QByteArrayLiteral("ntilde"), 241 },
    { QByteArrayLiteral("ograve"), 242 },
    { QByteArrayLiteral("oacute"), 243 },
    { QByteArrayLiteral("ocirc"), 244 },
    { QByteArrayLiteral("otilde"), 245 },
    { QByteArrayLiteral("ouml"), 246 },
    { QByteArrayLiteral("divide"), 247 },
    { QByteArrayLiteral("oslash"), 248 },
    { QByteArrayLiteral("ugrave"), 249 },
    { QByteArrayLiteral("uacute"), 250 },
    { QByteArrayLiteral("ucirc"), 251 },
    { QByteArrayLiteral("uuml"), 252 },
    { QByteArrayLiteral("yacute"), 253 },
    { QByteArrayLiteral("thorn"), 254 },
    { QByteArrayLiteral("yuml"), 255 },

    { QByteArrayLiteral("OElig"), 338 },
    { QByteArrayLiteral("oelig"), 339 },

    { QByteArrayLiteral("Scaron"), 352 },
    { QByteArrayLiteral("scaron"), 353 },

    { QByteArrayLiteral("Yuml"), 376 },

    { QByteArrayLiteral("fnof"), 402 },

    { QByteArrayLiteral("circ"), 710 },
    { QByteArrayLiteral("tilde"), 732 },

    { QByteArrayLiteral("Alpha"), 913 },
    { QByteArrayLiteral("Beta"), 914 },
    { QByteArrayLiteral("Gamma"), 915 },
    { QByteArrayLiteral("Delta"), 916 },
    { QByteArrayLiteral("Epsilon"), 917 },
    { QByteArrayLiteral("Zeta"), 918 },
    { QByteArrayLiteral("Eta"), 919 },
    { QByteArrayLiteral("Theta"), 920 },
    { QByteArrayLiteral("Iota"), 921 },
    { QByteArrayLiteral("Kappa"), 922 },
    { QByteArrayLiteral("Lambda"), 923 },
    { QByteArrayLiteral("Mu"), 924 },
    { QByteArrayLiteral("Nu"), 925 },
    { QByteArrayLiteral("Xi"), 926 },
    { QByteArrayLiteral("Omicron"), 927 },
    { QByteArrayLiteral("Pi"), 928 },
    { QByteArrayLiteral("Rho"), 929 },

    { QByteArrayLiteral("Sigma"), 931 },
    { QByteArrayLiteral("Tau"), 932 },
    { QByteArrayLiteral("Upsilon"), 933 },
    { QByteArrayLiteral("Phi"), 934 },
    { QByteArrayLiteral("Chi"), 935 },
    { QByteArrayLiteral("Psi"), 936 },
    { QByteArrayLiteral("Omega"), 937 },

    { QByteArrayLiteral("alpha"), 945 },
    { QByteArrayLiteral("beta"), 946 },
    { QByteArrayLiteral("gamma"), 947 },
    { QByteArrayLiteral("delta"), 948 },
    { QByteArrayLiteral("epsilon"), 949 },
    { QByteArrayLiteral("zeta"), 950 },
    { QByteArrayLiteral("eta"), 951 },
    { QByteArrayLiteral("theta"), 952 },
    { QByteArrayLiteral("iota"), 953 },
    { QByteArrayLiteral("kappa"), 954 },
    { QByteArrayLiteral("lambda"), 955 },
    { QByteArrayLiteral("mu"), 956 },
    { QByteArrayLiteral("nu"), 957 },
    { QByteArrayLiteral("xi"), 958 },
    { QByteArrayLiteral("omicron"), 959 },
    { QByteArrayLiteral("pi"), 960 },
    { QByteArrayLiteral("rho"), 961 },
    { QByteArrayLiteral("sigmaf"), 962 },
    { QByteArrayLiteral("sigma"), 963 },
    { QByteArrayLiteral("tau"), 964 },
    { QByteArrayLiteral("upsilon"), 965 },
    { QByteArrayLiteral("phi"), 966 },
    { QByteArrayLiteral("chi"), 967 },
    { QByteArrayLiteral("psi"), 968 },
    { QByteArrayLiteral("omega"), 969 },

    { QByteArrayLiteral("thetasym"), 977 },
    { QByteArrayLiteral("upsih"), 978 },

    { QByteArrayLiteral("piv"), 982 },

    { QByteArrayLiteral("ensp"), 8194 },
    { QByteArrayLiteral("emsp"), 8195 },
    { QByteArrayLiteral("thinsp"), 8201 },
    { QByteArrayLiteral("zwnj"), 8204 },
    { QByteArrayLiteral("zwj"), 8205 },
    { QByteArrayLiteral("lrm"), 8206 },
    { QByteArrayLiteral("rlm"), 8207 },

    { QByteArrayLiteral("ndash"), 8211 },
    { QByteArrayLiteral("mdash"), 8212 },
    { QByteArrayLiteral("lsquo"), 8216 },
    { QByteArrayLiteral("rsquo"), 8217 },
    { QByteArrayLiteral("sbquo"), 8218 },
    { QByteArrayLiteral("ldquo"), 8220 },
    { QByteArrayLiteral("rdquo"), 8221 },
    { QByteArrayLiteral("bdquo"), 8222 },
    { QByteArrayLiteral("dagger"), 8224 },
    { QByteArrayLiteral("Dagger"), 8225 },
    { QByteArrayLiteral("bull"), 8226 },
    { QByteArrayLiteral("hellip"), 8230 },
    { QByteArrayLiteral("permil"), 8240 },
    { QByteArrayLiteral("prime"), 8242 },
    { QByteArrayLiteral("Prime"), 8243 },
    { QByteArrayLiteral("lsaquo"), 8249 },
    { QByteArrayLiteral("rsaquo"), 8250 },
    { QByteArrayLiteral("oline"), 8254 },
    { QByteArrayLiteral("frasl"), 8260 },
    { QByteArrayLiteral("euro"), 8364 },


    { QByteArrayLiteral("image"), 8465 },
    { QByteArrayLiteral("weierp"), 8472 },
    { QByteArrayLiteral("real"), 8476 },
    { QByteArrayLiteral("trade"), 8482 },
    { QByteArrayLiteral("alefsym"), 8501 },

    { QByteArrayLiteral("larr"), 8592 },
    { QByteArrayLiteral("uarr"), 8593 },
    { QByteArrayLiteral("rarr"), 8594 },
    { QByteArrayLiteral("darr"), 8595 },

    { QByteArrayLiteral("harr"), 8596 },
    { QByteArrayLiteral("crarr"), 8629 },
    { QByteArrayLiteral("lArr"), 8656 },
    { QByteArrayLiteral("uArr"), 8657 },
    { QByteArrayLiteral("rArr"), 8658 },
    { QByteArrayLiteral("dArr"), 8659 },
    { QByteArrayLiteral("hArr"), 8660 },

    { QByteArrayLiteral("forall"), 8704 },
    { QByteArrayLiteral("part"), 8706 },
    { QByteArrayLiteral("exist"), 8707 },
    { QByteArrayLiteral("empty"), 8709 },
    { QByteArrayLiteral("nabla"), 8711 },
    { QByteArrayLiteral("isin"), 8712 },
    { QByteArrayLiteral("notin"), 8713 },
    { QByteArrayLiteral("ni"), 8715 },
    { QByteArrayLiteral("prod"), 8719 },
    { QByteArrayLiteral("sum"), 8721 },
    { QByteArrayLiteral("minus"), 8722 },
    { QByteArrayLiteral("lowast"), 8727 },
    { QByteArrayLiteral("radic"), 8730 },
    { QByteArrayLiteral("prop"), 8733 },
    { QByteArrayLiteral("infin"), 8734 },
    { QByteArrayLiteral("ang"), 8736 },
    { QByteArrayLiteral("and"), 8743 },
    { QByteArrayLiteral("or"), 8744 },
    { QByteArrayLiteral("cap"), 8745 },
    { QByteArrayLiteral("cup"), 8746 },
    { QByteArrayLiteral("int"), 8747 },
    { QByteArrayLiteral("there4"), 8756 },
    { QByteArrayLiteral("sim"), 8764 },
    { QByteArrayLiteral("cong"), 8773 },
    { QByteArrayLiteral("asymp"), 8776 },
    { QByteArrayLiteral("ne"), 8800 },
    { QByteArrayLiteral("equiv"), 8801 },
    { QByteArrayLiteral("le"), 8804 },
    { QByteArrayLiteral("ge"), 8805 },
    { QByteArrayLiteral("sub"), 8834 },
    { QByteArrayLiteral("sup"), 8835 },
    { QByteArrayLiteral("nsub"), 8836 },
    { QByteArrayLiteral("sube"), 8838 },
    { QByteArrayLiteral("supe"), 8839 },
    { QByteArrayLiteral("oplus"), 8853 },
    { QByteArrayLiteral("otimes"), 8855 },
    { QByteArrayLiteral("perp"), 8869 },
    { QByteArrayLiteral("sdot"), 8901 },

    { QByteArrayLiteral("lceil"), 8968 },
    { QByteArrayLiteral("rceil"), 8969 },
    { QByteArrayLiteral("lfloor"), 8970 },
    { QByteArrayLiteral("rfloor"), 8971 },
    { QByteArrayLiteral("lang"), 9001 },
    { QByteArrayLiteral("rang"), 9002 },

    { QByteArrayLiteral("loz"), 9674 },

    { QByteArrayLiteral("spades"), 9824 },
    { QByteArrayLiteral("clubs"), 9827 },
    { QByteArrayLiteral("hearts"), 9829 },
    { QByteArrayLiteral("diams"), 9830 }
};

HtmlDecoding::CharsetType HtmlDecoding::charsetType(const QByteArray & val) {
    QByteArray l_name = val.toLower();

    if (l_name == QByteArrayLiteral("utf-8"))
        return charset_utf8;
    else if (l_name == QByteArrayLiteral("windows-1251"))
        return charset_cp1251;

    return charset_unknown;
}

QByteArray & HtmlDecoding::decodeMnemonics(QByteArray & val) {
//    QRegularExpression reg("&([#\\w]+);");
//    QRegularExpressionMatch match;
//    int index = 0;

//    while(true) {
//        index = string.indexOf(reg, index, &match);
//        if (index == -1) break;

//        int sel_start = match.capturedStart(1);
//        int sel_length = match.capturedLength(1);

//        QString entity = string.mid(sel_start, sel_length);
//        QChar res;

//        if (entity.startsWith('#'))
//            res = QChar(entity.mid(1).toInt());
//        else {
//            if (!html_entities.contains(entity)) {
//                res = ' ';
//                qDebug() << "HTML ENTITY NOT EXISTS" << entity;
//            } else
//                res = html_entities[entity];
//        }

//        string.replace(match.capturedStart(0), match.capturedLength(0), res);
//    }
}

QByteArray & HtmlDecoding::decodeContent(const CharsetType & charset, QByteArray & val) {
    switch(charset) {
        case charset_utf8: { scanUtf8Char(val/*io, result, in*/); break;}
        case charset_cp1251: { scanRuChar(val/*io, result, in*/); break;}
        default:;
    }

    return val;
}

QByteArray & HtmlDecoding::decodeUrl(QByteArray & url, QByteArray * base_url) {
    ////            Relative URI	Absolute URI
    ////            about.html	http://WebReference.com/html/about.html
    ////            tutorial1/	http://WebReference.com/html/tutorial1/
    ////            tutorial1/2.html	http://WebReference.com/html/tutorial1/2.html
    ////            /	http://WebReference.com/
    ////            //www.internet.com/	http://www.internet.com/
    ////            /experts/	http://WebReference.com/experts/
    ////            ../	http://WebReference.com/
    ////            ../experts/	http://WebReference.com/experts/
    ////            ../../../	http://WebReference.com/
    ////            ./	http://WebReference.com/html/
    ////            ./about.html	http://WebReference.com/html/about.html
}


void HtmlDecoding::scanRuChar(QByteArray & val) {
//    int uc = in < 0 ? in + 256 : in;

//    if (uc < 192)
//        uc = cp1251_table[uc - 128];
//    else
//        uc = uc + 848;

//    result.append(QChar(uc));
}

void HtmlDecoding::scanUtf8Char(QByteArray & val/*QIODevice * io, QString & result, char & in*/) {
//    int need;
//    uint min_uc, uc;

//    if ((in & 0xe0) == 0xc0) {
//        uc = in & 0x1f;
//        need = 1;
//        min_uc = 0x80;
//    } else if ((in & 0xf0) == 0xe0) {
//        uc = in & 0x0f;
//        need = 2;
//        min_uc = 0x800;
//    } else if ((in&0xf8) == 0xf0) {
//        uc = in & 0x07;
//        need = 3;
//        min_uc = 0x10000;
//    } else {
//        qDebug() << "BLIA " << in;
//        result.append(in);
//        return;
//    }

////        if (io -> bytesAvailable() < need) { result.append(ch); return;}

//    for (int i = 0; i < need; ++i) {
//        io -> getChar(&in);
//        if ((in & 0xc0) != 0x80) { qDebug() << "PIPEC" << in; return; }
//        uc = (uc << 6) | (in & 0x3f);
//    }

//    if (isUnicodeNonCharacter(uc) || uc >= 0x110000 || (uc < min_uc) || (uc >= 0xd800 && uc <= 0xdfff)) {
//        qDebug() << "UNEBABLE"; return;
//    }

//    if (QChar::requiresSurrogates(uc)) {
//        result.append(QChar::highSurrogate(uc));
//        result.append(QChar::lowSurrogate(uc));
//    }
//    else result.append(QChar(uc));
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
