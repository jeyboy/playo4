#ifndef WEB_REQUEST_PARAMS_H
#define WEB_REQUEST_PARAMS_H

#include <qurl.h>

#include "func.h"

#include "web_manager_global.h"
#include "web_headers.h"
#include "web_cookies.h"
#include "web_utils.h"

//#define USER_AGENT_HEADER_NAME QByteArrayLiteral("User-Agent")
#define FORM_URLENCODE QByteArrayLiteral("application/x-www-form-urlencoded")
#ifdef Q_OS_WIN
    #define DEFAULT_AGENT QByteArrayLiteral("Mozilla/5.0 (Windows NT 6.1; WOW64; rv:48.0) Gecko/20100101 Firefox/48.0")
#elif Q_OS_MAC // there should be agent for mac
    #define DEFAULT_AGENT QByteArrayLiteral("Mozilla/5.0 (X11; Ubuntu; Linux i686; rv:43.0) Gecko/20100101 Firefox/50.0")
#else
    #define DEFAULT_AGENT QByteArrayLiteral("Mozilla/5.0 (X11; Ubuntu; Linux i686; rv:43.0) Gecko/20100101 Firefox/50.0")
#endif

#define DEFAULT_REQUEST_PARAMS RequestParams::rp_extract_params_to_payload

namespace Web {
    struct WEBMANAGERSHARED_EXPORT RequestParams {
        enum RequestParamsFlags {
            rp_none = 0,
            rp_follow,
            rp_async,
            rp_attach_agent,
            rp_extract_params_to_payload,
            rp_print_params,
            rp_has_payload
        };

        QUrl url;
        RequestParamsFlags rparams;
        Headers * headers;
        Cookies * cookies;
        Func * callback;

        RequestParams(const QUrl & url, const RequestParamsFlags & rparams = rp_none,
            Headers * headers = 0, Func * callback = 0, Cookies * cookies = 0) : url(url),
                 rparams(rparams), headers(headers), cookies(cookies), callback(callback) { prepare(); }

        inline bool isAsync() { return rparams & rp_async; }
        inline bool isExtractParams() { return rparams & rp_extract_params_to_payload; }
        inline bool isPrintParams() { return rparams & rp_print_params; }
        inline bool isHasPayload() { return rparams & rp_has_payload; }
        inline bool isFollowed() { return rparams & rp_follow; }
        inline bool isHasCallback() { return callback != 0; }

        void prepare() {
            if (rparams & rp_attach_agent) {
                if (!headers)
                    headers = new Headers();

                headers -> insert(QByteArrayLiteral("User-Agent"), DEFAULT_AGENT);
            }

            if (isAsync() && !callback) {
                qWarning() << "Called async request without callback:" << url;
            }
        }

        void erase() {
            delete callback;
            delete headers;
        }

        //TODO: add current url as referrer
        void prepareForRedirect(const QUrl & new_url) {

        }

        void addHeader(const QByteArray & name, const QByteArray & val) {
            if (!headers) headers = new Headers();

            headers -> insert(name, val);
        }
    };

    struct WEBMANAGERSHARED_EXPORT RequestDataParams : public RequestParams {
        QByteArray data;

//        static RequestDataParams & fromParams(RequestParams & params) { return dynamic_cast<RequestDataParams &>(params); }

        RequestDataParams(const QUrl & url, const RequestParamsFlags & rparams = DEFAULT_REQUEST_PARAMS,
            const QByteArray & data = QByteArray(), const QByteArray & content_type = FORM_URLENCODE,
            Headers * headers = 0, Func * callback = 0, Cookies * cookies = 0) :
                RequestParams(url, (RequestParamsFlags)(rparams | rp_has_payload), headers, callback, cookies), data(data) { prepare(content_type); }

        void prepare(const QByteArray & content_type) {
            bool has_content_type = !content_type.isEmpty();
            bool is_extract_params = isExtractParams();

            bool require_headers = has_content_type || is_extract_params;

            if (require_headers && !headers)
                headers = new Headers();

            if (has_content_type)
                headers -> insert(QByteArrayLiteral("Content-Type"), content_type);

            if (is_extract_params) {
                QByteArray payload = Utils::extractParams(url);

                if (!payload.isEmpty()) {
                    if(!data.isEmpty())
                        data += '&' + payload;
                    else data = payload;
                }
            }
        }
    };
}

#endif // WEB_REQUEST_PARAMS_H