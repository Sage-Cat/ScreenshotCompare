#include "database_module.hpp"
#include <QSqlQuery>
#include <QVariant>
#include <QBuffer>

DatabaseModule::DatabaseModule(QObject *parent) : QObject(parent), m_connectionName("screenshot_connection")
{
    openDatabase();
    createTableIfNeeded();
}

DatabaseModule::~DatabaseModule()
{
    m_database.close();
}

bool DatabaseModule::openDatabase()
{
    m_database = QSqlDatabase::addDatabase("QSQLITE", m_connectionName);
    m_database.setDatabaseName("screenshots.db");

    if (!m_database.open())
    {
        // Handle error - could not open database
        return false;
    }

    return true;
}

void DatabaseModule::createTableIfNeeded()
{
    QSqlQuery query(QSqlDatabase::database(m_connectionName));
    query.exec("CREATE TABLE IF NOT EXISTS screenshots ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "image BLOB NOT NULL, "
               "similarity REAL NOT NULL)");
}

bool DatabaseModule::saveScreenshot(const QImage &image, double similarity)
{
    if (image.isNull())
    {
        // Handle error - image is null
        return false;
    }

    QByteArray imageData;
    QBuffer buffer(&imageData);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG"); // Save the image as a PNG

    QSqlQuery query(QSqlDatabase::database(m_connectionName));
    query.prepare("INSERT INTO screenshots (image, similarity) VALUES (?, ?)");
    query.addBindValue(imageData);
    query.addBindValue(similarity);

    if (!query.exec())
    {
        // Handle error - could not insert data
        return false;
    }

    return true;
}

QMap<int, QPair<QImage, double>> DatabaseModule::loadScreenshots()
{
    QMap<int, QPair<QImage, double>> screenshots;

    QSqlQuery query(QSqlDatabase::database(m_connectionName));
    query.exec("SELECT id, image, similarity FROM screenshots");

    while (query.next())
    {
        int id = query.value(0).toInt();
        QByteArray imageData = query.value(1).toByteArray();
        double similarity = query.value(2).toDouble();

        QImage image;
        image.loadFromData(imageData, "PNG");

        screenshots.insert(id, qMakePair(image, similarity));
    }

    return screenshots;
}
