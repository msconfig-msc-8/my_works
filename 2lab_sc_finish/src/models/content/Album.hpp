#ifndef ALBUM_HPP
#define ALBUM_HPP

#include <string>
#include <vector>
#include <ctime>

/**
 * @brief Класс фотоальбома
 */
class Album {
private:
    std::string id_;
    std::string ownerId_;
    std::string name_;
    std::string description_;
    std::string coverUrl_;
    std::vector<std::string> photoIds_;
    std::time_t createdAt_;
    bool isPrivate_;

public:
    Album(const std::string& id, const std::string& ownerId,
          const std::string& name, const std::string& description = "")
        : id_(id), ownerId_(ownerId), name_(name), description_(description),
          coverUrl_(""), createdAt_(std::time(nullptr)), isPrivate_(false) {}

    // Getters
    const std::string& getId() const { return id_; }
    const std::string& getOwnerId() const { return ownerId_; }
    const std::string& getName() const { return name_; }
    const std::string& getDescription() const { return description_; }
    const std::string& getCoverUrl() const { return coverUrl_; }
    const std::vector<std::string>& getPhotoIds() const { return photoIds_; }
    std::time_t getCreatedAt() const { return createdAt_; }
    bool isPrivate() const { return isPrivate_; }
    size_t getPhotoCount() const { return photoIds_.size(); }

    // Methods
    void addPhoto(const std::string& photoId) {
        photoIds_.push_back(photoId);
        if (coverUrl_.empty() && !photoIds_.empty()) {
            coverUrl_ = photoId;
        }
    }

    void removePhoto(const std::string& photoId) {
        photoIds_.erase(
            std::remove(photoIds_.begin(), photoIds_.end(), photoId),
            photoIds_.end()
        );
    }

    void updateName(const std::string& name) {
        name_ = name;
    }

    void updateDescription(const std::string& description) {
        description_ = description;
    }

    void setCover(const std::string& coverUrl) {
        coverUrl_ = coverUrl;
    }

    void setPrivate(bool isPrivate) {
        isPrivate_ = isPrivate;
    }
};

#endif // ALBUM_HPP
