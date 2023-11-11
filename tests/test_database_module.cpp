#include <QtTest>
#include "database_module.hpp"

class TestDatabaseModule : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testOpenDatabase();
    void testSaveScreenshot();
    void testLoadScreenshots();

private:
    DatabaseModule *dbModule;
};

void TestDatabaseModule::initTestCase()
{
    dbModule = new DatabaseModule();
}

void TestDatabaseModule::cleanupTestCase()
{
    delete dbModule;
}

void TestDatabaseModule::testOpenDatabase()
{
    QVERIFY(dbModule->openDatabase());
}

void TestDatabaseModule::testSaveScreenshot()
{
    QImage dummyImage(100, 100, QImage::Format_RGB32);
    dummyImage.fill(Qt::white);
    QVERIFY(dbModule->saveScreenshot(dummyImage, 99.9));
}

void TestDatabaseModule::testLoadScreenshots()
{
    auto screenshots = dbModule->loadScreenshots();
    QVERIFY(!screenshots.isEmpty());
}

QTEST_MAIN(TestDatabaseModule)
#include "test_database_module.moc"
