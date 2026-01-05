#ifndef LOCATION_HPP
#define LOCATION_HPP

#define _USE_MATH_DEFINES
#include <cmath>
#include <string>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/**
 * @brief Класс географической локации
 */
class Location {
private:
    double latitude_;
    double longitude_;
    std::string city_;
    std::string country_;

    static constexpr double EARTH_RADIUS_KM = 6371.0;

public:
    Location(double latitude, double longitude, 
             const std::string& city = "", const std::string& country = "")
        : latitude_(latitude), longitude_(longitude), 
          city_(city), country_(country) {}

    // Getters
    double getLatitude() const { return latitude_; }
    double getLongitude() const { return longitude_; }
    const std::string& getCity() const { return city_; }
    const std::string& getCountry() const { return country_; }

    // Methods
    double getDistance(const Location& other) const {
        double lat1Rad = latitude_ * M_PI / 180.0;
        double lat2Rad = other.latitude_ * M_PI / 180.0;
        double deltaLat = (other.latitude_ - latitude_) * M_PI / 180.0;
        double deltaLon = (other.longitude_ - longitude_) * M_PI / 180.0;

        double a = std::sin(deltaLat / 2) * std::sin(deltaLat / 2) +
                   std::cos(lat1Rad) * std::cos(lat2Rad) *
                   std::sin(deltaLon / 2) * std::sin(deltaLon / 2);
        double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));

        return EARTH_RADIUS_KM * c;
    }

    std::string formatAddress() const {
        if (city_.empty() && country_.empty()) {
            return std::to_string(latitude_) + ", " + std::to_string(longitude_);
        }
        if (city_.empty()) return country_;
        if (country_.empty()) return city_;
        return city_ + ", " + country_;
    }

    void setCity(const std::string& city) { city_ = city; }
    void setCountry(const std::string& country) { country_ = country; }
};

#endif // LOCATION_HPP
