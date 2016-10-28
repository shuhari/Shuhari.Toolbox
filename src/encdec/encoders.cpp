#include "precompiled.h"
#include "encoders.h"


Encoder::~Encoder() {
}


QString Base64Encoder::encode(const QString &input, QTextCodec *codec) {
    auto bytes = codec->fromUnicode(input).toBase64();
    return codec->toUnicode(bytes);
}

QString Base64Encoder::decode(const QString &input, QTextCodec *codec) {
    auto bytes = QByteArray::fromBase64(codec->fromUnicode(input));
    return codec->toUnicode(bytes);
}


QString Md5Encoder::encode(const QString &input, QTextCodec *codec) {
    auto bytes = codec->fromUnicode(input);
    auto hash = QCryptographicHash::hash(bytes, QCryptographicHash::Md5);
    return hash.toHex();
}

QString Md5Encoder::decode(const QString &input, QTextCodec *codec) {
    return "<md5 decode: NO IMPL>";
}


QString UrlEncoder::encode(const QString &input, QTextCodec *codec) {
    return codec->toUnicode(QUrl::toPercentEncoding(input));
}

QString UrlEncoder::decode(const QString &input, QTextCodec *codec) {
    return QUrl::fromPercentEncoding(codec->fromUnicode(input));
}


HtmlEncoder::HtmlEncoder() {
    // Html entity taken from:
    // https://github.com/reillywatson/qthtmlencode/blob/master/HtmlEncodedString.cpp
    registerMap(34, "&quot;");
    registerMap(37, "&percnt;");
    registerMap(38, "&amp;");
    registerMap(39, "&apos;");
    registerMap(60, "&lt;");
    registerMap(62, "&gt;");
    registerMap(160, "&nbsp;");
    registerMap(161, "&iexcl;");
    registerMap(162, "&cent;");
    registerMap(163, "&pound;");
    registerMap(164, "&curren;");
    registerMap(165, "&yen;");
    registerMap(166, "&brvbar;");
    registerMap(167, "&sect;");
    registerMap(168, "&uml;");
    registerMap(169, "&copy;");
    registerMap(170, "&ordf;");
    registerMap(171, "&laquo;");
    registerMap(172, "&not;");
    registerMap(173, "&shy;");
    registerMap(174, "&reg;");
    registerMap(175, "&macr;");
    registerMap(176, "&deg;");
    registerMap(177, "&plusmn;");
    registerMap(178, "&sup2;");
    registerMap(179, "&sup3;");
    registerMap(180, "&acute;");
    registerMap(181, "&micro;");
    registerMap(182, "&para;");
    registerMap(183, "&middot;");
    registerMap(184, "&cedil;");
    registerMap(185, "&sup1;");
    registerMap(186, "&ordm;");
    registerMap(187, "&raquo;");
    registerMap(188, "&frac14;");
    registerMap(189, "&frac12;");
    registerMap(190, "&frac34;");
    registerMap(191, "&iquest;");
    registerMap(192, "&Agrave;");
    registerMap(193, "&Aacute;");
    registerMap(194, "&Acirc;");
    registerMap(195, "&Atilde;");
    registerMap(196, "&Auml;");
    registerMap(197, "&Aring;");
    registerMap(198, "&AElig;");
    registerMap(199, "&Ccedil;");
    registerMap(200, "&Egrave;");
    registerMap(201, "&Eacute;");
    registerMap(202, "&Ecirc;");
    registerMap(203, "&Euml;");
    registerMap(204, "&Igrave;");
    registerMap(205, "&Iacute;");
    registerMap(206, "&Icirc;");
    registerMap(207, "&Iuml;");
    registerMap(208, "&ETH;");
    registerMap(209, "&Ntilde;");
    registerMap(210, "&Ograve;");
    registerMap(211, "&Oacute;");
    registerMap(212, "&Ocirc;");
    registerMap(213, "&Otilde;");
    registerMap(214, "&Ouml;");
    registerMap(215, "&times;");
    registerMap(216, "&Oslash;");
    registerMap(217, "&Ugrave;");
    registerMap(218, "&Uacute;");
    registerMap(219, "&Ucirc;");
    registerMap(220, "&Uuml;");
    registerMap(221, "&Yacute;");
    registerMap(222, "&THORN;");
    registerMap(223, "&szlig;");
    registerMap(224, "&agrave;");
    registerMap(225, "&aacute;");
    registerMap(226, "&acirc;");
    registerMap(227, "&atilde;");
    registerMap(228, "&auml;");
    registerMap(229, "&aring;");
    registerMap(230, "&aelig;");
    registerMap(231, "&ccedil;");
    registerMap(232, "&egrave;");
    registerMap(233, "&eacute;");
    registerMap(234, "&ecirc;");
    registerMap(235, "&euml;");
    registerMap(236, "&igrave;");
    registerMap(237, "&iacute;");
    registerMap(238, "&icirc;");
    registerMap(239, "&iuml;");
    registerMap(240, "&eth;");
    registerMap(241, "&ntilde;");
    registerMap(242, "&ograve;");
    registerMap(243, "&oacute;");
    registerMap(244, "&ocirc;");
    registerMap(245, "&otilde;");
    registerMap(246, "&ouml;");
    registerMap(247, "&divide;");
    registerMap(248, "&oslash;");
    registerMap(249, "&ugrave;");
    registerMap(250, "&uacute;");
    registerMap(251, "&ucirc;");
    registerMap(252, "&uuml;");
    registerMap(253, "&yacute;");
    registerMap(254, "&thorn;");
    registerMap(255, "&yuml;");
    registerMap(338, "&OElig;");
    registerMap(339, "&oelig;");
    registerMap(352, "&Scaron;");
    registerMap(353, "&scaron;");
    registerMap(376, "&Yuml;");
    registerMap(402, "&fnof;");
    registerMap(512, "&zwnj;");
    registerMap(710, "&circ;");
    registerMap(732, "&tilde;");
    registerMap(913, "&Alpha;");
    registerMap(914, "&Beta;");
    registerMap(915, "&Gamma;");
    registerMap(916, "&Delta;");
    registerMap(917, "&Epsilon;");
    registerMap(918, "&Zeta;");
    registerMap(919, "&Eta;");
    registerMap(920, "&Theta;");
    registerMap(921, "&Iota;");
    registerMap(922, "&Kappa;");
    registerMap(923, "&Lambda;");
    registerMap(924, "&Mu;");
    registerMap(925, "&Nu;");
    registerMap(926, "&Xi;");
    registerMap(927, "&Omicron;");
    registerMap(928, "&Pi;");
    registerMap(929, "&Rho;");
    registerMap(931, "&Sigma;");
    registerMap(932, "&Tau;");
    registerMap(933, "&Upsilon;");
    registerMap(934, "&Phi;");
    registerMap(935, "&Chi;");
    registerMap(936, "&Psi;");
    registerMap(937, "&Omega;");
    registerMap(945, "&alpha;");
    registerMap(946, "&beta;");
    registerMap(947, "&gamma;");
    registerMap(948, "&delta;");
    registerMap(949, "&epsilon;");
    registerMap(950, "&zeta;");
    registerMap(951, "&eta;");
    registerMap(952, "&theta;");
    registerMap(953, "&iota;");
    registerMap(954, "&kappa;");
    registerMap(955, "&lambda;");
    registerMap(956, "&mu;");
    registerMap(957, "&nu;");
    registerMap(958, "&xi;");
    registerMap(959, "&omicron;");
    registerMap(960, "&pi;");
    registerMap(961, "&rho;");
    registerMap(962, "&sigmaf;");
    registerMap(963, "&sigma;");
    registerMap(964, "&tau;");
    registerMap(965, "&upsilon;");
    registerMap(966, "&phi;");
    registerMap(967, "&chi;");
    registerMap(968, "&psi;");
    registerMap(969, "&omega;");
    registerMap(977, "&thetasym;");
    registerMap(978, "&upsih;");
    registerMap(982, "&piv;");
    registerMap(8194, "&ensp;");
    registerMap(8195, "&emsp;");
    registerMap(8201, "&thinsp;");
    registerMap(8205, "&zwj;");
    registerMap(8206, "&lrm;");
    registerMap(8207, "&rlm;");
    registerMap(8211, "&ndash;");
    registerMap(8212, "&mdash;");
    registerMap(8216, "&lsquo;");
    registerMap(8217, "&rsquo;");
    registerMap(8218, "&sbquo;");
    registerMap(8220, "&ldquo;");
    registerMap(8221, "&rdquo;");
    registerMap(8222, "&bdquo;");
    registerMap(8224, "&dagger;");
    registerMap(8225, "&Dagger;");
    registerMap(8226, "&bull;");
    registerMap(8230, "&hellip;");
    registerMap(8240, "&permil;");
    registerMap(8242, "&prime;");
    registerMap(8243, "&Prime;");
    registerMap(8249, "&lsaquo;");
    registerMap(8250, "&rsaquo;");
    registerMap(8254, "&oline;");
    registerMap(8260, "&frasl;");
    registerMap(8364, "&euro;");
    registerMap(8465, "&image;");
    registerMap(8472, "&weierp;");
    registerMap(8476, "&real;");
    registerMap(8482, "&trade;");
    registerMap(8501, "&alefsym;");
    registerMap(8592, "&larr;");
    registerMap(8593, "&uarr;");
    registerMap(8594, "&rarr;");
    registerMap(8595, "&darr;");
    registerMap(8596, "&harr;");
    registerMap(8629, "&crarr;");
    registerMap(8656, "&lArr;");
    registerMap(8657, "&uArr;");
    registerMap(8658, "&rArr;");
    registerMap(8659, "&dArr;");
    registerMap(8660, "&hArr;");
    registerMap(8704, "&forall;");
    registerMap(8706, "&part;");
    registerMap(8707, "&exist;");
    registerMap(8709, "&empty;");
    registerMap(8711, "&nabla;");
    registerMap(8712, "&isin;");
    registerMap(8713, "&notin;");
    registerMap(8715, "&ni;");
    registerMap(8719, "&prod;");
    registerMap(8721, "&sum;");
    registerMap(8722, "&minus;");
    registerMap(8727, "&lowast;");
    registerMap(8730, "&radic;");
    registerMap(8733, "&prop;");
    registerMap(8734, "&infin;");
    registerMap(8736, "&ang;");
    registerMap(8745, "&cap;");
    registerMap(8746, "&cup;");
    registerMap(8747, "&int;");
    registerMap(8756, "&there4;");
    registerMap(8764, "&sim;");
    registerMap(8773, "&cong;");
    registerMap(8776, "&asymp;");
    registerMap(8800, "&ne;");
    registerMap(8801, "&equiv;");
    registerMap(8804, "&le;");
    registerMap(8805, "&ge;");
    registerMap(8834, "&sub;");
    registerMap(8835, "&sup;");
    registerMap(8836, "&nsub;");
    registerMap(8838, "&sube;");
    registerMap(8839, "&supe;");
    registerMap(8853, "&oplus;");
    registerMap(8855, "&otimes;");
    registerMap(8869, "&and;");
    registerMap(8869, "&perp;");
    registerMap(8870, "&or;");
    registerMap(8901, "&sdot;");
    registerMap(8968, "&lceil;");
    registerMap(8969, "&rceil;");
    registerMap(8970, "&lfloor;");
    registerMap(8971, "&rfloor;");
    registerMap(9001, "&lang;");
    registerMap(9002, "&rang;");
    registerMap(9674, "&loz;");
    registerMap(9824, "&spades;");
    registerMap(9827, "&clubs;");
    registerMap(9829, "&hearts;");
    registerMap(9830, "&diams;");
}


void HtmlEncoder::registerMap(wchar_t before, const QString &after) {
    QString strBefore = QString::fromWCharArray(&before, 1);
    _encodeMap[strBefore] = after;
    _decodeMap[after] = strBefore;
}


QString HtmlEncoder::encode(const QString &input, QTextCodec *codec) {
    Q_UNUSED(codec);

    QString result = input;
    foreach (QString k, _encodeMap.keys()) {
        auto v = _encodeMap[k];
        result = result.replace(k, v);
    }
    return result;
}


QString HtmlEncoder::decode(const QString &input, QTextCodec *codec) {
    Q_UNUSED(codec);

    QString result = input;
    foreach (QString k, _decodeMap.keys()) {
        auto v = _decodeMap[k];
        QRegExp re(k, Qt::CaseInsensitive);
        result = result.replace(re, v);
    }
    return result;
}

