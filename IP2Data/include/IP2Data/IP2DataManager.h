#pragma once

#include <QObject>
#include "Server.h"
#include "DatabaseManager.h"

namespace ip2Data
{
class IP2DataManager : public QObject
{
    Q_OBJECT
public:
    explicit IP2DataManager(QObject *parent = nullptr);
    void getData(const QString& address);
    bool deleteData(const QString& address);

signals:
    void signalDataReady(GeolocationData data);
    void signalErrorOccurred();

private slots:
    void onDataReady(ip2Data::GeolocationData data);
    void onErrorOccured();

private:
    QString resolveIp(const QString& address);
    server::Server _server;
    database::DatabaseManager _dbManager;
};
}
