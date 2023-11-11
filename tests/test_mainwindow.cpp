#include <QtTest>
#include <QPushButton>
#include <QLabel>
#include "mainwindow.hpp"

class TestMainWindow : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testButtonStartStop();

private:
    MainWindow *mainWindow;
};

void TestMainWindow::initTestCase()
{
    mainWindow = new MainWindow();
}

void TestMainWindow::cleanupTestCase()
{
    delete mainWindow;
}

void TestMainWindow::testButtonStartStop()
{
    QPushButton *button = mainWindow->findChild<QPushButton *>();
    QVERIFY(button);

    QSignalSpy spy(button, &QPushButton::clicked);
    QTest::mouseClick(button, Qt::LeftButton);
    QCOMPARE(button->text(), QString("Stop"));

    QTest::mouseClick(button, Qt::LeftButton);
    QCOMPARE(button->text(), QString("Start"));
}

QTEST_MAIN(TestMainWindow)
#include "test_mainwindow.moc"
