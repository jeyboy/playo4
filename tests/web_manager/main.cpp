#include <QString>
#include <QtTest>
#include <QSignalSpy>
#include <qdebug.h>

#include "web_manager.h"

//http://httpbin.org/ip Returns Origin IP.
//http://httpbin.org/user-agent Returns user-agent.
//http://httpbin.org/gzip Returns gzip-encoded data.
//http://httpbin.org/basic-auth/:user/:passwd Challenges HTTPBasic Auth.
//http://httpbin.org/hidden-basic-auth/:user/:passwd 404'd BasicAuth.
//http://httpbin.org/digest-auth/:qop/:user/:passwd Challenges HTTP Digest Auth.
//http://httpbin.org/stream/:n Streams n–100 lines.


#define GET_TEST_URL QUrl(QStringLiteral("http://httpbin.org/get"))
#define POST_TEST_URL QUrl(QStringLiteral("http://httpbin.org/post"))
#define PUT_TEST_URL QUrl(QStringLiteral("http://httpbin.org/put"))
#define DELETE_TEST_URL QUrl(QStringLiteral("http://httpbin.org/delete"))

//http://httpbin.org/response-headers?key=val Returns given response headers.
#define HEADERS_TEST_URL QUrl(QStringLiteral("http://httpbin.org/headers"))
#define STATUS_TEST_URL(code) QUrl(QStringLiteral("http://httpbin.org/status/") + QString::number(code))
#define REDIRECT_TEST_URL(times) QUrl(QStringLiteral("http://httpbin.org/redirect/") + QString::number(times))
#define REL_REDIRECT_TEST_URL(times) QUrl(QStringLiteral("http://httpbin.org/relative-redirect/") + QString::number(times))

#define COOKIES_TEST_URL QUrl(QStringLiteral("http://httpbin.org/cookies"))
#define COOKIE_TEST_URL(name, val) QUrl(QStringLiteral("http://httpbin.org/cookies/set/") + name + '/' + value)

#define DELAY_TEST_URL(secs) QUrl(QStringLiteral("http://httpbin.org/delay/") + QString::number(secs))

#define HTML_TEST_URL QUrl(QStringLiteral("http://google.com"))
#define JSON_TEST_URL QUrl(QStringLiteral("http://ip.jsontest.com/"))
#define XML_TEST_URL QUrl(QStringLiteral("https://www.w3schools.com/xml/simple.xml"))
#define XML_CSS_TEST_URL QUrl(QStringLiteral("https://www.w3schools.com/xml/simplexsl.xml"))

#define IMAGE_TEST_URL QUrl(QStringLiteral("https://www.google.com/images/branding/googlelogo/2x/googlelogo_color_272x92dp.png"))

using namespace Web;

class WebManagerTest : public QObject {
    Q_OBJECT
public:
    WebManagerTest();

protected:
    void instantiateThread() {
        Manager::setMainThreadSync(qApp -> thread());
    }

private Q_SLOTS:
    void testSyncGet();
    void testSyncPost();
    void testSyncPut();
    void testSyncDelete();
};

WebManagerTest::WebManagerTest() {}

void WebManagerTest::testSyncGet() {
    RequestParams * params = new RequestParams(GET_TEST_URL);
    Response * resp = Manager::procGet(params);
    qDebug() << resp -> toText();
    QVERIFY2(true, "Failure");
}
void WebManagerTest::testSyncPost() {
    RequestDataParams * params = new RequestDataParams(POST_TEST_URL, DEFAULT_FORM_REQUEST_PARAMS);
    Response * resp = Manager::procPost(params);
    qDebug() << resp -> toText();
    QVERIFY2(true, "Failure");
}
void WebManagerTest::testSyncPut() {
    RequestDataParams * params = new RequestDataParams(PUT_TEST_URL, DEFAULT_FORM_REQUEST_PARAMS);
    Response * resp = Manager::procPost(params);
    qDebug() << resp -> toText();
    QVERIFY2(true, "Failure");
}
void WebManagerTest::testSyncDelete() {
    RequestParams * params = new RequestParams(DELETE_TEST_URL);
    Response * resp = Manager::procDelete(params);
    qDebug() << resp -> toText();
    QVERIFY2(true, "Failure");
}

QTEST_GUILESS_MAIN(WebManagerTest) // QTEST_APPLESS_MAIN // QTEST_MAIN

#include "main.moc"



/////////////////////////////////////////////
////head  file
/////////////////////////////////////////////
//#include <QHttp>
//#include <QHttpResponseHeader>
//#include <QString>
//class hp:public QHttp
//{
//    Q_OBJECT
//public:
//    hp();
//    QString data;
//signals:
//    void ok();
//public slots:
//    void done(bool);
//};

/////////////////////////////////////////////
////cpp file
/////////////////////////////////////////////
//#include <QDebug>
//#include "hp.h"
//hp::hp()
//{
//   connect(this, SIGNAL(done(bool)), this, SLOT(done(bool)));

//}
//void hp::done( bool)
//{
//    data=readAll().mid(0,10);
//    qDebug()<<data<<endl;
//    emit ok();
//}

////////////////////////////////////////
//// test main
////////////////////////////////////////
//#include <QtTest>
//#include <QtCore>
// #include <QSignalSpy>
//#include "hp.h"

//class testDate: public QObject
//{
//   Q_OBJECT
//private slots:
//   void testValidity();
//};

//void testDate::testValidity()
//{
//    hp h;
//    h.setHost("webserver");
//    h.get("url");
//    QSignalSpy spy(&h, SIGNAL(ok()));
//    while (spy.count() == 0)
//        QTest::qWait(200);
//    QVERIFY( h.data == "expected data" );
//}
