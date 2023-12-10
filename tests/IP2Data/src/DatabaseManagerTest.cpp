#include "DatabaseManagerTest.h"
#include "IP2Data/DatabaseManager.h"

namespace ip2Data
{

const QString DatabaseManagerTest::TEST_DATABASE_NAME = "testdb";
const IpData DatabaseManagerTest::TEST_DATA{.ip = "123.123.123.123", .country = "Poland", .capital = "Sulechów", .city = "Wrocław", .latitude = 42.0, .longitude = 13.37};

using namespace database;
void DatabaseManagerTest::insertAndGetData()
{
    DatabaseManager manager(TEST_DATABASE_NAME);
    QVERIFY(manager.insertData(TEST_DATA));
    const auto dbData{manager.getData(TEST_DATA.ip)};
    QVERIFY(TEST_DATA == dbData);
}

void DatabaseManagerTest::insertSameDataTwice()
{
    DatabaseManager manager(TEST_DATABASE_NAME);
    QVERIFY(manager.insertData(TEST_DATA));
    QVERIFY(!manager.insertData(TEST_DATA));
}

void DatabaseManagerTest::deleteData()
{
    const IpData testData;
    DatabaseManager manager(TEST_DATABASE_NAME);
    QVERIFY(manager.insertData(testData));
    QVERIFY(manager.deleteData(TEST_DATA.ip));
    const auto dbData{manager.getData(TEST_DATA.ip)};
    QVERIFY(dbData == IpData{});
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
