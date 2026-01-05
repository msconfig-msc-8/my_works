#ifndef PAGE_HPP
#define PAGE_HPP

#include <string>
#include <ctime>

/**
 * @brief Класс публичной страницы
 */
class Page {
private:
    std::string id_;
    std::string name_;
    std::string category_;
    std::string ownerId_;
    std::string description_;
    std::string avatarUrl_;
    std::string coverUrl_;
    int followersCount_;
    std::time_t createdAt_;
    bool isVerified_;

public:
    Page(const std::string& id, const std::string& name,
         const std::string& category, const std::string& ownerId)
        : id_(id), name_(name), category_(category), ownerId_(ownerId),
          description_(""), avatarUrl_(""), coverUrl_(""), followersCount_(0),
          createdAt_(std::time(nullptr)), isVerified_(false) {}

    // Getters
    const std::string& getId() const { return id_; }
    const std::string& getName() const { return name_; }
    const std::string& getCategory() const { return category_; }
    const std::string& getOwnerId() const { return ownerId_; }
    const std::string& getDescription() const { return description_; }
    const std::string& getAvatarUrl() const { return avatarUrl_; }
    const std::string& getCoverUrl() const { return coverUrl_; }
    int getFollowersCount() const { return followersCount_; }
    std::time_t getCreatedAt() const { return createdAt_; }
    bool isVerified() const { return isVerified_; }

    // Methods
    void update(const std::string& name, const std::string& description) {
        name_ = name;
        description_ = description;
    }

    void setAvatar(const std::string& avatarUrl) {
        avatarUrl_ = avatarUrl;
    }

    void setCover(const std::string& coverUrl) {
        coverUrl_ = coverUrl;
    }

    void incrementFollowers() {
        followersCount_++;
    }

    void decrementFollowers() {
        if (followersCount_ > 0) {
            followersCount_--;
        }
    }

    void verify() {
        isVerified_ = true;
    }

    void setCategory(const std::string& category) {
        category_ = category;
    }
};

#endif // PAGE_HPP
