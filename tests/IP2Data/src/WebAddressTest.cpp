#include "IP2Data/WebAddress.h"
#include "WebAddressTest.h"

namespace ip2Data
{

void WebAddressTest::convertFromDomain()
{
    const QString expectedIp = "52.51.194.221";
    const auto ipAddresses = webAddress::convertToIp("www.justinguitar.com");
    QVERIFY(ipAddresses.contains(expectedIp));
}

void WebAddressTest::convertFromHttpDomain()
{
    const QString expectedIp = "212.77.98.9";
    const auto ipAddresses = webAddress::convertToIp("http://www.wp.pl");
    QVERIFY(ipAddresses.contains(expectedIp));
}

void WebAddressTest::convertFromHttpsDomain()
{
    const QString expectedIp = "212.77.98.9";
    const auto ipAddresses = webAddress::convertToIp("https://www.wp.pl");
    QVERIFY(ipAddresses.contains(expectedIp));
}

void WebAddressTest::convertFromIp()
{
    const QString ipToTest{"52.51.194.221"};
    const auto ipAddresses = webAddress::convertToIp(ipToTest);
    QVERIFY(ipAddresses.contains(ipToTest));

}

void WebAddressTest::invalidConvert()
{
    const auto ipAddresses = webAddress::convertToIp("this is not an valid domain address");
    QVERIFY(ipAddresses.isEmpty());
}
}
