#ifndef SCREENSHOT_SERVICE_HPP
#define SCREENSHOT_SERVICE_HPP

#include <QObject>
#include <QTimer>
#include <QImage>

class ScreenshotService : public QObject
{
    Q_OBJECT

public:
    explicit ScreenshotService(QObject *parent = nullptr);
    ~ScreenshotService();

    void startCapturing();
    void stopCapturing();

signals:
    void newScreenshotTaken(const QImage &screenshot, double similarity);

private slots:
    void captureScreen();

private:
    QTimer *captureTimer;
    QImage lastScreenshot;
    double calculateSimilarity(const QImage &image1, const QImage &image2);
};

#endif // SCREENSHOT_SERVICE_HPP
