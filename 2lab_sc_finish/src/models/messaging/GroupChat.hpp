#ifndef GROUPCHAT_HPP
#define GROUPCHAT_HPP

#include <string>
#include <vector>
#include <ctime>

/**
 * @brief Класс группового чата
 */
class GroupChat {
private:
    std::string id_;
    std::string name_;
    std::string adminId_;
    std::vector<std::string> members_;
    std::time_t createdAt_;
    std::string avatarUrl_;

public:
    GroupChat(const std::string& id, const std::string& name,
              const std::string& adminId)
        : id_(id), name_(name), adminId_(adminId),
          createdAt_(std::time(nullptr)), avatarUrl_("") {
        members_.push_back(adminId);
    }

    // Getters
    const std::string& getId() const { return id_; }
    const std::string& getName() const { return name_; }
    const std::string& getAdminId() const { return adminId_; }
    const std::vector<std::string>& getMembers() const { return members_; }
    std::time_t getCreatedAt() const { return createdAt_; }
    const std::string& getAvatarUrl() const { return avatarUrl_; }
    size_t getMemberCount() const { return members_.size(); }

    bool isMember(const std::string& userId) const {
        for (const auto& m : members_) {
            if (m == userId) return true;
        }
        return false;
    }

    bool isAdmin(const std::string& userId) const {
        return adminId_ == userId;
    }

    // Methods
    void addMember(const std::string& userId) {
        if (!isMember(userId)) {
            members_.push_back(userId);
        }
    }

    void removeMember(const std::string& userId) {
        if (userId != adminId_) {
            members_.erase(
                std::remove(members_.begin(), members_.end(), userId),
                members_.end()
            );
        }
    }

    void rename(const std::string& newName) {
        name_ = newName;
    }

    void setAvatar(const std::string& avatarUrl) {
        avatarUrl_ = avatarUrl;
    }

    void transferAdmin(const std::string& newAdminId) {
        if (isMember(newAdminId)) {
            adminId_ = newAdminId;
        }
    }
};

#endif // GROUPCHAT_HPP
