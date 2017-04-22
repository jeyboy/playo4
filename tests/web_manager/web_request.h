#ifndef WEB_REQUEST_H
#define WEB_REQUEST_H

#include "web_manager_global.h"

#include "qnetworkrequest.h"

namespace Web {
    class RequestParams;

    class WEBMANAGERSHARED_EXPORT Request : public QNetworkRequest {
    public:
        Request(const RequestParams & params);

        QByteArray headersStr();
    };
}

#endif // WEB_REQUEST_H
