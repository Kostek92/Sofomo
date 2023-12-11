#include <QTest>
#include "ServerTest.h"
#include "WebAddressTest.h"
#include "DatabaseManagerTest.h"
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    int status = 0;
    auto runTest = [&status, argc, argv](QObject* obj) {
        status |= QTest::qExec(obj, argc, argv);
    };

    runTest(new ip2Data::ServerTest);
    runTest(new ip2Data::WebAddressTest);
    runTest(new ip2Data::DatabaseManagerTest);
    return status;
}

// Comment main and comment out below for AutoTest plugin
//QTEST_MAIN(ip2Data::ServerTest)
// QTEST_MAIN(ip2Data::WebAddressTest)
// QTEST_MAIN(ip2Data::DatabaseManagerTest)
