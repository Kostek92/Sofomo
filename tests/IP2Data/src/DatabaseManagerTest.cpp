#include "DatabaseManagerTest.h"
#include "IP2Data/DatabaseManager.h"
#include "IP2Data/WebAddress.h"

namespace ip2Data
{

const QString DatabaseManagerTest::TEST_DATABASE_NAME = "testdb";
const GeolocationData DatabaseManagerTest::TEST_DATA{.ip = "123.123.123.123", .country = "Poland", .capital = "Sulechów", .city = "Wrocław", .latitude = 42.0, .longitude = 13.37};

using namespace database;
void DatabaseManagerTest::insertAndGetDataByIp()
{
    DatabaseManager manager(TEST_DATABASE_NAME);
    QVERIFY(manager.insertData(TEST_DATA));
    const auto dbData{manager.getData(TEST_DATA.ip)};
    QVERIFY(TEST_DATA == dbData);
}

void DatabaseManagerTest::insertAndGetDataByDomainAddress()
{
    const QString domainAddress = "www.wp.pl";
    const auto ipAddresses = webAddress::convertToIp(domainAddress);
    Q_ASSERT(!ipAddresses.isEmpty());
    const auto ipAddress = ipAddresses.front();

    GeolocationData expectedResult{TEST_DATA};
    expectedResult.ip = ipAddress;
    GeolocationData testDataWithDomainAddress{TEST_DATA};
    testDataWithDomainAddress.ip = domainAddress;

    DatabaseManager manager(TEST_DATABASE_NAME);
    QVERIFY(manager.insertData(testDataWithDomainAddress));
    const auto dbData{manager.getData(ipAddress)};
    QVERIFY(expectedResult == dbData);
}

void DatabaseManagerTest::insertSameDataTwice()
{
    DatabaseManager manager(TEST_DATABASE_NAME);
    QVERIFY(manager.insertData(TEST_DATA));
    QVERIFY(!manager.insertData(TEST_DATA));
}

void DatabaseManagerTest::deleteData()
{
    DatabaseManager manager(TEST_DATABASE_NAME);
    QVERIFY(manager.insertData(TEST_DATA));
    QVERIFY(manager.deleteData(TEST_DATA.ip));
    const auto dbData{manager.getData(TEST_DATA.ip)};
    QVERIFY(dbData == GeolocationData{});
}

void DatabaseManagerTest::init()
{
    removeDatabaseFile();
}

void DatabaseManagerTest::cleanupTestCase()
{
    removeDatabaseFile();
}

void DatabaseManagerTest::removeDatabaseFile() const
{
    QFile dbFile(TEST_DATABASE_NAME);
    dbFile.remove();
}
}
