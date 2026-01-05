#ifndef NOTIFICATION_HPP
#define NOTIFICATION_HPP

#include <string>
#include <ctime>

enum class NotificationType {
    LIKE,
    COMMENT,
    FOLLOW,
    FRIEND_REQUEST,
    MESSAGE,
    MENTION,
    GROUP_INVITE,
    EVENT_INVITE,
    SYSTEM
};

/**
 * @brief Класс уведомления
 */
class Notification {
private:
    std::string id_;
    std::string userId_;
    NotificationType type_;
    std::string message_;
    std::string linkId_;
    bool isRead_;
    std::time_t createdAt_;

public:
    Notification(const std::string& id, const std::string& userId,
                 NotificationType type, const std::string& message,
                 const std::string& linkId = "")
        : id_(id), userId_(userId), type_(type), message_(message),
          linkId_(linkId), isRead_(false), createdAt_(std::time(nullptr)) {}

    // Getters
    const std::string& getId() const { return id_; }
    const std::string& getUserId() const { return userId_; }
    NotificationType getType() const { return type_; }
    const std::string& getMessage() const { return message_; }
    const std::string& getLinkId() const { return linkId_; }
    bool isRead() const { return isRead_; }
    std::time_t getCreatedAt() const { return createdAt_; }

    // Methods
    void markAsRead() {
        isRead_ = true;
    }

    void dismiss() {
        isRead_ = true;
    }

    std::string getTypeString() const {
        switch (type_) {
            case NotificationType::LIKE: return "like";
            case NotificationType::COMMENT: return "comment";
            case NotificationType::FOLLOW: return "follow";
            case NotificationType::FRIEND_REQUEST: return "friend_request";
            case NotificationType::MESSAGE: return "message";
            case NotificationType::MENTION: return "mention";
            case NotificationType::GROUP_INVITE: return "group_invite";
            case NotificationType::EVENT_INVITE: return "event_invite";
            case NotificationType::SYSTEM: return "system";
            default: return "unknown";
        }
    }

    bool hasLink() const {
        return !linkId_.empty();
    }
};

#endif // NOTIFICATION_HPP
