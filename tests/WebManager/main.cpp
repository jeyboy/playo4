#include <QString>
#include <QtTest>

#include <qdebug.h>

#include <curl/curl.h>

class WebManagerTest : public QObject {
    Q_OBJECT

public:
    WebManagerTest();

private Q_SLOTS:
    void testFeatures();
    void testCase1();
};

WebManagerTest::WebManagerTest() {}

void WebManagerTest::testFeatures() {
    curl_version_info_data * d = curl_version_info(CURLVERSION_NOW);

    qDebug() << "CURL_VERSION_IPV6:" << ((d -> features & CURL_VERSION_IPV6) != 0);
    qDebug() << "CURL_VERSION_SSL:" << ((d -> features & CURL_VERSION_SSL) != 0);
    qDebug() << "CURL_VERSION_LIBZ:" << ((d -> features & CURL_VERSION_LIBZ) != 0);
    qDebug() << "CURL_VERSION_LARGEFILE:" << ((d -> features & CURL_VERSION_LARGEFILE) != 0);
    qDebug() << "CURL_VERSION_CONV:" << ((d -> features & CURL_VERSION_CONV) != 0);

    qDebug() << "CURL_VERSION_HTTP2:" << ((d -> features & CURL_VERSION_HTTP2) != 0);
    qDebug() << "CURL_VERSION_UNIX_SOCKETS:" << ((d -> features & CURL_VERSION_UNIX_SOCKETS) != 0);
    qDebug() << "CURL_VERSION_HTTPS_PROXY:" << ((d -> features & CURL_VERSION_HTTPS_PROXY) != 0);

    delete d;

    QVERIFY2(true, "Failure");
}

void WebManagerTest::testCase1() {
    CURL *curl;
    CURLcode res;   

    curl = curl_easy_init();
    if(curl) {
//      curl_easy_setopt(curl, CURLOPT_URL, "http://www.example.com/");
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.github.com/users/mralexgray/repos");
        curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "gzip,deflate");
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

      res = curl_easy_perform(curl);

      if(CURLE_OK == res) {
        char *ct;
        /* ask for the content-type */
        res = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &ct);

        if((CURLE_OK == res) && ct)
          printf("We received Content-Type: %s\n", ct);
      } else {
          printf(curl_easy_strerror(res));
      }

      /* always cleanup */
      curl_easy_cleanup(curl);
    }


    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(WebManagerTest)

#include "main.moc"
