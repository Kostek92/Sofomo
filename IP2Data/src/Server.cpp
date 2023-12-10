#include "Server.h"
#include "WebAddress.h"
#include <QNetworkReply>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>

namespace ip2Data::Server
{
Server::Server(QObject *parent)
    : QObject{parent}
{

}

void Server::getData(const QString &address)
{
    const auto ipAddress(webAddress::convertToIp(address));
    if(ipAddress.isEmpty())
    {
        return;
    }
    if (m_reply) {
        m_reply->abort();
        m_reply->deleteLater();
        m_reply = nullptr;
    }
    QUrlQuery query;
    query.addQueryItem("access_key", _conversionServerAPIKey);
    query.addQueryItem("output", "json");
    const QNetworkRequest req (_ipConversionServerAddress + ipAddress.first() + "?" + query.toString());
    m_reply = _networkManager.get(req);
    connect(m_reply, &QNetworkReply::finished, this, &Server::parseData);
}

void Server::parseData()
{
    if (m_reply->error() == QNetworkReply::NoError)
    {
        QByteArray data = m_reply->readAll();
        const QJsonDocument jsonDocument{QJsonDocument::fromJson(data)};
        if (!jsonDocument.isNull())
        {
            const auto jsonObject {jsonDocument.object()};
            const auto ip = jsonDocument["ip"].toString();
            const auto countryName = jsonDocument["country_name"].toString();
            const auto city = jsonDocument["city"].toString();
            const auto locationObj = jsonDocument["location"].toObject();
            const auto capital = locationObj["capital"].toString();
            const auto latitude = jsonDocument["latitude"].toDouble();
            const auto longitude = jsonDocument["longitude"].toDouble();
            emit signalDataReady( IpData{.ip = ip, .country = countryName , .capital = capital, .city = city, .latitude = latitude, .longitude = longitude} );
        }
        else
        {
            qCritical() << "Received invalid reply";
        }
    }
    else if (m_reply->error() != QNetworkReply::OperationCanceledError) {
        qCritical() << "Reply failed, eror:" << m_reply->errorString();
    }
}
}
