#ifndef MENTION_HPP
#define MENTION_HPP

#include <string>
#include <ctime>

enum class MentionContentType {
    POST,
    COMMENT,
    STORY
};

/**
 * @brief Класс упоминания пользователя
 */
class Mention {
private:
    std::string id_;
    std::string mentionerId_;
    std::string mentionedId_;
    std::string contentId_;
    MentionContentType contentType_;
    std::time_t createdAt_;

public:
    Mention(const std::string& id, const std::string& mentionerId,
            const std::string& mentionedId, const std::string& contentId,
            MentionContentType contentType)
        : id_(id), mentionerId_(mentionerId), mentionedId_(mentionedId),
          contentId_(contentId), contentType_(contentType),
          createdAt_(std::time(nullptr)) {}

    // Getters
    const std::string& getId() const { return id_; }
    const std::string& getMentionerId() const { return mentionerId_; }
    const std::string& getMentionedId() const { return mentionedId_; }
    const std::string& getContentId() const { return contentId_; }
    MentionContentType getContentType() const { return contentType_; }
    std::time_t getCreatedAt() const { return createdAt_; }

    // Methods
    bool isMentionedUser(const std::string& userId) const {
        return mentionedId_ == userId;
    }

    std::string getContentTypeString() const {
        switch (contentType_) {
            case MentionContentType::POST: return "post";
            case MentionContentType::COMMENT: return "comment";
            case MentionContentType::STORY: return "story";
            default: return "unknown";
        }
    }
};

#endif // MENTION_HPP
