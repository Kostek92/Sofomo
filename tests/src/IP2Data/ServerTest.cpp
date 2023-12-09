#include <QTest>
#include <QSignalSpy>
#include "IP2Data/Server.h"
namespace ip2Data
{
class ServerTest: public QObject
{
    Q_OBJECT
public:
    ServerTest(QObject* parent = nullptr)
        : QObject(parent)
        ,_server{this}
        ,_spy(&_server, &Server::Server::signalDataReady)
    {
    }

private slots:
    void testDataReady();
    void testInvalidIp();
    void testNotIp();

private:
    void testData(const IpData& expectedData);

    Server::Server _server;
    QSignalSpy _spy;
};

void ServerTest::testData(const IpData& expectedData)
{
    connect(&_server, &Server::Server::signalDataReady, this, [&expectedData](const IpData serverResponse)
            {
                QCOMPARE(serverResponse, expectedData);
            });
    QCOMPARE(_spy.wait(5000), true);
}

void ServerTest::testDataReady()
{
    const QString ipToTest{"193.17.41.249"};
    _server.getData(ipToTest);
    testData(IpData{.ip = ipToTest, .country = "Poland", .capital = "Warsaw", .city = "Włochy", .latitude = 52.17, .longitude = 20.91});
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


QTEST_MAIN(ip2Data::ServerTest)
#include "ServerTest.moc"
