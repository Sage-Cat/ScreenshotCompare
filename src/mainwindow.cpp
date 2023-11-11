#include "mainwindow.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          m_startStopButton(new QPushButton("Start", this)),
                                          m_gridLayout(new QGridLayout()),
                                          m_statusLabel(new QLabel("Ready", this)),
                                          m_screenshotService(new ScreenshotService(this)),
                                          m_databaseModule(new DatabaseModule(this))
{
    // Set up the main window layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Set up the start/stop button
    connect(m_startStopButton, &QPushButton::clicked, this, &MainWindow::onStartStopClicked);
    mainLayout->addWidget(m_startStopButton);

    // Set up the status label
    mainLayout->addWidget(m_statusLabel);

    // Set up the grid layout for displaying screenshots
    QWidget *gridWidget = new QWidget();
    gridWidget->setLayout(m_gridLayout);
    mainLayout->addWidget(gridWidget);

    setCentralWidget(centralWidget);

    // Connect ScreenshotService
    connect(m_screenshotService, &ScreenshotService::newScreenshotTaken, this, &MainWindow::onNewScreenshotTaken);

    // Load existing screenshots from database
    loadScreenshotsFromDatabase();
}

MainWindow::~MainWindow()
{
    // Clean up if needed
}

void MainWindow::onStartStopClicked()
{
    if (m_startStopButton->text() == "Start")
    {
        m_startStopButton->setText("Stop");
        m_statusLabel->setText("Capturing...");
        m_screenshotService->startCapturing(); // Start capturing screenshots
    }
    else
    {
        m_startStopButton->setText("Start");
        m_statusLabel->setText("Stopped");
        m_screenshotService->stopCapturing(); // Stop capturing screenshots
    }
}

void MainWindow::onNewScreenshotTaken(const QImage &screenshot, double similarity)
{
    // Update the UI with the new screenshot
    updateGridView(screenshot, similarity);

    // Save the new screenshot to the database
    saveScreenshotToDatabase(screenshot, similarity);
}

void MainWindow::updateGridView(const QImage &screenshot, double similarity)
{
    // Convert the QImage to a QPixmap for display in the grid
    QPixmap pixmap = QPixmap::fromImage(screenshot.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation)); // Adjust size as needed
    QLabel *imageLabel = new QLabel();
    imageLabel->setPixmap(pixmap);

    QLabel *similarityLabel = new QLabel(QString::number(similarity) + "%");

    // Assuming you have a predefined layout, we add the new screenshot and similarity label to it
    // Clear the layout first to make room for the new screenshot at position 1
    QLayoutItem *child;
    while ((child = m_gridLayout->takeAt(0)) != nullptr)
    {
        delete child->widget(); // Delete the widget to prevent memory leak
        delete child;
    }

    // Add the new image and similarity label at the beginning
    m_gridLayout->addWidget(imageLabel, 0, 0);      // Add the image label at the first row and column
    m_gridLayout->addWidget(similarityLabel, 0, 1); // Add the similarity label next to it

    // Now, repopulate the grid with the rest of the thumbnails
    // This will be handled by another function that maintains a list of thumbnails
    // repopulateGrid();
}

void MainWindow::onNewScreenshotTaken(const QImage &screenshot, double similarity)
{
    // Update the UI with the new screenshot
    updateGridView(screenshot, similarity);

    // Save the new screenshot to the database
    saveScreenshotToDatabase(screenshot, similarity);
}

void MainWindow::saveScreenshotToDatabase(const QImage &screenshot, double similarity)
{
    if (!m_databaseModule->saveScreenshot(screenshot, similarity))
    {
        // Handle error - could not save screenshot
    }
}

void MainWindow::loadScreenshotsFromDatabase()
{
    auto screenshots = m_databaseModule->loadScreenshots();
    for (auto it = screenshots.constBegin(); it != screenshots.constEnd(); ++it)
    {
        // Add each screenshot to the grid view
        // You will need to create a method to add screenshots to the grid
        const QImage &image = it.value().first;
        double similarity = it.value().second;
        updateGridView(image, similarity);
    }
}
