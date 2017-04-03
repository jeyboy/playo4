#include "web_request.h"

#include "web_headers.h"

using namespace Web;

Request Request::withHeaders(const Headers & headers) {
    for(Headers::ConstIterator header = headers.cbegin(); header != headers.cend(); header++)
        setRawHeader(header.key().toUtf8(), header.value().toUtf8());

    // in some cases referer broke the link - od is one of it
//            if (!headers.contains(QStringLiteral("Referer")))
//                setRawHeader("Referer", url().path().toUtf8());

    if (!headers.contains(USER_AGENT_HEADER_NAME))
        setRawHeader(USER_AGENT_HEADER_NAME.toUtf8(), DEFAULT_AGENT.toUtf8());

    return *this;
}

Response * Request::viaGet(bool async) { return manager -> get(*this, async); }

Response * Request::viaPost(const QByteArray & data, const QString & content_type, bool async) {
    QByteArray payload = data;

    if (payload.isEmpty()) {
        QUrl curl = url();
        payload = manager -> isExtractParamsToPayload() ? extractParams(curl) : QByteArray();
        setUrl(curl);
    }

    //            QUrl curl = url();
    //            QByteArray payload = manager -> isExtractParamsToPayload() ? extractParams(curl) : QByteArray();
    //            setUrl(curl);

    //            if (!data.isEmpty()) {
    //                if (!payload.isEmpty()) {
    //                    payload = payload + '&' + data;
    //                } else payload = data;
    //            }

    setHeader(QNetworkRequest::ContentTypeHeader, content_type);
    return manager -> post(*this, payload, async);
}

Response * Request::viaPut(const QByteArray & data, const QString & content_type, bool async) {
    QByteArray payload = data;

    if (payload.isEmpty()) {
        QUrl curl = url();
        payload = manager -> isExtractParamsToPayload() ? extractParams(curl) : QByteArray();
        setUrl(curl);
    }

    setHeader(QNetworkRequest::ContentTypeHeader, content_type);
    return manager -> put(*this, payload, async);
}

Response * Request::viaForm(const QByteArray & data, bool async) { return viaPost(data, FORM_URLENCODE, async); }

