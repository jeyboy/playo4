#ifndef WEB_REQUEST_PARAMS_H
#define WEB_REQUEST_PARAMS_H

#include "web_manager_global.h"
#include "web_headers.h"

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
        enum RequestType {
            rt_custom = 0,
            rt_head,
            rt_get,
            rt_post,
            rt_form,
            rt_put,
            rt_delete
        };

        enum RequestParams {
            rp_none = 0,
            rp_async,
            rp_attach_agent,
            rp_extract_params_to_payload,
            rp_print_params
        };


        RequestType rtype;
        RequestParams rparams;
        Headers * headers;

        RequestParams(const RequestType & rtype = rt_get, Headers * headers = 0,
            const RequestParams & rparams = DEFAULT_REQUEST_PARAMS)
                : rtype(rtype), rparams(rparams), headers(headers) {}

        QByteArray typeStr() {
            switch(rtype) {
                case rt_head: return QByteArrayLiteral("HEAD");
                case rt_get: return QByteArrayLiteral("GET");
                case rt_post: return QByteArrayLiteral("POST");
                case rt_form: return QByteArrayLiteral("FORM");
                case rt_put: return QByteArrayLiteral("PUT");
                case rt_delete: return QByteArrayLiteral("DELETE");
                default: return QByteArrayLiteral("CUSTOM");
            }
        }

        bool isAsync() { return rparams & rp_async; }
        bool isExtractParams() { return rparams & rp_extract_params_to_payload; }
        bool isPrintParams() { return rparams & rp_print_params; }
    };

    struct WEBMANAGERSHARED_EXPORT RequestDataParams : public RequestParams {
        QByteArray data;

        RequestDataParams(const QByteArray & data = QByteArray(), const RequestType & rtype = rt_get, Headers * headers = 0,
            const RequestParams & rparams = DEFAULT_REQUEST_PARAMS, const QByteArray & content_type = FORM_URLENCODE) : data(data), RequestParams(rtype, headers, rparams)  {

            bool has_content_type = !content_type.isEmpty();

            bool require_headers = has_content_type || isExtractParams();

            if (require_headers && !headers)
                headers = new Headers();

            if (has_content_type)
                headers -> insert(QByteArrayLiteral("Content-Type"), content_type);

            if (rparams & rp_attach_agent)
                headers -> insert(QByteArrayLiteral("User-Agent"), DEFAULT_AGENT);
        }
    };
}

#endif // WEB_REQUEST_PARAMS_H
