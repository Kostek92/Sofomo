#include "ServerTest.h"
#include <QSignalSpy>
#include "IP2Data/Server.h"
namespace ip2Data
{

void ServerTest::testDataReadyWithIp()
{
    const QString ipToTest{"212.77.98.9"};
    const GeolocationData& expectedData {.ip = ipToTest, .country = "Poland", .capital = "Warsaw", .city = "Gdańsk", .latitude = 54.31, .longitude = 18.63};
    server::Server server(this);
    QSignalSpy spy(&server, &server::Server::signalDataReady);
    connect(&server, &server::Server::signalDataReady, this, [expectedData](const GeolocationData serverResponse)
            {
                QCOMPARE(serverResponse, expectedData);
            });
    server.getData(ipToTest);
    QCOMPARE(spy.wait(5000), true);
}

void ServerTest::testDataReadyWithDomainAddress()
{    
    const QString ipToTest{"212.77.98.9"};
    const GeolocationData& expectedData {.ip = ipToTest, .country = "Poland", .capital = "Warsaw", .city = "Gdańsk", .latitude = 54.31, .longitude = 18.63};
    server::Server server(this);
    QSignalSpy spy(&server, &server::Server::signalDataReady);
    connect(&server, &server::Server::signalDataReady, this, [expectedData](const GeolocationData serverResponse)
            {
                QCOMPARE(serverResponse, expectedData);
            });
    server.getData("https://www.wp.pl");
    QCOMPARE(spy.wait(5000), true);
}

void ServerTest::testInvalidIp()
{
    const QString ipToTest{"127.0.0.1"};
    const GeolocationData& expectedData {.ip = ipToTest};
    server::Server server(this);
    QSignalSpy spy(&server, &server::Server::signalDataReady);
    connect(&server, &server::Server::signalDataReady, this, [expectedData](const GeolocationData serverResponse)
            {
                QCOMPARE(serverResponse, expectedData);
            });
    server.getData(ipToTest);
}

void ServerTest::testNotIp()
{
    server::Server server(this);
    QSignalSpy spy(&server, &server::Server::signalDataReady);
    server.getData("notAnIp");
    QCOMPARE(spy.wait(3000), false);
}
}
