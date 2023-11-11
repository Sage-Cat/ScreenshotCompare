#include <QtTest>
#include "image_comparison_module.hpp"

class TestImageComparisonModule : public QObject
{
    Q_OBJECT

private slots:
    void testCalculateSimilarity_data();
    void testCalculateSimilarity();
};

void TestImageComparisonModule::testCalculateSimilarity_data()
{
    QTest::addColumn<QImage>("image1");
    QTest::addColumn<QImage>("image2");
    QTest::addColumn<double>("expectedSimilarity");

    // Add test data. Here we're adding two identical images and expecting 100% similarity.
    QImage image1(100, 100, QImage::Format_ARGB32);
    QImage image2(100, 100, QImage::Format_ARGB32);
    image1.fill(Qt::white);
    image2.fill(Qt::white);

    QTest::newRow("identical images") << image1 << image2 << 100.0;

    // Add more test data for different scenarios (e.g., completely different images, partially similar images, etc.)
}

void TestImageComparisonModule::testCalculateSimilarity()
{
    QFETCH(QImage, image1);
    QFETCH(QImage, image2);
    QFETCH(double, expectedSimilarity);

    double similarity = ImageComparisonModule::calculateSimilarity(image1, image2);
    QCOMPARE(similarity, expectedSimilarity);
}

QTEST_MAIN(TestImageComparisonModule)
#include "test_image_comparison_module.moc"
