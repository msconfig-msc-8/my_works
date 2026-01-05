#ifndef STORY_HPP
#define STORY_HPP

#include <string>
#include <ctime>

/**
 * @brief Класс истории (story)
 */
class Story {
private:
    std::string id_;
    std::string authorId_;
    std::string mediaUrl_;
    std::time_t createdAt_;
    std::time_t expiresAt_;
    int viewCount_;
    bool isActive_;

    static const int STORY_DURATION_HOURS = 24;

public:
    Story(const std::string& id, const std::string& authorId,
          const std::string& mediaUrl)
        : id_(id), authorId_(authorId), mediaUrl_(mediaUrl),
          createdAt_(std::time(nullptr)), viewCount_(0), isActive_(true) {
        const int secondsInHour = 3600;
        expiresAt_ = createdAt_ + (STORY_DURATION_HOURS * secondsInHour);
    }

    // Getters
    const std::string& getId() const { return id_; }
    const std::string& getAuthorId() const { return authorId_; }
    const std::string& getMediaUrl() const { return mediaUrl_; }
    std::time_t getCreatedAt() const { return createdAt_; }
    std::time_t getExpiresAt() const { return expiresAt_; }
    int getViewCount() const { return viewCount_; }
    bool isActive() const { return isActive_; }

    bool isExpired() const {
        return std::time(nullptr) > expiresAt_;
    }

    // Methods
    void view() {
        if (!isExpired() && isActive_) {
            viewCount_++;
        }
    }

    void expire() {
        isActive_ = false;
    }

    void deleteStory() {
        isActive_ = false;
    }

    int getTimeRemainingSeconds() const {
        if (isExpired()) return 0;
        return static_cast<int>(expiresAt_ - std::time(nullptr));
    }
};

#endif // STORY_HPP
