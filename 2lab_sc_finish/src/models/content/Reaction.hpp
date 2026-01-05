#ifndef REACTION_HPP
#define REACTION_HPP

#include <string>
#include <ctime>

enum class ReactionType {
    LIKE,
    LOVE,
    HAHA,
    WOW,
    SAD,
    ANGRY
};

/**
 * @brief Класс реакции на контент
 */
class Reaction {
private:
    std::string id_;
    std::string userId_;
    std::string contentId_;
    ReactionType type_;
    std::time_t createdAt_;

public:
    Reaction(const std::string& id, const std::string& userId,
             const std::string& contentId, ReactionType type)
        : id_(id), userId_(userId), contentId_(contentId),
          type_(type), createdAt_(std::time(nullptr)) {}

    // Getters
    const std::string& getId() const { return id_; }
    const std::string& getUserId() const { return userId_; }
    const std::string& getContentId() const { return contentId_; }
    ReactionType getType() const { return type_; }
    std::time_t getCreatedAt() const { return createdAt_; }

    // Methods
    void changeType(ReactionType newType) {
        type_ = newType;
        createdAt_ = std::time(nullptr);
    }

    std::string getTypeString() const {
        switch (type_) {
            case ReactionType::LIKE: return "like";
            case ReactionType::LOVE: return "love";
            case ReactionType::HAHA: return "haha";
            case ReactionType::WOW: return "wow";
            case ReactionType::SAD: return "sad";
            case ReactionType::ANGRY: return "angry";
            default: return "unknown";
        }
    }

    std::string getEmoji() const {
        switch (type_) {
            case ReactionType::LIKE: return "👍";
            case ReactionType::LOVE: return "❤️";
            case ReactionType::HAHA: return "😂";
            case ReactionType::WOW: return "😮";
            case ReactionType::SAD: return "😢";
            case ReactionType::ANGRY: return "😠";
            default: return "👍";
        }
    }
};

#endif // REACTION_HPP
