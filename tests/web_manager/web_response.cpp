#include "web_response.h"

#include "web_manager.h"

#include <qtextcodec.h>

using namespace Web;

Response * Response::fromReply(QNetworkReply * reply) {
    Response * resp = (Response *)reply;
    ((Manager *)reply -> manager()) -> setStatusCode(resp -> status());
    return resp;
}

Response * Response::followByRedirect(QHash<QUrl, bool> prev_urls) {
    QUrl new_url = redirectUrl();
    if (!new_url.isEmpty()) {
        if (prev_urls.contains(new_url)) return this;
        else prev_urls.insert(new_url, true);

        appendHeaders(new_url);
        deleteLater();
        return ((Manager *)manager()) -> requestTo(new_url).viaGet() -> followByRedirect(prev_urls);
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

