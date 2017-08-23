#include "web_proxy.h"

#include "web_manager.h"

using namespace Web;

//https://gimmeproxy.com/

//http://www.freeproxylists.net/ru/?c=&pt=&pr=&a%5B%5D=0&a%5B%5D=1&a%5B%5D=2&u=90
//https://www.socks-proxy.net/
//http://www.gatherproxy.com/proxylistbycountry
//http://www.gatherproxy.com/sockslist/sockslistbycountry
//http://www.socks24.org/


Proxy * Proxy::findinSource1(const ManagerProxyType & ptype, const QByteArray & country) {
    QUrlQuery query;

    query.addQueryItem(QLatin1Literal("get"), QLatin1Literal("true"));
    query.addQueryItem(QLatin1Literal("post"), QLatin1Literal("true"));
    query.addQueryItem(QLatin1Literal("cookies"), QLatin1Literal("true"));
    query.addQueryItem(QLatin1Literal("referer"), QLatin1Literal("true"));

    ////        user-agent 	true/false 	user-agent header support 	http://gimmeproxy.com/api/getProxy?user-agent=false
    ////        port 	integer 	Proxy port 	http://gimmeproxy.com/api/getProxy?port=80
    /// ////        anonymityLevel 	0/1 	Anonymity level, 1 - anonymous, 0 - not anonymous 	http://gimmeproxy.com/api/getProxy?anonymityLevel=1

    if (ptype != pt_any) {
        if (ptype & pt_ssl)
            query.addQueryItem(QLatin1Literal("supportsHttps"), QLatin1Literal("true"));

        if (ptype & pt_http)
            query.addQueryItem(QLatin1Literal("protocol"), QLatin1Literal("http"));
        else if (ptype == pt_socks5)
            query.addQueryItem(QLatin1Literal("protocol"), QLatin1Literal("socks5"));
        else return 0;
    }

    if (!country.isEmpty()) {

    }


////        country 	string 	Return only proxies with specified country
//    }


    //    RequestParams * params = new RequestParams(
    //        COOKIE_TEST_URL(QByteArrayLiteral("na"), QByteArrayLiteral("me"))
    //    );
    //    Response * resp = Manager::procGet(params);

    //    Json obj = resp -> toJson()[QStringLiteral("cookies")];
}
Proxy * Proxy::findinSource2(const ManagerProxyType & ptype, const QByteArray & country) {

}
Proxy * Proxy::findinSource3(const ManagerProxyType & ptype, const QByteArray & country) {

}
Proxy * Proxy::findinSource4(const ManagerProxyType & ptype, const QByteArray & country) {

}
Proxy * Proxy::findinSource5(const ManagerProxyType & ptype, const QByteArray & country) {

}



Proxy * Proxy::find(const ManagerProxyType & ptype, const QByteArray & country) {

}
