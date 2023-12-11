#include "GeolocationDataInfo.h"


GeolocationDataInfo::GeolocationDataInfo(QObject *parent)
    : QObject{parent}
{

}

QString GeolocationDataInfo::getIp() const
{
    return ip;
}

void GeolocationDataInfo::setIp(const QString &newIp)
{
    if (ip == newIp)
        return;
    ip = newIp;
    emit ipChanged();
}

QString GeolocationDataInfo::getCountry() const
{
    return country;
}

void GeolocationDataInfo::setCountry(const QString &newCountry)
{
    if (country == newCountry)
        return;
    country = newCountry;
    emit countryChanged();
}

QString GeolocationDataInfo::getCapital() const
{
    return capital;
}

void GeolocationDataInfo::setCapital(const QString &newCapital)
{
    if (capital == newCapital)
        return;
    capital = newCapital;
    emit capitalChanged();
}

QString GeolocationDataInfo::getCity() const
{
    return city;
}

void GeolocationDataInfo::setCity(const QString &newCity)
{
    if (city == newCity)
        return;
    city = newCity;
    emit cityChanged();
}

double GeolocationDataInfo::getLatitude() const
{
    return latitude;
}

void GeolocationDataInfo::setLatitude(double newLatitude)
{
    if (qFuzzyCompare(latitude, newLatitude))
        return;
    latitude = newLatitude;
    emit latitudeChanged();
}

double GeolocationDataInfo::getLongitude() const
{
    return longitude;
}

void GeolocationDataInfo::setLongitude(double newLongitude)
{
    if (qFuzzyCompare(longitude, newLongitude))
        return;
    longitude = newLongitude;
    emit longitudeChanged();
}
