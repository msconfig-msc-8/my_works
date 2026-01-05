#ifndef GROUP_HPP
#define GROUP_HPP

#include <string>
#include <vector>
#include <ctime>
#include "../../exceptions/Exceptions.hpp"

/**
 * @brief Класс группы/сообщества
 */
class Group {
private:
    std::string id_;
    std::string name_;
    std::string description_;
    std::string ownerId_;
    bool isPrivate_;
    std::time_t createdAt_;
    std::string avatarUrl_;
    std::vector<std::string> memberIds_;

public:
    Group(const std::string& id, const std::string& name,
          const std::string& ownerId, bool isPrivate = false)
        : id_(id), name_(name), description_(""), ownerId_(ownerId),
          isPrivate_(isPrivate), createdAt_(std::time(nullptr)), avatarUrl_("") {
        memberIds_.push_back(ownerId);
    }

    // Getters
    const std::string& getId() const { return id_; }
    const std::string& getName() const { return name_; }
    const std::string& getDescription() const { return description_; }
    const std::string& getOwnerId() const { return ownerId_; }
    bool isPrivate() const { return isPrivate_; }
    std::time_t getCreatedAt() const { return createdAt_; }
    const std::string& getAvatarUrl() const { return avatarUrl_; }
    const std::vector<std::string>& getMemberIds() const { return memberIds_; }
    size_t getMemberCount() const { return memberIds_.size(); }

    bool isMember(const std::string& userId) const {
        for (const auto& m : memberIds_) {
            if (m == userId) return true;
        }
        return false;
    }

    bool isOwner(const std::string& userId) const {
        return ownerId_ == userId;
    }

    // Methods
    void update(const std::string& name, const std::string& description) {
        name_ = name;
        description_ = description;
    }

    void addMember(const std::string& userId) {
        if (!isMember(userId)) {
            memberIds_.push_back(userId);
        }
    }

    void removeMember(const std::string& userId) {
        if (userId != ownerId_) {
            memberIds_.erase(
                std::remove(memberIds_.begin(), memberIds_.end(), userId),
                memberIds_.end()
            );
        }
    }

    void setPrivate(bool isPrivate) {
        isPrivate_ = isPrivate;
    }

    void setAvatar(const std::string& avatarUrl) {
        avatarUrl_ = avatarUrl;
    }

    void transferOwnership(const std::string& newOwnerId) {
        if (isMember(newOwnerId)) {
            ownerId_ = newOwnerId;
        }
    }
};

#endif // GROUP_HPP
