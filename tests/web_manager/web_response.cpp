#include "web_response.h"

#include "web_manager.h"

#include <qtextcodec.h>

using namespace Web;

Response * Response::fromReply(QNetworkReply * reply) {
    return dynamic_cast<Response *>(reply);
}

QByteArray Response::encoding() {
    QByteArray content_type = header(QNetworkRequest::ContentTypeHeader).toByteArray();
    QList<QByteArray> parts;
    Utils::split(content_type, QByteArrayLiteral("charset="), parts);

    if (parts.length() == 1)
        return QByteArrayLiteral("utf-8");
    else
        return parts.last();
}

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

//        appendHeaders(new_url);

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

Html::Page Response::toHtml(bool destroy) {
    if (error()) qCritical() << "IOERROR" << error() << url();

    QByteArray enc = encoding();
    Html::Page doc(this, Html::Decoding::charsetType(enc));
    if (destroy) deleteLater();
    return doc;
}

QUrl Response::toRedirectUrl(bool destroy) {
    if (error()) qCritical() << "IOERROR" << error() << url();

    QUrl uri = redirectUrl();
    if (destroy) deleteLater();
    return uri;
}

