#ifndef LIKE_HPP
#define LIKE_HPP

#include <string>
#include <ctime>

enum class LikeTargetType {
    POST,
    COMMENT,
    PHOTO,
    VIDEO,
    STORY
};

/**
 * @brief Класс лайка
 */
class Like {
private:
    std::string id_;
    std::string userId_;
    std::string targetId_;
    LikeTargetType targetType_;
    std::time_t createdAt_;

public:
    Like(const std::string& id, const std::string& userId,
         const std::string& targetId, LikeTargetType targetType)
        : id_(id), userId_(userId), targetId_(targetId),
          targetType_(targetType), createdAt_(std::time(nullptr)) {}

    // Getters
    const std::string& getId() const { return id_; }
    const std::string& getUserId() const { return userId_; }
    const std::string& getTargetId() const { return targetId_; }
    LikeTargetType getTargetType() const { return targetType_; }
    std::time_t getCreatedAt() const { return createdAt_; }

    // Methods
    bool matchesTarget(const std::string& targetId, LikeTargetType type) const {
        return targetId_ == targetId && targetType_ == type;
    }
};

#endif // LIKE_HPP
