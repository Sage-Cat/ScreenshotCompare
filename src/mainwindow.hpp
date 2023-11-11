#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>

class ScreenshotService;
class DatabaseModule;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void onStartStopClicked();
    void onNewScreenshotTaken(const QImage &screenshot, double similarity);

private:
    void updateGridView(const QImage &image, double similarity);
    void saveScreenshotToDatabase(const QImage &screenshot, double similarity);
    void loadScreenshotsFromDatabase();

    QPushButton *m_startStopButton{nullptr};
    QGridLayout *m_gridLayout{nullptr};
    QLabel *m_statusLabel{nullptr};
    ScreenshotService *m_screenshotService{nullptr};
    DatabaseModule *m_databaseModule{nullptr};
};

#endif // MAINWINDOW_HPP
