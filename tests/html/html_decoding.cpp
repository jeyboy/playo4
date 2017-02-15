#include "html_decoding.h"
#include <defines.h>

//#include <qregularexpression.h>
#include <qdebug.h>

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

    { QByteArrayLiteral("fnof"), 402 },

//    Греческие
//    Α 	греческая заглавная альфа 	&Alpha; 	&#913;
//    Β 	греческая заглавная бета 	&Beta; 	&#914;
//    Γ 	греческая заглавная гамма 	&Gamma; 	&#915;
//    Δ 	греческая заглавная дельта 	&Delta; 	&#916;
//    Ε 	греческая заглавная эпсилон 	&Epsilon; 	&#917;
//    Ζ 	греческая заглавная дзета 	&Zeta; 	&#918;
//    Η 	греческая заглавная эта 	&Eta; 	&#919;
//    Θ 	греческая заглавная тета 	&Theta; 	&#920;
//    Ι 	греческая заглавная йота 	&Iota; 	&#921;
//    Κ 	греческая заглавная каппа 	&Kappa; 	&#922;
//    Λ 	греческая заглавная лямбда 	&Lambda; 	&#923;
//    Μ 	греческая заглавная мю 	&Mu; 	&#924;
//    Ν 	греческая заглавная ню 	&Nu; 	&#925;
//    Ξ 	греческая заглавная кси 	&Xi; 	&#926;
//    Ο 	греческая заглавная омикрон 	&Omicron; 	&#927;
//    Π 	греческая заглавная пи 	&Pi; 	&#928;
//    Ρ 	греческая заглавная ро 	&Rho; 	&#929;
//    Σ 	греческая заглавная сигма 	&Sigma; 	&#931;
//    Τ 	греческая заглавная тау 	&Tau; 	&#932;
//    Υ 	греческая заглавная ипсилон 	&Upsilon; 	&#933;
//    Φ 	греческая заглавная фи 	&Phi; 	&#934;
//    Χ 	греческая заглавная хи 	&Chi; 	&#935;
//    Ψ 	греческая заглавная пси 	&Psi; 	&#936;
//    Ω 	греческая заглавная омега 	&Omega; 	&#937;
//    α 	греческая строчная альфа 	&alpha; 	&#945;
//    β 	греческая строчная бета 	&beta; 	&#946;
//    γ 	греческая строчная гамма 	&gamma; 	&#947;
//    δ 	греческая строчная дельта 	&delta; 	&#948;
//    ε 	греческая строчная эпсилон 	&epsilon; 	&#949;
//    ζ 	греческая строчная дзета 	&zeta; 	&#950;
//    η 	греческая строчная эта 	&eta; 	&#951;
//    θ 	греческая строчная тета 	&theta; 	&#952;
//    ι 	греческая строчная йота 	&iota; 	&#953;
//    κ 	греческая строчная каппа 	&kappa; 	&#954;
//    λ 	греческая строчная ламбда 	&lambda; 	&#955;
//    μ 	греческая строчная мю 	&mu; 	&#956;
//    ν 	греческая строчная ню 	&nu; 	&#957;
//    ξ 	греческая строчная кси 	&xi; 	&#958;
//    ο 	греческая строчная омикрон 	&omicron; 	&#959;
//    π 	греческая строчная пи 	&pi; 	&#960;
//    ρ 	греческая строчная ро 	&rho; 	&#961;
//    ς 	греческая конечная сигма 	&sigmaf; 	&#962;
//    σ 	греческая строчная сигма 	&sigma; 	&#963;
//    τ 	греческая строчная тау 	&tau; 	&#964;
//    υ 	греческая строчная ипсилон 	&upsilon; 	&#965;
//    φ 	греческая строчная фи 	&phi; 	&#966;
//    χ 	греческая строчная хи 	&chi; 	&#967;
//    ψ 	греческая строчная пси 	&psi; 	&#968;
//    ω 	греческая строчная омега 	&omega; 	&#969;
//    ϑ 	греческая символьная тета 	&thetasym; 	&#977;
//    ϒ 	греческий ипсилон с хвостиком 	&upsih; 	&#978;
//    ϖ 	греческая строчная пи (другой вариант) 	&piv; 	&#982;
//    Основная пунктуация
//    • 	маркер списка (буллит) 	&bull; 	&#8226;
//    … 	горизонтальное многоточие 	&hellip; 	&#8230;
//    ′ 	штрих 	&prime; 	&#8242;
//    ″ 	двойной штрих 	&Prime; 	&#8243;
//    ‾ 	верхняя черта 	&oline; 	&#8254;
//    ⁄ 	косая черта 	&frasl; 	&#8260;
//    Буквоподобные символы
//    ℘ 	рукописная заглавная P = power set = Weierstrass p 	&weierp; 	&#8472;
//    ℑ 	чёрная заглавная I = мнимая часть 	&image; 	&#8465;
//    ℜ 	чёрная заглавная R = вещественная часть 	&real; 	&#8476;
//    ™ 	товарный знак 	&trade; 	&#8482;
//    ℵ 	буква Алеф — кардинальное число 	&alefsym; 	&#8501;
//    Стрелки
//    ← 	влево 	&larr; 	&#8592;
//    ↑ 	вверх 	&uarr; 	&#8593;
//    → 	вправо 	&rarr; 	&#8594;
//    ↓ 	вниз 	&darr; 	&#8595;
//    ◄ 	влево 		&#9668;
//    ▲ 	вверх 		&#9650;
//    ► 	вправо 		&#9658;
//    ▼ 	вниз 		&#9660;
//    ↔ 	влево-вправо 	&harr; 	&#8596;
//    ↵ 	вниз с углом вправо = возврат каретки 	&crarr; 	&#8629;
//    ⇐ 	двойная стрелка влево 	&lArr; 	&#8656;
//    ⇑ 	двойная вверх 	&uArr; 	&#8657;
//    ⇒ 	двойная вправо 	&rArr; 	&#8658;
//    ⇓ 	двойная вниз 	&dArr; 	&#8659;
//    ⇔ 	двойная влево-вправо 	&hArr; 	&#8660;
//    Математические операции
//    [ 	левая квадратная скобка 		&#91;
//    ] 	правая квадратная скобка 		&#93;
//    / 	деление 		&#47;
//    \ 	разность множеств 		&#92;
//    ∀ 	для всех 	&forall; 	&#8704;
//    ∂ 	частичный дифференциал 	&part; 	&#8706;
//    ∃ 	существует 	&exist; 	&#8707;
//    ∅ 	пустое множество 	&empty; 	&#8709;
//    ∇ 	оператор набла = backward difference 	&nabla; 	&#8711;
//    ∈ 	принадлежит 	&isin; 	&#8712;
//    ∉ 	не принадлежит 	&notin; 	&#8713;
//    ∋ 	содержит 	&ni; 	&#8715;
//    ∏ 	знак произведения 	&prod; 	&#8719;
//    ∑ 	знак суммы 	&sum; 	&#8721;
//    − 	минус 	&minus; 	&#8722;
//    ∗ 	оператор звёздочка 	&lowast; 	&#8727;
//    √ 	квадратный корень = знак радикала 	&radic; 	&#8730;
//    ∝ 	пропорционально к 	&prop; 	&#8733;
//    ∞ 	бесконечность 	&infin; 	&#8734;
//    ∠ 	угол 	&ang; 	&#8736;
//    ∧ 	логическое И = wedge 	&and; 	&#8743;
//    ∨ 	логическое ИЛИ = vee 	&or; 	&#8744;
//    ∩ 	пересечение = cap 	&cap; 	&#8745;
//    ∪ 	объединение = cup 	&cup; 	&#8746;
//    ∫ 	интеграл 	&int; 	&#8747;
//    ∴ 	следовательно 	&there4; 	&#8756;
//    ∼ 	оператор тильда = varies with = подобно 	&sim; 	&#8764;
//    ≅ 	конгруэнтно 	&cong; 	&#8773;
//    ≈ 	примерно равно 	&asymp; 	&#8776;
//    ≠ 	не равно 	&ne; 	&#8800;
//    ≡ 	тождественно равно 	&equiv; 	&#8801;
//    ≤ 	меньше или равно 	&le; 	&#8804;
//    ≥ 	больше или равно 	&ge; 	&#8805;
//    ⊂ 	подмножество 	&sub; 	&#8834;
//    ⊃ 	включает в себя 	&sup; 	&#8835;
//    ⊄ 	не включает в себя 	&nsub; 	&#8836;
//    ⊆ 	подмножество или эквивалентно 	&sube; 	&#8838;
//    ⊇ 	включает в себя или эквивалентно 	&supe; 	&#8839;
//    ⊕ 	плюс в круге = прямая сумма 	&oplus; 	&#8853;
//    ⊗ 	умножение в круге = тензорное произведение 	&otimes; 	&#8855;
//    ⊥ 	up tack = ортогонально к = перпендикулярно 	&perp; 	&#8869;
//    ⋅ 	оператор точка 	&sdot; 	&#8901;
//    Различные технические
//    ⌈ 	левая скобка округления вверх = apl upstile 	&lceil; 	&#8968;
//    ⌉ 	правая скобка округления вверх 	&rceil; 	&#8969;
//    ⌊ 	левая скобка округления вниз = apl downstile 	&lfloor; 	&#8970;
//    ⌋ 	правая скобка округления вниз 	&rfloor; 	&#8971;
//    〈 	угловая скобка влево = бра 	&lang; 	&#9001;
//    〉 	угловая скобка вправо = кет 	&rang; 	&#9002;
//    Геометрические Фигуры
//    ◊ 	ромб 	&loz; 	&#9674;
//    Различные символы
//    ♠ 	«пики» (картёжные) 	&spades; 	&#9824;
//    ♣ 	«трефы» 	&clubs; 	&#9827;
//    ♥ 	«червы» 	&hearts; 	&#9829;
//    ♦ 	«бубны» 	&diams; 	&#9830;
//    Latin Extended-A
//    Œ 	латинская заглавная лигатура OE 	&OElig; 	&#338;
//    œ 	латинская лигатура oe 	&oelig; 	&#339;
//    Š 	латинская заглавная S с птичкой 	&Scaron; 	&#352;
//    š 	латинская s с птичкой 	&scaron; 	&#353;
//    Ÿ 	латинская заглавная Y с двоеточием 	&Yuml; 	&#376;
//    Модификаторы букв
//    ˆ 	акцент перевёрнутая птичка/circumflex accent 	&circ; 	&#710;
//    ˜ 	малая тильда 	&tilde; 	&#732;
//    Общая пунктуация
//        пробел длины N 	&ensp; 	&#8194;
//        пробел длины M 	&emsp; 	&#8195;
//        узкий пробел 	&thinsp; 	&#8201;
//    ‌ 	zero width non-joiner 	&zwnj; 	&#8204;
//    ‍ 	zero width joiner 	&zwj; 	&#8205;
//    ‎ 	left-to-right mark 	&lrm; 	&#8206;
//    ‏ 	right-to-left mark 	&rlm; 	&#8207;
//    ‑ 	неразрывный (неразделяемый) дефис / non-breaking hyphen 	  	&#8209;
//    – 	тире длины N 	&ndash; 	&#8211;
//    — 	тире длины M 	&mdash; 	&#8212;
//    ‘ 	одиночная левая кавычка 	&lsquo; 	&#8216;
//    ’ 	одиночная правая кавычка 	&rsquo; 	&#8217;
//    ‚ 	одиночная low-9/нижняя кавычка 	&sbquo; 	&#8218;
//    “ 	двойная левая кавычка 	&ldquo; 	&#8220;
//    ” 	двойная правая кавычка 	&rdquo; 	&#8221;
//    „ 	двойная low-9/нижняя кавычка 	&bdquo; 	&#8222;
//    † 	крест/dagger 	&dagger; 	&#8224;
//    ‡ 	двойной dagger 	&Dagger; 	&#8225;
//    ‰ 	промилле 	&permil; 	&#8240;
//    ‹ 	одиночная левая угловая скобка (предложена, но ещё не стандартизирована ISO) 	&lsaquo; 	&#8249;
//    › 	одиночная правая угловая скобка (предложена, но ещё не стандартизирована ISO) 	&rsaquo; 	&#8250;
//    € 	евро 	&euro; 	&#8364;
};

HtmlDecoding::CharsetType HtmlDecoding::charsetType(const QString & ch_name) {
    QString l_name = ch_name.toLower();

    if (l_name == QStringLiteral("utf-8"))
        return charset_utf8;
    else if (l_name == QStringLiteral("windows-1251"))
        return charset_cp1251;

    return charset_unknown;
}

void HtmlDecoding::decodeMnemonics(QByteArray & val) {
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
