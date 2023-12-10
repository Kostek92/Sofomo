#pragma once

#include "IpData.h"
#include <QSqlQuery>

namespace ip2Data::database
{
class DatabaseManager
{

public:
    DatabaseManager(const QString& databaseName);
    ~DatabaseManager();
    bool insertData(const IpData& data) const;
    IpData getData(const QString& address) const;
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
