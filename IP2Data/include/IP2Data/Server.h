#pragma once

#include <QUrl>
#include <QNetworkAccessManager>
#include <QObject>
#include "IpData.h"

namespace ip2Data::server
{
class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    void getData(const QString& ip);

signals:
    void signalDataReady(IpData data);

private slots:
    void parseData();

private:
    QNetworkAccessManager _networkManager;
    QNetworkReply *m_reply = nullptr;
    const QString _ipConversionServerAddress = "http://api.ipstack.com/";
    const QString _conversionServerAPIKey = "01329290c82aedc9000d56154145fe5e";
};
}
