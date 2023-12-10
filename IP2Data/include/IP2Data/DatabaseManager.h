#pragma once

#include "GeolocationData.h"
#include <QSqlQuery>

namespace ip2Data::database
{
class DatabaseManager
{

public:
    DatabaseManager(const QString& databaseName);
    ~DatabaseManager();
    bool insertData(const GeolocationData& data) const;
    GeolocationData getData(const QString& address) const;
    bool deleteData(const QString& address) const;

private:
    bool executeQuery(QSqlQuery& sqlQuery) const;
    void createTable() const;
    bool openDatabaseConnection() const;
    void closeDatabaseConnection() const;
    static const QString TABLE_NAME;
    static const QString DRIVER;
    static const QString ALL_FIELDS;
    static const QString CONNECTION_NAME;
    const QString _databaseName;
};

}
