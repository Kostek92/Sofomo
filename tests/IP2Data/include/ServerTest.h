#include <QTest>
namespace ip2Data
{
class ServerTest: public QObject
{
    Q_OBJECT
public:
    explicit ServerTest(QObject* parent = nullptr)
        : QObject(parent)
    {
    }

private slots:
    void testDataReadyWithIp();
    void testDataReadyWithDomainAddress();
    void testInvalidIp();
    void testNotIp();

private:
};
}
