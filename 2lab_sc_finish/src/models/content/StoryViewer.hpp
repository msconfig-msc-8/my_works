#ifndef STORYVIEWER_HPP
#define STORYVIEWER_HPP

#include <string>
#include <ctime>

/**
 * @brief Класс просмотра истории
 */
class StoryViewer {
private:
    std::string storyId_;
    std::string viewerId_;
    std::time_t viewedAt_;

public:
    StoryViewer(const std::string& storyId, const std::string& viewerId)
        : storyId_(storyId), viewerId_(viewerId), viewedAt_(std::time(nullptr)) {}

    // Getters
    const std::string& getStoryId() const { return storyId_; }
    const std::string& getViewerId() const { return viewerId_; }
    std::time_t getViewedAt() const { return viewedAt_; }

    // Methods
    void recordView() {
        viewedAt_ = std::time(nullptr);
    }

    bool hasViewed(const std::string& storyId, const std::string& viewerId) const {
        return storyId_ == storyId && viewerId_ == viewerId;
    }
};

#endif // STORYVIEWER_HPP
