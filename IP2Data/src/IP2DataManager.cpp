#include "IP2DataManager.h"
#include "WebAddress.h"

namespace ip2Data
{
IP2DataManager::IP2DataManager(QObject *parent)
    : QObject{parent}
    , _server{parent}
    , _dbManager{"SofomoDb"}
{
    connect(&_server, &server::Server::signalDataReady, this, &IP2DataManager::onDataReady);
    connect(&_server, &server::Server::signalErrorOccurred, this, &IP2DataManager::onErrorOccured);
}

void IP2DataManager::getData(const QString &address)
{
    const auto ipAddress = resolveIp(address);
    if(ipAddress.isEmpty())
    {
        return;
    }
    auto data = _dbManager.getData(ipAddress);
    if(data.isEmpty())
    {
        qInfo() << "Data" << address << "not found in database. Checking server";
       _server.getData(ipAddress);
    }
    else
    {
        qInfo() << "Data" << address << "found in database";
        emit signalDataReady(data);
    }
}

bool IP2DataManager::deleteData(const QString &address)
{
    const auto ipAddress = resolveIp(address);
    if(ipAddress.isEmpty())
    {
        return false;
    }
    if(_dbManager.containsData(ipAddress))
    {
        if(_dbManager.deleteData(ipAddress))
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
        emit signalErrorOccurred();
    }
    else
    {
        data.ip = resolveIp(data.ip);
        qInfo() << "Data" << data.ip << "found on server. Saving into database";
        _dbManager.insertData(data);
        emit signalDataReady(data);
    }
}

void IP2DataManager::onErrorOccured()
{
    qInfo() << "Data not found";
    emit signalErrorOccurred();
}

QString IP2DataManager::resolveIp(const QString &address)
{
    const auto ipAddresses(webAddress::convertToIp(address));
    if(ipAddresses.isEmpty())
    {
        qInfo() << "Cannot resolve IP address from" << address;
        emit signalErrorOccurred();
        return QString();
    }
    return ipAddresses.first();
}
}
