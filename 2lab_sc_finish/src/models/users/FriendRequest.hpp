#ifndef FRIENDREQUEST_HPP
#define FRIENDREQUEST_HPP

#include <string>
#include <ctime>

enum class FriendRequestStatus {
    PENDING,
    ACCEPTED,
    REJECTED,
    CANCELLED
};

/**
 * @brief Класс запроса в друзья
 */
class FriendRequest {
private:
    std::string senderId_;
    std::string receiverId_;
    FriendRequestStatus status_;
    std::time_t sentAt_;

public:
    FriendRequest(const std::string& senderId, const std::string& receiverId)
        : senderId_(senderId), receiverId_(receiverId), 
          status_(FriendRequestStatus::PENDING), sentAt_(std::time(nullptr)) {}

    // Getters
    const std::string& getSenderId() const { return senderId_; }
    const std::string& getReceiverId() const { return receiverId_; }
    FriendRequestStatus getStatus() const { return status_; }
    std::time_t getSentAt() const { return sentAt_; }

    bool isPending() const {
        return status_ == FriendRequestStatus::PENDING;
    }

    // Methods
    void accept() {
        status_ = FriendRequestStatus::ACCEPTED;
    }

    void reject() {
        status_ = FriendRequestStatus::REJECTED;
    }

    void cancel() {
        status_ = FriendRequestStatus::CANCELLED;
    }
};

#endif // FRIENDREQUEST_HPP
