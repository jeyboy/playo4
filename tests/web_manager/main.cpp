#include <QString>
#include <QtTest>
#include <qdebug.h>


#include "web_manager.h"

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
