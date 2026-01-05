#ifndef ATTACHMENT_HPP
#define ATTACHMENT_HPP

#include <string>
#include <ctime>

enum class AttachmentType {
    IMAGE,
    VIDEO,
    AUDIO,
    DOCUMENT,
    OTHER
};

/**
 * @brief Класс вложения к сообщению
 */
class Attachment {
private:
    std::string id_;
    std::string messageId_;
    std::string fileUrl_;
    AttachmentType fileType_;
    std::string fileName_;
    size_t fileSize_;
    std::time_t uploadedAt_;

public:
    Attachment(const std::string& id, const std::string& messageId,
               const std::string& fileUrl, AttachmentType fileType,
               const std::string& fileName, size_t fileSize)
        : id_(id), messageId_(messageId), fileUrl_(fileUrl),
          fileType_(fileType), fileName_(fileName), fileSize_(fileSize),
          uploadedAt_(std::time(nullptr)) {}

    // Getters
    const std::string& getId() const { return id_; }
    const std::string& getMessageId() const { return messageId_; }
    const std::string& getFileUrl() const { return fileUrl_; }
    AttachmentType getFileType() const { return fileType_; }
    const std::string& getFileName() const { return fileName_; }
    size_t getFileSize() const { return fileSize_; }
    std::time_t getUploadedAt() const { return uploadedAt_; }

    // Methods
    std::string getFileSizeFormatted() const {
        const size_t KB = 1024;
        const size_t MB = KB * 1024;
        const size_t GB = MB * 1024;

        if (fileSize_ >= GB) {
            return std::to_string(fileSize_ / GB) + " GB";
        } else if (fileSize_ >= MB) {
            return std::to_string(fileSize_ / MB) + " MB";
        } else if (fileSize_ >= KB) {
            return std::to_string(fileSize_ / KB) + " KB";
        }
        return std::to_string(fileSize_) + " B";
    }

    std::string getFileTypeString() const {
        switch (fileType_) {
            case AttachmentType::IMAGE: return "image";
            case AttachmentType::VIDEO: return "video";
            case AttachmentType::AUDIO: return "audio";
            case AttachmentType::DOCUMENT: return "document";
            default: return "other";
        }
    }

    bool isMedia() const {
        return fileType_ == AttachmentType::IMAGE ||
               fileType_ == AttachmentType::VIDEO ||
               fileType_ == AttachmentType::AUDIO;
    }
};

#endif // ATTACHMENT_HPP
