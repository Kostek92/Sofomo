#pragma once

#include <QObject>
#include "Server.h"

namespace ip2Data
{
    class IP2DataManager : public QObject
    {
        Q_OBJECT
    public:
        explicit IP2DataManager(QObject *parent = nullptr);

    signals:
    private:
        server::Server _server;
    };

}
