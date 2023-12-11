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
    Q_PROPERTY(QString statusInfo READ statusInfo WRITE setStatusInfo NOTIFY statusInfoChanged)
    Q_PROPERTY(bool processing READ processing WRITE setProcessing NOTIFY processingChanged)

    GeolocationDataInfo *getCurrentData() const;
    void setCurrentData(GeolocationDataInfo *newCurrentData);

    QString statusInfo() const;
    void setStatusInfo(const QString &newStatusInfo);

    bool processing() const;
    void setProcessing(bool newProcessing);

public slots:
    void onGetDataClicked(const QString& address);
    void onDeleteDataClicked(const QString& address);

signals:
    void currentDataChanged();
    void statusInfoChanged();

    void processingChanged();

private slots:
    void onDataReady(ip2Data::GeolocationData data);

private:
    void setEmptyValues();
    void onButtonClicked();

    GeolocationDataInfo *_currentData = nullptr;
    ip2Data::IP2DataManager* _dataManager;
    QString m_statusInfo;
    bool m_processing = false;
};
