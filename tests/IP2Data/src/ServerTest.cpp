#include "ServerTest.h"
namespace ip2Data
{
void ServerTest::testData(const IpData& expectedData)
{
    connect(&_server, &server::Server::signalDataReady, this, [&expectedData](const IpData serverResponse)
            {
                QCOMPARE(serverResponse, expectedData);
            });
    QCOMPARE(_spy.wait(5000), true);
}

void ServerTest::testDataReadyWithIp()
{
    const QString ipToTest{"212.77.98.9"};
    _server.getData(ipToTest);
    testData(IpData{.ip = ipToTest, .country = "Poland", .capital = "Warsaw", .city = "Gdańsk", .latitude = 54.31, .longitude = 18.63});
}

void ServerTest::testDataReadyWithDomainAddress()
{
    _server.getData("https://www.wp.pl");
    testData(IpData{.ip = "212.77.98.9", .country = "Poland", .capital = "Warsaw", .city = "Gdańsk", .latitude = 54.31, .longitude = 18.63});
}


void ServerTest::testInvalidIp()
{
    const QString ipToTest{"127.0.0.1"};
    _server.getData(ipToTest);
    testData({.ip = ipToTest});
}

void ServerTest::testNotIp()
{
    _server.getData("notAnIp");
    QCOMPARE(_spy.wait(3000), false);
}
}
