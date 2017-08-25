#include "web_proxy.h"

#include "country.h"
#include "web_manager.h"

using namespace Web;

//https://www.socks-proxy.net/
//http://www.gatherproxy.com/proxylistbycountry
//http://www.gatherproxy.com/sockslist/sockslistbycountry
//http://www.socks24.org/

QHash<QLatin1String, bool> Proxy::blacklisted;
QHash<QString, Proxy::ManagerProxyType> Proxy::type_mapping = {
    {ASTR("http"), Proxy::pt_http},
    {ASTR("https"), Proxy::pt_https},
    {ASTR("socks5"), Proxy::pt_socks5},
    {ASTR("socks5s"), Proxy::pt_socks5s}
};


//https://gimmeproxy.com/
Proxy * Proxy::findinSource1(const ManagerProxyType & ptype, const QByteArray & country) {
    QUrlQuery query;

    query.addQueryItem(ASTR("get"), ASTR("true"));
    query.addQueryItem(ASTR("post"), ASTR("true"));
    query.addQueryItem(ASTR("cookies"), ASTR("true"));
    query.addQueryItem(ASTR("referer"), ASTR("true"));

    ////        user-agent 	true/false 	user-agent header support 	http://gimmeproxy.com/api/getProxy?user-agent=false
    ////        port 	integer 	Proxy port 	http://gimmeproxy.com/api/getProxy?port=80
    ////        anonymityLevel 	0/1 	Anonymity level, 1 - anonymous, 0 - not anonymous 	http://gimmeproxy.com/api/getProxy?anonymityLevel=1
    ////        notCountry 	string 	Exclude proxies from some country from search 	http://gimmeproxy.com/api/getProxy?notCountry=US

    if (ptype != pt_any) {
        if (ptype & pt_ssl)
            query.addQueryItem(ASTR("supportsHttps"), ASTR("true"));

        if (ptype & pt_http)
            query.addQueryItem(ASTR("protocol"), ASTR("http"));
        else if (ptype == pt_socks5)
            query.addQueryItem(ASTR("protocol"), ASTR("socks5"));
        else return 0;
    }

    if (!country.isEmpty()) {
        CountryCell * cell = Country::obj().find(country);

        if (!cell)
            return 0;

        query.addQueryItem(ASTR("country"), cell -> name2letters);
    }

    QUrl url = QUrl(QLatin1Literal("http://gimmeproxy.com/api/getProxy"));
    url.setQuery(query);

    Response * resp = Manager::procGet(url);

    Json json = resp -> toJson();

    if (json.hasKey(QLatin1Literal("ip"))) {
        return new Proxy(
            (ManagerProxyType)(
                strToType(json.string(ASTR("type"))) |
                    (json.boolean(ASTR("supportsHttps")) ? pt_ssl : pt_none)
            ),
            json.string(ASTR("ip")),
            (quint16)json.string(ASTR("port")).toInt(),
            json.string(ASTR("country")).toUtf8()
        );
    }
    else return  0;
}

//http://www.freeproxylists.net/ru/?c=&pt=&pr=&a%5B%5D=0&a%5B%5D=1&a%5B%5D=2&u=90
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
