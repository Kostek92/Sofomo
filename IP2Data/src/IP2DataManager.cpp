#include "IP2DataManager.h"

namespace ip2Data
{
IP2DataManager::IP2DataManager(QObject *parent)
    : QObject{parent}
    , _server{parent}
{
}
}
