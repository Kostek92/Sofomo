#include "AppController.h"

AppController::AppController(QObject *parent)
    : QObject{parent}
    , _dataManager{new ip2Data::IP2DataManager{parent}}
{
    connect(_dataManager, &ip2Data::IP2DataManager::signalDataReady, this, &AppController::onDataReady);
    connect(_dataManager, &ip2Data::IP2DataManager::signalErrorOccurred, this, &AppController::onErrorOccured);
    setCurrentData(new GeolocationDataInfo(parent));
    setEmptyValues();
}


GeolocationDataInfo *AppController::getCurrentData() const
{
    return _currentData;
}

void AppController::setCurrentData(GeolocationDataInfo *newCurrentData)
{
    if (_currentData == newCurrentData)
        return;
    _currentData = newCurrentData;
    emit currentDataChanged();
}

void AppController::onGetDataClicked(const QString &address)
{
    setEmptyValues();
    onButtonClicked();
    _dataManager->getData(address);
}

void AppController::onDeleteDataClicked(const QString &address)
{
    onButtonClicked();
    if(_dataManager->deleteData(address))
    {
        setStatusInfo("Address deleted from database");
    }
    else
    {
        setStatusInfo("Address not found in database");
    }
    setProcessing(false);
}

void AppController::onDataReady(ip2Data::GeolocationData data)
{
    setProcessing(false);
    if(!data.isEmpty())
    {
        _currentData->setIp(data.ip);
        _currentData->setCountry(data.country);
        _currentData->setCapital(data.capital);
        _currentData->setCity(data.city);
        _currentData->setLatitude(data.latitude);
        _currentData->setLongitude(data.longitude);
    }
}

void AppController::onErrorOccured()
{
    setProcessing(false);
}

void AppController::setEmptyValues()
{
    const QString emptyString = "-";
    _currentData->setIp(emptyString);
    _currentData->setCountry(emptyString);
    _currentData->setCity(emptyString);
    _currentData->setCapital(emptyString);
    _currentData->setLatitude(0.0);
    _currentData->setLongitude(0.0);
}

void AppController::onButtonClicked()
{
    setStatusInfo("");
    setProcessing(true);
}

QString AppController::statusInfo() const
{
    return m_statusInfo;
}

void AppController::setStatusInfo(const QString &newStatusInfo)
{
    if (m_statusInfo == newStatusInfo)
        return;
    m_statusInfo = newStatusInfo;
    emit statusInfoChanged();
}

bool AppController::processing() const
{
    return m_processing;
}

void AppController::setProcessing(bool newProcessing)
{
    if (m_processing == newProcessing)
        return;
    m_processing = newProcessing;
    emit processingChanged();
}
