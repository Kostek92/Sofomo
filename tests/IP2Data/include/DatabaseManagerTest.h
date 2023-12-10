#include <QTest>
#include "IP2Data/GeolocationData.h"
namespace ip2Data
{
class DatabaseManagerTest: public QObject
{
    Q_OBJECT
public:
    explicit DatabaseManagerTest(QObject* parent = nullptr)
        : QObject(parent)
    {
    }

private slots:
    void insertAndGetDataByIp();
    void insertAndGetDataByDomainAddress();
    void insertSameDataTwice();
    void deleteData();
    void init();
    void cleanupTestCase();

private:
    void removeDatabaseFile() const;
    static const QString TEST_DATABASE_NAME;
    static const GeolocationData TEST_DATA;
};
}
