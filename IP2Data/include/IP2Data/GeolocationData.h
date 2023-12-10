#pragma once
#include <QString>


namespace ip2Data
{
namespace{
using coordinatesType = double;
}
struct GeolocationData
{
    QString ip;
    QString country;
    QString capital;
    QString city;
    coordinatesType latitude{0.0};
    coordinatesType longitude{0.0};
    bool operator==(const GeolocationData& data) const
    {
        return (ip == data.ip
                && country == data.country
                && capital == data.capital
                && city == data.city
                && areCoordinatesSame(latitude, data.latitude)
                && areCoordinatesSame(longitude, data.longitude));
    }
    bool operator!=(const GeolocationData& data) const
    {
        return !(*this == data);
    }

private:
    static constexpr double coordinatesPrecision = 0.01;
    static bool areCoordinatesSame(coordinatesType coord1, coordinatesType coord2)
    {
        return fabs(coord1 - coord2) < coordinatesPrecision;
    }
};

}


