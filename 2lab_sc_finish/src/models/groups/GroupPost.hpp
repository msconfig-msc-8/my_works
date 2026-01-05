#ifndef GROUPPOST_HPP
#define GROUPPOST_HPP

#include <string>
#include <ctime>

enum class GroupPostStatus {
    PENDING,
    APPROVED,
    REJECTED
};

/**
 * @brief Класс публикации в группе
 */
class GroupPost {
private:
    std::string id_;
    std::string groupId_;
    std::string authorId_;
    std::string content_;
    std::time_t createdAt_;
    GroupPostStatus status_;
    std::string imageUrl_;

public:
    GroupPost(const std::string& id, const std::string& groupId,
              const std::string& authorId, const std::string& content)
        : id_(id), groupId_(groupId), authorId_(authorId), content_(content),
          createdAt_(std::time(nullptr)), status_(GroupPostStatus::PENDING),
          imageUrl_("") {}

    // Getters
    const std::string& getId() const { return id_; }
    const std::string& getGroupId() const { return groupId_; }
    const std::string& getAuthorId() const { return authorId_; }
    const std::string& getContent() const { return content_; }
    std::time_t getCreatedAt() const { return createdAt_; }
    GroupPostStatus getStatus() const { return status_; }
    const std::string& getImageUrl() const { return imageUrl_; }

    bool isPending() const { return status_ == GroupPostStatus::PENDING; }
    bool isApproved() const { return status_ == GroupPostStatus::APPROVED; }
    bool isRejected() const { return status_ == GroupPostStatus::REJECTED; }

    // Methods
    void approve() {
        status_ = GroupPostStatus::APPROVED;
    }

    void reject() {
        status_ = GroupPostStatus::REJECTED;
    }

    void edit(const std::string& newContent) {
        content_ = newContent;
        status_ = GroupPostStatus::PENDING;
    }

    void setImage(const std::string& imageUrl) {
        imageUrl_ = imageUrl;
    }

    std::string getStatusString() const {
        switch (status_) {
            case GroupPostStatus::PENDING: return "pending";
            case GroupPostStatus::APPROVED: return "approved";
            case GroupPostStatus::REJECTED: return "rejected";
            default: return "unknown";
        }
    }
};

#endif // GROUPPOST_HPP
