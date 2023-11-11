#include "mainwindow.hpp"

#include <QVBoxLayout>
#include <QScrollArea>
#include <QDebug>

#include "screenshot_service.hpp"
#include "database_module.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_startStopButton(new QPushButton(tr("Start"), this)),
      m_gridLayout(new QGridLayout()),
      m_statusLabel(new QLabel(tr("Ready"), this)),
      m_screenshotService(new ScreenshotService(this)),
      m_databaseModule(new DatabaseModule(this))
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    connect(m_startStopButton, &QPushButton::clicked, this, &MainWindow::onStartStopClicked);
    mainLayout->addWidget(m_startStopButton);

    m_statusLabel->setMaximumHeight(20);
    mainLayout->addWidget(m_statusLabel);

    resize(800, 600);

    QWidget *gridWidget = new QWidget();
    m_gridLayout->setSpacing(10);
    gridWidget->setLayout(m_gridLayout);
    mainLayout->addWidget(gridWidget);

    setCentralWidget(centralWidget);

    connect(m_screenshotService, &ScreenshotService::newScreenshotTaken, this, &MainWindow::onNewScreenshotTaken);

    loadScreenshotsFromDatabase();
}

MainWindow::~MainWindow() {}

void MainWindow::onStartStopClicked()
{
    const QString startText = tr("Start");
    const QString stopText = tr("Stop");
    const QString capturingText = tr("Capturing...");
    const QString stoppedText = tr("Stopped");

    if (m_startStopButton->text() == startText)
    {
        m_startStopButton->setText(stopText);
        m_statusLabel->setText(capturingText);
        m_screenshotService->startCapturing();
    }
    else
    {
        m_startStopButton->setText(startText);
        m_statusLabel->setText(stoppedText);
        m_screenshotService->stopCapturing();
    }
}

void MainWindow::onNewScreenshotTaken(const QImage &screenshot, double similarity)
{
    updateGridView(screenshot, similarity);
    saveScreenshotToDatabase(screenshot, similarity);
}

void MainWindow::updateGridView(const QImage &screenshot, double similarity)
{
    // Calculate the position for the new image in the grid
    int imageCount = m_gridLayout->count();
    int row = imageCount / 5;
    int col = imageCount % 5;

    // Prepare the image and the similarity label
    QPixmap pixmap = QPixmap::fromImage(screenshot.scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    QLabel *imageLabel = new QLabel();
    imageLabel->setPixmap(pixmap);
    imageLabel->setAlignment(Qt::AlignCenter);

    QLabel *similarityLabel = new QLabel(QString::asprintf("%.2f%%", similarity));
    similarityLabel->setAlignment(Qt::AlignCenter);

    // Group them in a container widget
    QWidget *containerWidget = new QWidget();
    QVBoxLayout *containerLayout = new QVBoxLayout(containerWidget);
    containerLayout->addWidget(imageLabel);
    containerLayout->addWidget(similarityLabel);
    containerWidget->setStyleSheet("border: 1px solid black;");

    // Add the container to the grid
    m_gridLayout->addWidget(containerWidget, row, col);
}

void MainWindow::saveScreenshotToDatabase(const QImage &screenshot, double similarity)
{
    if (!m_databaseModule->saveScreenshot(screenshot, similarity))
        qWarning() << "Could not save screenshot to database";
}

void MainWindow::loadScreenshotsFromDatabase()
{
    auto screenshots = m_databaseModule->loadScreenshots();
    for (auto it = screenshots.constBegin(); it != screenshots.constEnd(); ++it)
    {
        const QImage &image = it.value().first;
        double similarity = it.value().second;
        updateGridView(image, similarity);
    }
}
