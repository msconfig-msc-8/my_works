#ifndef PHOTO_HPP
#define PHOTO_HPP

#include <string>
#include <ctime>

/**
 * @brief Класс фотографии
 */
class Photo {
private:
    std::string id_;
    std::string albumId_;
    std::string url_;
    std::string caption_;
    std::time_t uploadedAt_;
    int width_;
    int height_;

public:
    Photo(const std::string& id, const std::string& albumId,
          const std::string& url, const std::string& caption = "")
        : id_(id), albumId_(albumId), url_(url), caption_(caption),
          uploadedAt_(std::time(nullptr)), width_(0), height_(0) {}

    // Getters
    const std::string& getId() const { return id_; }
    const std::string& getAlbumId() const { return albumId_; }
    const std::string& getUrl() const { return url_; }
    const std::string& getCaption() const { return caption_; }
    std::time_t getUploadedAt() const { return uploadedAt_; }
    int getWidth() const { return width_; }
    int getHeight() const { return height_; }

    // Methods
    void updateCaption(const std::string& caption) {
        caption_ = caption;
    }

    void setDimensions(int width, int height) {
        width_ = width;
        height_ = height;
    }

    bool hasCaption() const {
        return !caption_.empty();
    }

    std::string getAspectRatio() const {
        if (width_ == 0 || height_ == 0) return "unknown";
        if (width_ == height_) return "1:1";
        if (width_ > height_) return "landscape";
        return "portrait";
    }
};

#endif // PHOTO_HPP
