#pragma once

#include <QObject>

class IP2DataManager : public QObject
{
    Q_OBJECT
public:
    explicit IP2DataManager(QObject *parent = nullptr);

signals:
};
