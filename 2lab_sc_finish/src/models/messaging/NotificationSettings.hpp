#ifndef NOTIFICATIONSETTINGS_HPP
#define NOTIFICATIONSETTINGS_HPP

#include <string>

/**
 * @brief Класс настроек уведомлений
 */
class NotificationSettings {
private:
    std::string userId_;
    bool emailEnabled_;
    bool pushEnabled_;
    bool soundEnabled_;
    bool vibrationEnabled_;
    bool likesEnabled_;
    bool commentsEnabled_;
    bool followsEnabled_;
    bool messagesEnabled_;

public:
    explicit NotificationSettings(const std::string& userId)
        : userId_(userId), emailEnabled_(true), pushEnabled_(true),
          soundEnabled_(true), vibrationEnabled_(true), likesEnabled_(true),
          commentsEnabled_(true), followsEnabled_(true), messagesEnabled_(true) {}

    // Getters
    const std::string& getUserId() const { return userId_; }
    bool isEmailEnabled() const { return emailEnabled_; }
    bool isPushEnabled() const { return pushEnabled_; }
    bool isSoundEnabled() const { return soundEnabled_; }
    bool isVibrationEnabled() const { return vibrationEnabled_; }
    bool isLikesEnabled() const { return likesEnabled_; }
    bool isCommentsEnabled() const { return commentsEnabled_; }
    bool isFollowsEnabled() const { return followsEnabled_; }
    bool isMessagesEnabled() const { return messagesEnabled_; }

    // Methods
    void toggleEmail() { emailEnabled_ = !emailEnabled_; }
    void togglePush() { pushEnabled_ = !pushEnabled_; }
    void toggleSound() { soundEnabled_ = !soundEnabled_; }
    void toggleVibration() { vibrationEnabled_ = !vibrationEnabled_; }
    void toggleLikes() { likesEnabled_ = !likesEnabled_; }
    void toggleComments() { commentsEnabled_ = !commentsEnabled_; }
    void toggleFollows() { followsEnabled_ = !followsEnabled_; }
    void toggleMessages() { messagesEnabled_ = !messagesEnabled_; }

    void setEmailEnabled(bool enabled) { emailEnabled_ = enabled; }
    void setPushEnabled(bool enabled) { pushEnabled_ = enabled; }

    void disableAll() {
        emailEnabled_ = false;
        pushEnabled_ = false;
        soundEnabled_ = false;
        vibrationEnabled_ = false;
    }

    void enableAll() {
        emailEnabled_ = true;
        pushEnabled_ = true;
        soundEnabled_ = true;
        vibrationEnabled_ = true;
    }
};

#endif // NOTIFICATIONSETTINGS_HPP
