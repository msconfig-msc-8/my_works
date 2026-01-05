#ifndef ACTIVITYLOG_HPP
#define ACTIVITYLOG_HPP

#include <string>
#include <ctime>

enum class ActivityType {
    LOGIN,
    LOGOUT,
    POST_CREATED,
    POST_EDITED,
    POST_DELETED,
    COMMENT_ADDED,
    LIKE_ADDED,
    FOLLOW,
    UNFOLLOW,
    PROFILE_UPDATED,
    SETTINGS_CHANGED
};

/**
 * @brief Класс журнала активности
 */
class ActivityLog {
private:
    std::string id_;
    std::string userId_;
    ActivityType action_;
    std::string targetId_;
    std::string details_;
    std::time_t timestamp_;

public:
    ActivityLog(const std::string& id, const std::string& userId,
                ActivityType action, const std::string& targetId = "")
        : id_(id), userId_(userId), action_(action), targetId_(targetId),
          details_(""), timestamp_(std::time(nullptr)) {}

    // Getters
    const std::string& getId() const { return id_; }
    const std::string& getUserId() const { return userId_; }
    ActivityType getAction() const { return action_; }
    const std::string& getTargetId() const { return targetId_; }
    const std::string& getDetails() const { return details_; }
    std::time_t getTimestamp() const { return timestamp_; }

    // Methods
    void setDetails(const std::string& details) {
        details_ = details;
    }

    std::string getActionString() const {
        switch (action_) {
            case ActivityType::LOGIN: return "login";
            case ActivityType::LOGOUT: return "logout";
            case ActivityType::POST_CREATED: return "post_created";
            case ActivityType::POST_EDITED: return "post_edited";
            case ActivityType::POST_DELETED: return "post_deleted";
            case ActivityType::COMMENT_ADDED: return "comment_added";
            case ActivityType::LIKE_ADDED: return "like_added";
            case ActivityType::FOLLOW: return "follow";
            case ActivityType::UNFOLLOW: return "unfollow";
            case ActivityType::PROFILE_UPDATED: return "profile_updated";
            case ActivityType::SETTINGS_CHANGED: return "settings_changed";
            default: return "unknown";
        }
    }

    bool hasTarget() const {
        return !targetId_.empty();
    }
};

#endif // ACTIVITYLOG_HPP
