#ifndef BLOCKEDUSER_HPP
#define BLOCKEDUSER_HPP

#include <string>
#include <ctime>

/**
 * @brief Класс заблокированного пользователя
 */
class BlockedUser {
private:
    std::string blockerId_;
    std::string blockedId_;
    std::time_t blockedAt_;
    std::string reason_;
    bool isBlocked_;

public:
    BlockedUser(const std::string& blockerId, const std::string& blockedId,
                const std::string& reason = "")
        : blockerId_(blockerId), blockedId_(blockedId), 
          blockedAt_(std::time(nullptr)), reason_(reason), isBlocked_(true) {}

    // Getters
    const std::string& getBlockerId() const { return blockerId_; }
    const std::string& getBlockedId() const { return blockedId_; }
    std::time_t getBlockedAt() const { return blockedAt_; }
    const std::string& getReason() const { return reason_; }
    bool isUserBlocked() const { return isBlocked_; }

    // Methods
    void block(const std::string& reason = "") {
        isBlocked_ = true;
        blockedAt_ = std::time(nullptr);
        reason_ = reason;
    }

    void unblock() {
        isBlocked_ = false;
    }
};

#endif // BLOCKEDUSER_HPP
