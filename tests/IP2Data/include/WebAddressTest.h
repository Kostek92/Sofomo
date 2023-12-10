#include <QTest>

namespace ip2Data
{
class WebAddressTest: public QObject
{
    Q_OBJECT

public:
    explicit WebAddressTest(QObject* parent = nullptr)
        : QObject(parent)
    {
    }
private slots:
    void convertFromDomain();
    void convertFromHttpDomain();
    void convertFromHttpsDomain();
    void convertFromIp();
    void invalidConvert();
};
}
