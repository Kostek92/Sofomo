#pragma once

#include <QObject>
#include "GeolocationDataInfo.h"
#include "IP2Data/IP2DataManager.h"
#include "IP2Data/GeolocationData.h"

class AppController : public QObject
{
    Q_OBJECT
public:
    explicit AppController(QObject *parent = nullptr);
    Q_PROPERTY(GeolocationDataInfo* currentData READ getCurrentData WRITE setCurrentData NOTIFY currentDataChanged)
    Q_PROPERTY(bool processing READ processing WRITE setProcessing NOTIFY processingChanged)

    GeolocationDataInfo *getCurrentData() const;
    void setCurrentData(GeolocationDataInfo *newCurrentData);

    bool processing() const;
    void setProcessing(bool newProcessing);

public slots:
    void onGetDataClicked(const QString& address);
    void onDeleteDataClicked(const QString& address);

signals:
    void currentDataChanged();

    void processingChanged();

private slots:
    void onDataReady(ip2Data::GeolocationData data);
    void onErrorOccured();

private:
    void setEmptyValues();
    void onButtonClicked();

    GeolocationDataInfo *_currentData = nullptr;
    ip2Data::IP2DataManager* _dataManager;
    bool m_processing = false;
};
