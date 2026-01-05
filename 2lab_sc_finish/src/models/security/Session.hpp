#ifndef SESSION_HPP
#define SESSION_HPP

#include <string>
#include <ctime>

/**
 * @brief Класс сессии пользователя
 */
class Session {
private:
    std::string id_;
    std::string userId_;
    std::string token_;
    std::string ipAddress_;
    std::string userAgent_;
    std::time_t createdAt_;
    std::time_t expiresAt_;
    bool isActive_;

    static const int SESSION_DURATION_DAYS = 30;

public:
    Session(const std::string& id, const std::string& userId,
            const std::string& token, const std::string& ipAddress,
            const std::string& userAgent)
        : id_(id), userId_(userId), token_(token), ipAddress_(ipAddress),
          userAgent_(userAgent), createdAt_(std::time(nullptr)), isActive_(true) {
        const int secondsInDay = 86400;
        expiresAt_ = createdAt_ + (SESSION_DURATION_DAYS * secondsInDay);
    }

    // Getters
    const std::string& getId() const { return id_; }
    const std::string& getUserId() const { return userId_; }
    const std::string& getToken() const { return token_; }
    const std::string& getIpAddress() const { return ipAddress_; }
    const std::string& getUserAgent() const { return userAgent_; }
    std::time_t getCreatedAt() const { return createdAt_; }
    std::time_t getExpiresAt() const { return expiresAt_; }
    bool isActive() const { return isActive_; }

    bool isExpired() const {
        return std::time(nullptr) > expiresAt_;
    }

    bool isValid() const {
        return isActive_ && !isExpired();
    }

    // Methods
    bool validate(const std::string& token) const {
        return isValid() && token_ == token;
    }

    void terminate() {
        isActive_ = false;
    }

    void refresh() {
        const int secondsInDay = 86400;
        expiresAt_ = std::time(nullptr) + (SESSION_DURATION_DAYS * secondsInDay);
    }

    void updateIpAddress(const std::string& ipAddress) {
        ipAddress_ = ipAddress;
    }
};

#endif // SESSION_HPP
