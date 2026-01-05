#ifndef FRIENDLIST_HPP
#define FRIENDLIST_HPP

#include <string>
#include <vector>
#include <algorithm>
#include "../../exceptions/Exceptions.hpp"

/**
 * @brief Класс списка друзей пользователя
 */
class FriendList {
private:
    std::string ownerId_;
    std::vector<std::string> friends_;
    std::vector<std::string> pendingRequests_;

public:
    explicit FriendList(const std::string& ownerId)
        : ownerId_(ownerId) {}

    // Getters
    const std::string& getOwnerId() const { return ownerId_; }
    const std::vector<std::string>& getFriends() const { return friends_; }
    const std::vector<std::string>& getPendingRequests() const { return pendingRequests_; }
    size_t getFriendsCount() const { return friends_.size(); }

    bool isFriend(const std::string& userId) const {
        return std::find(friends_.begin(), friends_.end(), userId) != friends_.end();
    }

    bool hasPendingRequest(const std::string& userId) const {
        auto it = std::find(pendingRequests_.begin(), pendingRequests_.end(), userId);
        return it != pendingRequests_.end();
    }

    // Methods
    void addFriend(const std::string& userId) {
        if (isFriend(userId)) {
            throw AlreadyFriendsException();
        }
        friends_.push_back(userId);
    }

    void removeFriend(const std::string& userId) {
        auto it = std::find(friends_.begin(), friends_.end(), userId);
        if (it != friends_.end()) {
            friends_.erase(it);
        }
    }

    void addPendingRequest(const std::string& userId) {
        if (!hasPendingRequest(userId)) {
            pendingRequests_.push_back(userId);
        }
    }

    void acceptRequest(const std::string& userId) {
        auto it = std::find(pendingRequests_.begin(), pendingRequests_.end(), userId);
        if (it != pendingRequests_.end()) {
            pendingRequests_.erase(it);
            addFriend(userId);
        }
    }

    void rejectRequest(const std::string& userId) {
        auto it = std::find(pendingRequests_.begin(), pendingRequests_.end(), userId);
        if (it != pendingRequests_.end()) {
            pendingRequests_.erase(it);
        }
    }
};

#endif // FRIENDLIST_HPP
