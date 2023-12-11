#pragma once
#include <QString>

#include <QObject>
#include <qqml.h>

class GeolocationDataInfo : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QString ip READ getIp WRITE setIp NOTIFY ipChanged)
    Q_PROPERTY(QString country READ getCountry WRITE setCountry NOTIFY countryChanged)
    Q_PROPERTY(QString capital READ getCapital WRITE setCapital NOTIFY capitalChanged)
    Q_PROPERTY(QString city READ getCity WRITE setCity NOTIFY cityChanged)
    Q_PROPERTY(double latitude READ getLatitude WRITE setLatitude NOTIFY latitudeChanged)
    Q_PROPERTY(double longitude READ getLongitude WRITE setLongitude NOTIFY longitudeChanged)

public:
    explicit GeolocationDataInfo(QObject *parent = nullptr);

    QString getIp() const;
    void setIp(const QString &newIp);

    QString getCountry() const;
    void setCountry(const QString &newCountry);

    QString getCapital() const;
    void setCapital(const QString &newCapital);

    QString getCity() const;
    void setCity(const QString &newCity);

    double getLatitude() const;
    void setLatitude(double newLatitude);

    double getLongitude() const;
    void setLongitude(double newLongitude);

signals:
    void ipChanged();
    void countryChanged();
    void capitalChanged();
    void cityChanged();
    void latitudeChanged();
    void longitudeChanged();

private:
    QString ip;
    QString country;
    QString capital;
    QString city;
    double latitude{0.0};
    double longitude{0.0};
};




