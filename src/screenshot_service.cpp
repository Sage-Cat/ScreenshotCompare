#include "screenshot_service.hpp"

#include <QScreen>
#include <QGuiApplication>
#include <QDesktopWidget>
#include <QWindow>

#include "image_comparison_module.hpp"

ScreenshotService::ScreenshotService(QObject *parent) : QObject(parent),
                                                        captureTimer(new QTimer(this))
{
    // Set up the timer with an interval and connect it to the captureScreen slot
    captureTimer->setInterval(60000); // Set to 60000ms for 1 minute intervals
    connect(captureTimer, &QTimer::timeout, this, &ScreenshotService::captureScreen);
}

ScreenshotService::~ScreenshotService()
{
    // Clean up if needed
}

void ScreenshotService::startCapturing()
{
    captureTimer->start();
}

void ScreenshotService::stopCapturing()
{
    captureTimer->stop();
}

void ScreenshotService::captureScreen()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    if (!screen)
        return;

    QImage screenshot = screen->grabWindow(0).toImage();

    // Here you would have your logic to compare `screenshot` with `lastScreenshot`
    // For now, let's just emit the signal with a dummy similarity value
    double similarity = 0.0; // Replace with actual calculation
    if (!lastScreenshot.isNull())
    {
        similarity = calculateSimilarity(screenshot, lastScreenshot);
    }

    emit newScreenshotTaken(screenshot, similarity);
    lastScreenshot = screenshot;
}

double ScreenshotService::calculateSimilarity(const QImage &image1, const QImage &image2)
{
    return ImageComparisonModule::calculateSimilarity(image1, image2);
}
