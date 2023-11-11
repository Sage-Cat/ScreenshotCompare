#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include "screenshot_service.hpp"
#include "database_module.hpp"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onStartStopClicked();
    void onNewScreenshotTaken(const QImage &screenshot, double similarity);
    void updateGridView(const QImage &image, double similarity);
    void saveScreenshotToDatabase(const QImage &screenshot, double similarity);
    void loadScreenshotsFromDatabase();

private:
    Ui::MainWindow *ui;
    QPushButton *m_startStopButton;
    QGridLayout *m_gridLayout;
    QLabel *m_statusLabel;
    ScreenshotService *m_screenshotService;
    DatabaseModule *m_databaseModule;
};

#endif // MAINWINDOW_HPP
