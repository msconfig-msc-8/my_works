#ifndef FOLLOWER_HPP
#define FOLLOWER_HPP

#include <string>
#include <ctime>

/**
 * @brief Класс подписчика
 */
class Follower {
private:
    std::string followerId_;
    std::string followeeId_;
    std::time_t followedAt_;
    bool isActive_;

public:
    Follower(const std::string& followerId, const std::string& followeeId)
        : followerId_(followerId), followeeId_(followeeId), 
          followedAt_(std::time(nullptr)), isActive_(true) {}

    // Getters
    const std::string& getFollowerId() const { return followerId_; }
    const std::string& getFolloweeId() const { return followeeId_; }
    std::time_t getFollowedAt() const { return followedAt_; }
    bool isActive() const { return isActive_; }

    // Methods
    void follow() {
        isActive_ = true;
        followedAt_ = std::time(nullptr);
    }

    void unfollow() {
        isActive_ = false;
    }
};

#endif // FOLLOWER_HPP
