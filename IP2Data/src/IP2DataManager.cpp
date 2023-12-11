#include "IP2DataManager.h"

namespace ip2Data
{
IP2DataManager::IP2DataManager(QObject *parent)
    : QObject{parent}
    , _server{parent}
    , _dbManager{"SofomoDb"}
{
    connect(&_server, &server::Server::signalDataReady, this, &IP2DataManager::onDataReady);
}

bool IP2DataManager::saveData(const GeolocationData &data) const
{
    return _dbManager.insertData(data);
}

void IP2DataManager::getData(const QString &address)
{
    auto data = _dbManager.getData(address);
    if(data.isEmpty())
    {
        qInfo() << "Data" << address << "not found in database. Checking server";
       _server.getData(address);
    }
    else
    {
        qInfo() << "Data" << address << "found in database";
        emit signalDataReady(data);
    }
}

bool IP2DataManager::deleteData(const QString &address) const
{
    if(_dbManager.containsData(address))
    {
        if(_dbManager.deleteData(address))
        {
            qInfo() << "Data" << address << "deleted from database";
            return true;
        }
    }
    qInfo() << "Data" << address << "not found in database";
    return false;
}

void IP2DataManager::onDataReady(GeolocationData data)
{
    if(data.isEmpty())
    {
        qInfo() << "Data" << data.ip << "not found on server";
    }
    else
    {
        qInfo() << "Data" << data.ip << "found on server. Saving into database";
        _dbManager.insertData(data);
    }
    emit signalDataReady(data);
}
}
