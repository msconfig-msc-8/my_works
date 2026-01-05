#ifndef CHAT_HPP
#define CHAT_HPP

#include <string>
#include <vector>
#include <ctime>

/**
 * @brief Класс чата между пользователями
 */
class Chat {
private:
    std::string id_;
    std::vector<std::string> participants_;
    std::time_t createdAt_;
    std::string lastMessageId_;
    std::time_t lastMessageAt_;

public:
    Chat(const std::string& id, const std::vector<std::string>& participants)
        : id_(id), participants_(participants), createdAt_(std::time(nullptr)),
          lastMessageId_(""), lastMessageAt_(0) {}

    // Getters
    const std::string& getId() const { return id_; }
    const std::vector<std::string>& getParticipants() const { return participants_; }
    std::time_t getCreatedAt() const { return createdAt_; }
    const std::string& getLastMessageId() const { return lastMessageId_; }
    std::time_t getLastMessageAt() const { return lastMessageAt_; }

    bool hasParticipant(const std::string& userId) const {
        for (const auto& p : participants_) {
            if (p == userId) return true;
        }
        return false;
    }

    size_t getParticipantCount() const {
        return participants_.size();
    }

    // Methods
    void addMessage(const std::string& messageId) {
        lastMessageId_ = messageId;
        lastMessageAt_ = std::time(nullptr);
    }

    void addParticipant(const std::string& userId) {
        if (!hasParticipant(userId)) {
            participants_.push_back(userId);
        }
    }

    void removeParticipant(const std::string& userId) {
        participants_.erase(
            std::remove(participants_.begin(), participants_.end(), userId),
            participants_.end()
        );
    }

    std::string getOtherParticipant(const std::string& userId) const {
        for (const auto& p : participants_) {
            if (p != userId) return p;
        }
        return "";
    }
};

#endif // CHAT_HPP
