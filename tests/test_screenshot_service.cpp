#include <QtTest>
#include "screenshot_service.hpp"

class TestScreenshotService : public QObject
{
    Q_OBJECT

private slots:
    void testScreenshotCapturing();
};

void TestScreenshotService::testScreenshotCapturing()
{
    ScreenshotService service;
    QSignalSpy spy(&service, &ScreenshotService::newScreenshotTaken);
    service.captureScreen();
    QCOMPARE(spy.count(), 1);

    QList<QVariant> arguments = spy.takeFirst();
    QVERIFY(arguments.at(0).type() == QVariant::Image);

    QImage capturedImage = qvariant_cast<QImage>(arguments.at(0));
    QVERIFY(!capturedImage.isNull());
}

QTEST_MAIN(TestScreenshotService)
#include "test_screenshot_service.moc"
