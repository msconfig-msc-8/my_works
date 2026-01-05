#ifndef PROFILESTATS_HPP
#define PROFILESTATS_HPP

#include <string>

/**
 * @brief Класс статистики профиля
 */
class ProfileStats {
private:
    std::string userId_;
    int postsCount_;
    int followersCount_;
    int followingCount_;
    int likesReceived_;
    int commentsReceived_;

public:
    explicit ProfileStats(const std::string& userId)
        : userId_(userId), postsCount_(0), followersCount_(0),
          followingCount_(0), likesReceived_(0), commentsReceived_(0) {}

    // Getters
    const std::string& getUserId() const { return userId_; }
    int getPostsCount() const { return postsCount_; }
    int getFollowersCount() const { return followersCount_; }
    int getFollowingCount() const { return followingCount_; }
    int getLikesReceived() const { return likesReceived_; }
    int getCommentsReceived() const { return commentsReceived_; }

    double getEngagementRate() const {
        if (followersCount_ == 0) return 0.0;
        int totalEngagement = likesReceived_ + commentsReceived_;
        return (static_cast<double>(totalEngagement) / followersCount_) * 100.0;
    }

    double getFollowerRatio() const {
        if (followingCount_ == 0) return 0.0;
        return static_cast<double>(followersCount_) / followingCount_;
    }

    // Methods
    void incrementPosts() { postsCount_++; }
    void decrementPosts() { if (postsCount_ > 0) postsCount_--; }
    void incrementFollowers() { followersCount_++; }
    void decrementFollowers() { if (followersCount_ > 0) followersCount_--; }
    void incrementFollowing() { followingCount_++; }
    void decrementFollowing() { if (followingCount_ > 0) followingCount_--; }
    void incrementLikes() { likesReceived_++; }
    void incrementComments() { commentsReceived_++; }

    void updateStats(int posts, int followers, int following) {
        postsCount_ = posts;
        followersCount_ = followers;
        followingCount_ = following;
    }
};

#endif // PROFILESTATS_HPP
