#ifndef CHATMEMBER_HPP
#define CHATMEMBER_HPP

#include <string>
#include <ctime>

enum class ChatRole {
    MEMBER,
    MODERATOR,
    ADMIN
};

/**
 * @brief Класс участника чата
 */
class ChatMember {
private:
    std::string chatId_;
    std::string userId_;
    std::time_t joinedAt_;
    ChatRole role_;
    bool isMuted_;

public:
    ChatMember(const std::string& chatId, const std::string& userId,
               ChatRole role = ChatRole::MEMBER)
        : chatId_(chatId), userId_(userId), joinedAt_(std::time(nullptr)),
          role_(role), isMuted_(false) {}

    // Getters
    const std::string& getChatId() const { return chatId_; }
    const std::string& getUserId() const { return userId_; }
    std::time_t getJoinedAt() const { return joinedAt_; }
    ChatRole getRole() const { return role_; }
    bool isMuted() const { return isMuted_; }

    bool isAdmin() const {
        return role_ == ChatRole::ADMIN;
    }

    bool isModerator() const {
        return role_ == ChatRole::MODERATOR || role_ == ChatRole::ADMIN;
    }

    // Methods
    void updateRole(ChatRole newRole) {
        role_ = newRole;
    }

    void mute() {
        isMuted_ = true;
    }

    void unmute() {
        isMuted_ = false;
    }

    std::string getRoleString() const {
        switch (role_) {
            case ChatRole::ADMIN: return "admin";
            case ChatRole::MODERATOR: return "moderator";
            case ChatRole::MEMBER: return "member";
            default: return "member";
        }
    }
};

#endif // CHATMEMBER_HPP
