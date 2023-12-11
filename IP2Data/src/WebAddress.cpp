#include <WebAddress.h>

namespace ip2Data::webAddress
{
namespace
{
    void removeHttp(QString &address)
    {
        address.remove("http://");
        address.remove("https://");
    }
    QStringList getIpsAsStrings(const QList<QHostAddress>& hostAddresses)
    {
        QStringList res;
        for (const auto &hostAddress : hostAddresses)
        {
            res.push_back(hostAddress.toString());
        }
        return res;
    }
}

QStringList convertToIp(QString address)
{
    QHostAddress ipAddress(address);
    if(!ipAddress.isNull())
    {
        return {address};
    }

    removeHttp(address);

    auto resolvedIpInfo{QHostInfo::fromName(address)};
    if(!resolvedIpInfo.addresses().empty())
    {
        return getIpsAsStrings(resolvedIpInfo.addresses());
    }
    return {};
}
}
