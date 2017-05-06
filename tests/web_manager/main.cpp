#include <QString>
#include <QtTest>
#include <qdebug.h>

#include "web_manager.h"

//http://httpbin.org/ip Returns Origin IP.
//http://httpbin.org/user-agent Returns user-agent.
//http://httpbin.org/headers Returns header dict.
//http://httpbin.org/get Returns GET data.
//http://httpbin.org/post Returns POST data.
//http://httpbin.org/put Returns PUT data.
//http://httpbin.org/delete Returns DELETE data
//http://httpbin.org/gzip Returns gzip-encoded data.
//http://httpbin.org/status/:code Returns given HTTP Status code.
//http://httpbin.org/response-headers?key=val Returns given response headers.
//http://httpbin.org/redirect/:n 302 Redirects n times.
//http://httpbin.org/relative-redirect/:n 302 Relative redirects n times.
//http://httpbin.org/cookies Returns cookie data.
//http://httpbin.org/cookies/set/:name/:value Sets a simple cookie.
//http://httpbin.org/basic-auth/:user/:passwd Challenges HTTPBasic Auth.
//http://httpbin.org/hidden-basic-auth/:user/:passwd 404'd BasicAuth.
//http://httpbin.org/digest-auth/:qop/:user/:passwd Challenges HTTP Digest Auth.
//http://httpbin.org/stream/:n Streams n–100 lines.
//http://httpbin.org/delay/:n Delays responding for n–10 seconds.


#define POST_TEST_URL QUrl(QStringLiteral("http://httpbin.org/post"))


#define HTML_TEST_URL QUrl(QStringLiteral("http://google.com"))
#define JSON_TEST_URL QUrl(QStringLiteral("http://ip.jsontest.com/"))
#define XML_TEST_URL QUrl(QStringLiteral("https://www.w3schools.com/xml/simple.xml"))
#define XML_CSS_TEST_URL QUrl(QStringLiteral("https://www.w3schools.com/xml/simplexsl.xml"))

#define IMAGE_TEST_URL QUrl(QStringLiteral("https://www.google.com/images/branding/googlelogo/2x/googlelogo_color_272x92dp.png"))


class WebManagerTest : public QObject {
    Q_OBJECT

public:
    WebManagerTest();

private Q_SLOTS:
    void testFeatures();
};

WebManagerTest::WebManagerTest() {}

void WebManagerTest::testFeatures() {
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(WebManagerTest)

#include "main.moc"
