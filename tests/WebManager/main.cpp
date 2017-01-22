#include <QString>
#include <QtTest>

#include <curl/curl.h>

class WebManagerTest : public QObject {
    Q_OBJECT

public:
    WebManagerTest();

private Q_SLOTS:
    void testCase1();
};

WebManagerTest::WebManagerTest() {}

void WebManagerTest::testCase1() {
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if(curl) {
      curl_easy_setopt(curl, CURLOPT_URL, "http://www.example.com/");
      res = curl_easy_perform(curl);

      if(CURLE_OK == res) {
        char *ct;
        /* ask for the content-type */
        res = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &ct);

        if((CURLE_OK == res) && ct)
          printf("We received Content-Type: %s\n", ct);
      }

      /* always cleanup */
      curl_easy_cleanup(curl);
    }


    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(WebManagerTest)

#include "main.moc"
