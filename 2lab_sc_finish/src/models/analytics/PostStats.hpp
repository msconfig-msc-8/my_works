#ifndef POSTSTATS_HPP
#define POSTSTATS_HPP

#include <string>

/**
 * @brief Класс статистики публикации
 */
class PostStats {
private:
    std::string postId_;
    int likesCount_;
    int commentsCount_;
    int sharesCount_;
    int views_;
    int saves_;

public:
    explicit PostStats(const std::string& postId)
        : postId_(postId), likesCount_(0), commentsCount_(0),
          sharesCount_(0), views_(0), saves_(0) {}

    // Getters
    const std::string& getPostId() const { return postId_; }
    int getLikesCount() const { return likesCount_; }
    int getCommentsCount() const { return commentsCount_; }
    int getSharesCount() const { return sharesCount_; }
    int getViews() const { return views_; }
    int getSaves() const { return saves_; }

    int getTotalEngagement() const {
        return likesCount_ + commentsCount_ + sharesCount_ + saves_;
    }

    double getEngagementRate() const {
        if (views_ == 0) return 0.0;
        return (static_cast<double>(getTotalEngagement()) / views_) * 100.0;
    }

    // Methods
    void incrementLikes() { likesCount_++; }
    void decrementLikes() { if (likesCount_ > 0) likesCount_--; }
    void incrementComments() { commentsCount_++; }
    void decrementComments() { if (commentsCount_ > 0) commentsCount_--; }
    void incrementShares() { sharesCount_++; }
    void incrementViews() { views_++; }
    void incrementSaves() { saves_++; }
    void decrementSaves() { if (saves_ > 0) saves_--; }

    void reset() {
        likesCount_ = 0;
        commentsCount_ = 0;
        sharesCount_ = 0;
        views_ = 0;
        saves_ = 0;
    }
};

#endif // POSTSTATS_HPP
