#include "web_response.h"

#include "web_manager.h"

#include <qtextcodec.h>

using namespace Web;

QHash<QByteArray, Response::ResponseType> Response::response_predefined_types = {
    {QByteArrayLiteral("text/html"), Response::rt_html },
    {QByteArrayLiteral(""), Response::rt_js },
    {QByteArrayLiteral("application/json"), Response::rt_json }
};

Response * Response::fromReply(QNetworkReply * reply) {
    return reinterpret_cast<Response *>(reply);
}

void Response::initInfoFromContentHeader() {
    QByteArray content_type = header(QNetworkRequest::ContentTypeHeader).toByteArray();
    QList<QByteArray> type_parts = content_type.split(';');

    qDebug() << type_parts;

    setProperty(
        RESPONSE_TYPE_PROPERTY,
        response_predefined_types.contains(type_parts[0]) ? response_predefined_types[type_parts[0]] : rt_unknown
    );

    if (type_parts.length() == 1) {
        setProperty(RESPONSE_ENCODING_PROPERTY, DEFAULT_ENCODING);
    } else {
        QList<QByteArray> parts;
        Utils::split(type_parts.last(), QByteArrayLiteral("charset="), parts);

        setProperty(RESPONSE_ENCODING_PROPERTY, parts.length() == 1 ? DEFAULT_ENCODING : parts.last());
    }
}

Response::ResponseType Response::reponseType() {
    int res = property(RESPONSE_TYPE_PROPERTY).toInt();
    if (res == rt_none) {
        initInfoFromContentHeader();
        res = property(RESPONSE_TYPE_PROPERTY).toInt();
    }
    return (ResponseType)res;
}
QByteArray Response::encoding() {
    QByteArray res = property(RESPONSE_ENCODING_PROPERTY).toByteArray();
    if (res.isEmpty()) {
        initInfoFromContentHeader();
        res = property(RESPONSE_ENCODING_PROPERTY).toByteArray();
    }
    return res;
}

//QByteArray Response::encoding() {
//    QByteArray content_type = header(QNetworkRequest::ContentTypeHeader).toByteArray();
//    QList<QByteArray> type_parts = content_type.split(';');

//    qDebug() << type_parts;

////    rtype = response_predefined_types.contains(type_parts[0]) ? response_predefined_types[type_parts[0]] : rt_unknown;

//    if (type_parts.length() == 1) {
//        return DEFAULT_ENCODING;
//    } else {
//        QList<QByteArray> parts;
//        Utils::split(type_parts.last(), QByteArrayLiteral("charset="), parts);

//        if (parts.length() == 1)
//            return DEFAULT_ENCODING;
//        else
//            return parts.last();
//    }
//}

Response * Response::print() {
    qDebug() << "-------------------------";
    qDebug() << "URL:" << toUrl(false);
    qDebug() << "REDIRECT URL:" << toRedirectUrl(false);
    qDebug() << "HEADERS:" << rawHeaderPairs();
    qDebug() << "-------------------------";

    return this;
}

void Response::printHeaders() {
    QList<RawHeaderPair> headers = rawHeaderPairs();

    qDebug() << "------------ HEADERS LIST ----------------";

    for(QList<RawHeaderPair>::ConstIterator it = headers.cbegin(); it != headers.cend(); it++)
        qDebug() << (*it).first << (*it).second;

    qDebug() << "------------ END OF LIST ----------------";
}

QUrl Response::redirectUrl() {
    QVariant possibleRedirectUrl = attribute(QNetworkRequest::RedirectionTargetAttribute);
    if (possibleRedirectUrl.isValid()) {
        QUrl new_url = possibleRedirectUrl.toUrl();

        if (new_url.isRelative())
            new_url = url().resolved(new_url);

        return new_url;

    } else return QUrl();
}

Response * Response::followByRedirect(QHash<QUrl, bool> prev_urls) {
    QUrl new_url = redirectUrl();

    if (!new_url.isEmpty()) {
        if (prev_urls.contains(new_url)) return this;
        else prev_urls.insert(new_url, true);

        RequestParams * params = VariantPtr<RequestParams>::asPtr(
            property(MANAGER_PROPERTY_NAME)
        );

        RequestParams * current_params = RequestParams::buildRedirectParams(
            new_url,
            params,
            new Headers({ {QByteArrayLiteral("Referer"), url().toString().toUtf8() } }) // source -> request().rawHeader("Referer")
        );

        deleteLater();
        return ((Manager *)manager()) -> sendGet(current_params);
    }


    return this;
}

QUrlQuery Response::toQuery(bool destroy) {
    QByteArray ar = readAll();
    if (destroy) deleteLater();
    return QUrlQuery(QUrl::fromPercentEncoding(ar));
}

QByteArray Response::toBytes(bool destroy) {
    QByteArray ar = readAll();
    printHeaders();
    if (destroy) deleteLater();
    return ar;
}

QString Response::toText(bool destroy) {
    QByteArray ar = readAll();
    QByteArray enc = encoding();
    qDebug() << "ENC" << enc;
    QTextCodec * codec = QTextCodec::codecForName(enc);

    if (destroy) deleteLater();

    return codec -> toUnicode(ar);
}
QJsonObject Response::toJson(const QString & wrap, bool destroy) { //TODO: enc not used yet
    QByteArray ar = readAll();

    if (error()) {
        qCritical() << "IOERROR" << error() << url();
        qCritical() << ar;
    }

    QByteArray header = rawHeader("Content-Type");

    if (header.startsWith("application/json") || header.startsWith("application/javascript")) {
//                ar.replace('\'', '"'); // ' wraps responds to errors on parsing // need to replace ' with "
        if (!wrap.isEmpty()) { ar.prepend(QStringLiteral("{\"%1\":").arg(wrap).toUtf8()); ar.append("}"); }
        if (destroy) deleteLater();
        QJsonParseError err;
        QJsonObject ret =  QJsonDocument::fromJson(ar, &err).object();
        if (err.error == QJsonParseError::NoError) return ret;
    }

    qCritical() << "NOT JSON" << rawHeader("Content-Type");
    return QJsonObject {{JSON_ERR_FIELD, QString(ar)}};
}
QPixmap Response::toPixmap(bool destroy) {
    if (error()) qCritical() << "IOERROR" << error() << url();

    QPixmap image;
    image.loadFromData(readAll());
    if (destroy) deleteLater();
    return image;
}

QUrl Response::toUrl(bool destroy) {
    if (error()) qCritical() << "IOERROR" << error() << url();

    QUrl uri = url();
    if (destroy) deleteLater();
    return uri;
}

//Html::Page Response::toHtml(bool destroy) {
//    if (error()) qCritical() << "IOERROR" << error() << url();

//    QByteArray enc = encoding();
//    Html::Page doc(this, Html::Decoding::charsetType(enc));
//    if (destroy) deleteLater();
//    return doc;
//}

QUrl Response::toRedirectUrl(bool destroy) {
    if (error()) qCritical() << "IOERROR" << error() << url();

    QUrl uri = redirectUrl();
    if (destroy) deleteLater();
    return uri;
}

