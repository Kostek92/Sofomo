#include "DatabaseManager.h"
#include "WebAddress.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

namespace ip2Data::database
{

const QString DatabaseManager::TABLE_NAME("geodata_table");
const QString DatabaseManager::DRIVER("QSQLITE");
const QString DatabaseManager::ALL_FIELDS("ip, country, capital, city, latitude, longitute");
const QString DatabaseManager::CONNECTION_NAME(TABLE_NAME + "_connection");

DatabaseManager::DatabaseManager(const QString& databaseName)
    : _databaseName{databaseName}
{
    if(openDatabaseConnection())
    {
        createTable();
    }
    else
    {
        qCritical() << "Cannot open database";
    }
}

DatabaseManager::~DatabaseManager()
{
    closeDatabaseConnection();
}

bool DatabaseManager::insertData(const GeolocationData &data) const
{
    const auto ipAddresses(webAddress::convertToIp(data.ip));
    if(ipAddresses.isEmpty())
    {
        return false;
    }
    QSqlQuery sqlQuery;
    sqlQuery.prepare("INSERT INTO  " + TABLE_NAME + " (" + ALL_FIELDS + ") VALUES (?,?,?,?,?,?);");
    sqlQuery.addBindValue(ipAddresses.first());
    sqlQuery.addBindValue(data.country);
    sqlQuery.addBindValue(data.capital);
    sqlQuery.addBindValue(data.city);
    sqlQuery.addBindValue(data.latitude);
    sqlQuery.addBindValue(data.longitude);
    return executeQuery(sqlQuery);
}

GeolocationData DatabaseManager::getData(const QString &address) const
{
    const auto ipAddresses(webAddress::convertToIp(address));
    if(ipAddresses.isEmpty())
    {
        return GeolocationData{};
    }
    QSqlQuery sqlQuery;
    sqlQuery.prepare("SELECT + " + ALL_FIELDS + " FROM " + TABLE_NAME + " WHERE ip = ?;");
    sqlQuery.addBindValue(ipAddresses.first());

    const bool queryExecuted = executeQuery(sqlQuery);
    if (queryExecuted)
    {
        if (sqlQuery.next())
        {
            const auto ip{sqlQuery.value(0).toString()};
            const auto country{sqlQuery.value(1).toString()};
            const auto capital{sqlQuery.value(2).toString()};
            const auto city{sqlQuery.value(3).toString()};
            const auto latitude{sqlQuery.value(4).toDouble()};
            const auto longitude{sqlQuery.value(5).toDouble()};
            return GeolocationData{.ip = ip, .country = country , .capital = capital , .city = city , .latitude = latitude, .longitude = longitude};
        }
    }
    return GeolocationData{};
}

bool DatabaseManager::deleteData(const QString &address) const
{
    const auto ipAddresses(webAddress::convertToIp(address));
    if(ipAddresses.isEmpty())
    {
        return false;
    }
    QSqlQuery sqlQuery;
    sqlQuery.prepare("DELETE FROM " + TABLE_NAME + " WHERE ip = ?;");
    sqlQuery.addBindValue(ipAddresses.first());
    return executeQuery(sqlQuery);
}

bool DatabaseManager::executeQuery(QSqlQuery &sqlQuery) const
{
    QSqlDatabase db = QSqlDatabase::database();
    if(!db.isOpen())
    {
        qCritical() << "Cannot open database" << db.databaseName() << db.lastError();
        return false;
    }
    const bool queryExecuted = sqlQuery.exec();
    if(!queryExecuted)
    {
        qCritical() << "Error executing query: " << sqlQuery.executedQuery() << sqlQuery.lastError();
    }
    return queryExecuted;

}

void DatabaseManager::createTable() const
{
    QString query = "CREATE TABLE IF NOT EXISTS " + TABLE_NAME + " ( ip VARCHAR(20) PRIMARY KEY, country TEXT, capital TEXT, city TEXT, latitude DOUBLE, longitute DOUBLE);";
    QSqlQuery sqlQuery(query);
    executeQuery(sqlQuery);
}

bool DatabaseManager::openDatabaseConnection() const
{
    QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);
    db.setHostName("acidalia");
    db.setDatabaseName(_databaseName);
    db.setUserName("mojito");
    db.setPassword("J0a1m8");
    const bool isOpen = db.open();
    if(!isOpen)
    {
        qCritical() << "Cannot open database";
    }
    return isOpen;
}

void DatabaseManager::closeDatabaseConnection() const
{
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);

}
}
//CREATE TABLE IF NOT EXISTS geodata_table ( ip VARCHAR(20) PRIMARY KEY, country TEXT, capital TEXT, city TEXT, latitude DOUBLE, longitute DOUBLE);
//INSERT INTO geodata_table(ip, country, capital, city, latitude, longitute) VALUES("123.123.123.123", "Polska", "Warszawa", "Gdańsk", 12.1251251, 115.161636);
//SELECT * FROM geodata_table where ip = '123.123.123.123'
