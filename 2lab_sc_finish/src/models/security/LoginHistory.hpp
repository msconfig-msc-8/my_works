#ifndef LOGINHISTORY_HPP
#define LOGINHISTORY_HPP

#include <string>
#include <ctime>

/**
 * @brief Класс истории входов
 */
class LoginHistory {
private:
    std::string userId_;
    std::string ipAddress_;
    std::string userAgent_;
    std::string location_;
    std::time_t loginAt_;
    bool successful_;

public:
    LoginHistory(const std::string& userId, const std::string& ipAddress,
                 const std::string& userAgent, bool successful)
        : userId_(userId), ipAddress_(ipAddress), userAgent_(userAgent),
          location_(""), loginAt_(std::time(nullptr)), successful_(successful) {}

    // Getters
    const std::string& getUserId() const { return userId_; }
    const std::string& getIpAddress() const { return ipAddress_; }
    const std::string& getUserAgent() const { return userAgent_; }
    const std::string& getLocation() const { return location_; }
    std::time_t getLoginAt() const { return loginAt_; }
    bool isSuccessful() const { return successful_; }

    // Methods
    void setLocation(const std::string& location) {
        location_ = location;
    }

    bool isSuspicious() const {
        return !successful_;
    }

    std::string getDeviceType() const {
        if (userAgent_.find("Mobile") != std::string::npos) {
            return "mobile";
        }
        if (userAgent_.find("Tablet") != std::string::npos) {
            return "tablet";
        }
        return "desktop";
    }

    std::string getBrowser() const {
        if (userAgent_.find("Chrome") != std::string::npos) return "Chrome";
        if (userAgent_.find("Firefox") != std::string::npos) return "Firefox";
        if (userAgent_.find("Safari") != std::string::npos) return "Safari";
        if (userAgent_.find("Edge") != std::string::npos) return "Edge";
        return "Unknown";
    }
};

#endif // LOGINHISTORY_HPP
