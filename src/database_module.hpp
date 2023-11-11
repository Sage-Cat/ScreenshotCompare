#ifndef DATABASE_MODULE_HPP
#define DATABASE_MODULE_HPP

#include <QObject>
#include <QSqlDatabase>
#include <QImage>
#include <QMap>

class DatabaseModule : public QObject
{
    Q_OBJECT

public:
    explicit DatabaseModule(QObject *parent = nullptr);
    ~DatabaseModule();

    bool openDatabase(); // Opens or creates the database
    bool saveScreenshot(const QImage &image, double similarity);
    QMap<int, QPair<QImage, double>> loadScreenshots(); // Returns a map with an ID and a pair of QImage and similarity

private:
    QSqlDatabase m_database;
    QString m_connectionName;
    void createTableIfNeeded(); // Helper to create the table on first run
};

#endif // DATABASE_MODULE_HPP
