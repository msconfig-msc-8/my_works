#ifndef SHARE_HPP
#define SHARE_HPP

#include <string>
#include <ctime>

/**
 * @brief Класс репоста/шеринга публикации
 */
class Share {
private:
    std::string id_;
    std::string userId_;
    std::string postId_;
    std::time_t sharedAt_;
    std::string message_;

public:
    Share(const std::string& id, const std::string& userId,
          const std::string& postId, const std::string& message = "")
        : id_(id), userId_(userId), postId_(postId),
          sharedAt_(std::time(nullptr)), message_(message) {}

    // Getters
    const std::string& getId() const { return id_; }
    const std::string& getUserId() const { return userId_; }
    const std::string& getPostId() const { return postId_; }
    std::time_t getSharedAt() const { return sharedAt_; }
    const std::string& getMessage() const { return message_; }

    // Methods
    void updateMessage(const std::string& newMessage) {
        message_ = newMessage;
    }

    bool hasMessage() const {
        return !message_.empty();
    }
};

#endif // SHARE_HPP
