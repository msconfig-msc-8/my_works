#ifndef VOICEMESSAGE_HPP
#define VOICEMESSAGE_HPP

#include <string>
#include <ctime>

/**
 * @brief Класс голосового сообщения
 */
class VoiceMessage {
private:
    std::string id_;
    std::string senderId_;
    std::string chatId_;
    std::string audioUrl_;
    int duration_;
    bool isListened_;
    std::time_t createdAt_;

public:
    VoiceMessage(const std::string& id, const std::string& senderId,
                 const std::string& chatId, const std::string& audioUrl,
                 int duration)
        : id_(id), senderId_(senderId), chatId_(chatId),
          audioUrl_(audioUrl), duration_(duration),
          isListened_(false), createdAt_(std::time(nullptr)) {}

    // Getters
    const std::string& getId() const { return id_; }
    const std::string& getSenderId() const { return senderId_; }
    const std::string& getChatId() const { return chatId_; }
    const std::string& getAudioUrl() const { return audioUrl_; }
    int getDuration() const { return duration_; }
    bool isListened() const { return isListened_; }
    std::time_t getCreatedAt() const { return createdAt_; }

    // Methods
    void play() {
        markListened();
    }

    void markListened() {
        isListened_ = true;
    }

    std::string getDurationFormatted() const {
        int minutes = duration_ / 60;
        int seconds = duration_ % 60;
        return std::to_string(minutes) + ":" +
               (seconds < 10 ? "0" : "") + std::to_string(seconds);
    }
};

#endif // VOICEMESSAGE_HPP
