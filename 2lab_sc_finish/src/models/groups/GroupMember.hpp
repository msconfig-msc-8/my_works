#ifndef GROUPMEMBER_HPP
#define GROUPMEMBER_HPP

#include <string>
#include <ctime>

enum class GroupRole {
    MEMBER,
    MODERATOR,
    ADMIN,
    OWNER
};

/**
 * @brief Класс участника группы
 */
class GroupMember {
private:
    std::string groupId_;
    std::string userId_;
    GroupRole role_;
    std::time_t joinedAt_;

public:
    GroupMember(const std::string& groupId, const std::string& userId,
                GroupRole role = GroupRole::MEMBER)
        : groupId_(groupId), userId_(userId), role_(role),
          joinedAt_(std::time(nullptr)) {}

    // Getters
    const std::string& getGroupId() const { return groupId_; }
    const std::string& getUserId() const { return userId_; }
    GroupRole getRole() const { return role_; }
    std::time_t getJoinedAt() const { return joinedAt_; }

    bool isAdmin() const {
        return role_ == GroupRole::ADMIN || role_ == GroupRole::OWNER;
    }

    bool isModerator() const {
        return role_ == GroupRole::MODERATOR || isAdmin();
    }

    bool isOwner() const {
        return role_ == GroupRole::OWNER;
    }

    // Methods
    void promote() {
        if (role_ == GroupRole::MEMBER) {
            role_ = GroupRole::MODERATOR;
        } else if (role_ == GroupRole::MODERATOR) {
            role_ = GroupRole::ADMIN;
        }
    }

    void demote() {
        if (role_ == GroupRole::ADMIN) {
            role_ = GroupRole::MODERATOR;
        } else if (role_ == GroupRole::MODERATOR) {
            role_ = GroupRole::MEMBER;
        }
    }

    void setRole(GroupRole role) {
        role_ = role;
    }

    std::string getRoleString() const {
        switch (role_) {
            case GroupRole::OWNER: return "owner";
            case GroupRole::ADMIN: return "admin";
            case GroupRole::MODERATOR: return "moderator";
            case GroupRole::MEMBER: return "member";
            default: return "member";
        }
    }
};

#endif // GROUPMEMBER_HPP
