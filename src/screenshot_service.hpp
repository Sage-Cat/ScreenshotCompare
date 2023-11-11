#ifndef SCREENSHOT_SERVICE_HPP
#define SCREENSHOT_SERVICE_HPP

#include <QObject>
#include <QTimer>
#include <QImage>
#include <QFutureWatcher>
#include <chrono>

class ScreenshotService : public QObject
{
    Q_OBJECT

public:
    static const std::chrono::seconds DEFAULT_TIME_INTERVAL;

    explicit ScreenshotService(QObject *parent = nullptr);
    ~ScreenshotService();

    void startCapturing();
    void stopCapturing();

signals:
    void newScreenshotTaken(const QImage &screenshot, double similarity);

public slots:
    void captureScreen();

private slots:
    void handleSimilarityCalculationFinished();

private:
    QTimer *captureTimer{nullptr};
    QImage lastScreenshot;
    QFutureWatcher<double> similarityWatcher;
};

#endif // SCREENSHOT_SERVICE_HPP
