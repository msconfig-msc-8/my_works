#ifndef USERSTATUS_HPP
#define USERSTATUS_HPP

#include <string>
#include <ctime>

/**
 * @brief Класс статуса пользователя
 */
class UserStatus {
private:
    std::string userId_;
    std::string statusText_;
    std::string emoji_;
    std::time_t expiresAt_;

public:
    explicit UserStatus(const std::string& userId)
        : userId_(userId), statusText_(""), emoji_(""), expiresAt_(0) {}

    // Getters
    const std::string& getUserId() const { return userId_; }
    const std::string& getStatusText() const { return statusText_; }
    const std::string& getEmoji() const { return emoji_; }
    std::time_t getExpiresAt() const { return expiresAt_; }

    bool isExpired() const {
        if (expiresAt_ == 0) return false;
        return std::time(nullptr) > expiresAt_;
    }

    bool hasStatus() const {
        return !statusText_.empty() && !isExpired();
    }

    // Methods
    void updateStatus(const std::string& text, const std::string& emoji, 
                      int durationHours = 0) {
        statusText_ = text;
        emoji_ = emoji;
        if (durationHours > 0) {
            const int secondsInHour = 3600;
            expiresAt_ = std::time(nullptr) + (durationHours * secondsInHour);
        } else {
            expiresAt_ = 0;
        }
    }

    void clearStatus() {
        statusText_ = "";
        emoji_ = "";
        expiresAt_ = 0;
    }
};

#endif // USERSTATUS_HPP
