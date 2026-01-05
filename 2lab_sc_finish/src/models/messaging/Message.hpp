#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>
#include <ctime>
#include "../../exceptions/Exceptions.hpp"

/**
 * @brief Класс личного сообщения
 */
class Message {
private:
    std::string id_;
    std::string senderId_;
    std::string receiverId_;
    std::string content_;
    std::time_t sentAt_;
    bool isRead_;
    bool isDeleted_;

public:
    Message(const std::string& id, const std::string& senderId,
            const std::string& receiverId, const std::string& content)
        : id_(id), senderId_(senderId), receiverId_(receiverId),
          content_(content), sentAt_(std::time(nullptr)),
          isRead_(false), isDeleted_(false) {}

    // Getters
    const std::string& getId() const { return id_; }
    const std::string& getSenderId() const { return senderId_; }
    const std::string& getReceiverId() const { return receiverId_; }
    const std::string& getContent() const { return content_; }
    std::time_t getSentAt() const { return sentAt_; }
    bool isRead() const { return isRead_; }
    bool isDeleted() const { return isDeleted_; }

    // Methods
    void markAsRead() {
        isRead_ = true;
    }

    void deleteMessage() {
        isDeleted_ = true;
    }

    void editContent(const std::string& newContent) {
        if (newContent.empty()) {
            throw InvalidContentException("Message cannot be empty");
        }
        content_ = newContent;
    }

    bool isSentBy(const std::string& userId) const {
        return senderId_ == userId;
    }

    bool isReceivedBy(const std::string& userId) const {
        return receiverId_ == userId;
    }
};

#endif // MESSAGE_HPP
