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
        ,_spy(&_server, &server::Server::signalDataReady)
    {
    }

private slots:
    void testDataReadyWithIp();
    void testDataReadyWithDomainAddress();
    void testInvalidIp();
    void testNotIp();

private:
    void testData(const IpData& expectedData);

    server::Server _server;
    QSignalSpy _spy;
};
}
