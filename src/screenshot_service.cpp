#include "screenshot_service.hpp"

#include <QPixMap>
#include <QtConcurrent/QtConcurrent>
#include <QScreen>
#include <QGuiApplication>

#include "image_comparison_module.hpp"

const std::chrono::seconds ScreenshotService::DEFAULT_TIME_INTERVAL{60};

ScreenshotService::ScreenshotService(QObject *parent)
    : QObject(parent),
      captureTimer(new QTimer(this))
{
    captureTimer->setInterval(std::chrono::duration_cast<std::chrono::milliseconds>(DEFAULT_TIME_INTERVAL).count());
    connect(captureTimer, &QTimer::timeout, this, &ScreenshotService::captureScreen);
    connect(&similarityWatcher, &QFutureWatcher<double>::finished, this, &ScreenshotService::handleSimilarityCalculationFinished);
}

ScreenshotService::~ScreenshotService() = default;

void ScreenshotService::startCapturing()
{
    captureTimer->start();
}

void ScreenshotService::stopCapturing()
{
    captureTimer->stop();
    similarityWatcher.waitForFinished();
}

void ScreenshotService::captureScreen()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    if (screen == nullptr)
    {
        return;
    }

    QImage screenshot = screen->grabWindow(0).toImage();

    if (!lastScreenshot.isNull())
    {
        QFuture<double> future = QtConcurrent::run(ImageComparisonModule::calculateSimilarity, screenshot, lastScreenshot);
        similarityWatcher.setFuture(future);
    }
    else
    {
        emit newScreenshotTaken(screenshot, 0.0);
    }

    lastScreenshot = std::move(screenshot);
}

void ScreenshotService::handleSimilarityCalculationFinished()
{
    double similarity = similarityWatcher.result();
    emit newScreenshotTaken(lastScreenshot, similarity);
}
