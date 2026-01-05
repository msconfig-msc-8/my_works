#ifndef VIDEO_HPP
#define VIDEO_HPP

#include <string>
#include <ctime>

/**
 * @brief Класс видео
 */
class Video {
private:
    std::string id_;
    std::string authorId_;
    std::string url_;
    std::string title_;
    std::string description_;
    int duration_;
    int views_;
    std::time_t uploadedAt_;

public:
    Video(const std::string& id, const std::string& authorId,
          const std::string& url, const std::string& title, int duration)
        : id_(id), authorId_(authorId), url_(url), title_(title),
          description_(""), duration_(duration), views_(0),
          uploadedAt_(std::time(nullptr)) {}

    // Getters
    const std::string& getId() const { return id_; }
    const std::string& getAuthorId() const { return authorId_; }
    const std::string& getUrl() const { return url_; }
    const std::string& getTitle() const { return title_; }
    const std::string& getDescription() const { return description_; }
    int getDuration() const { return duration_; }
    int getViews() const { return views_; }
    std::time_t getUploadedAt() const { return uploadedAt_; }

    // Methods
    void play() {
        incrementViews();
    }

    void incrementViews() {
        views_++;
    }

    void updateTitle(const std::string& title) {
        title_ = title;
    }

    void updateDescription(const std::string& description) {
        description_ = description;
    }

    std::string getDurationFormatted() const {
        int minutes = duration_ / 60;
        int seconds = duration_ % 60;
        return std::to_string(minutes) + ":" + 
               (seconds < 10 ? "0" : "") + std::to_string(seconds);
    }
};

#endif // VIDEO_HPP
