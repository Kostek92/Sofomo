#include <QTest>
#include "IP2Data/IpData.h"
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
    void insertAndGetData();
    void insertSameDataTwice();
    void deleteData();
    void init();
    void cleanupTestCase();

private:
    void removeDatabaseFile() const;
    static const QString TEST_DATABASE_NAME;
    static const IpData TEST_DATA;
};
}