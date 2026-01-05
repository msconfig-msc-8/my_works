#ifndef REPORT_HPP
#define REPORT_HPP

#include <string>
#include <ctime>

enum class ReportStatus {
    PENDING,
    UNDER_REVIEW,
    RESOLVED,
    DISMISSED
};

enum class ReportTargetType {
    USER,
    POST,
    COMMENT,
    MESSAGE,
    GROUP
};

/**
 * @brief Класс жалобы/репорта
 */
class Report {
private:
    std::string id_;
    std::string reporterId_;
    std::string targetId_;
    ReportTargetType targetType_;
    std::string reason_;
    std::string description_;
    ReportStatus status_;
    std::time_t createdAt_;
    std::time_t resolvedAt_;

public:
    Report(const std::string& id, const std::string& reporterId,
           const std::string& targetId, ReportTargetType targetType,
           const std::string& reason)
        : id_(id), reporterId_(reporterId), targetId_(targetId),
          targetType_(targetType), reason_(reason), description_(""),
          status_(ReportStatus::PENDING), createdAt_(std::time(nullptr)),
          resolvedAt_(0) {}

    // Getters
    const std::string& getId() const { return id_; }
    const std::string& getReporterId() const { return reporterId_; }
    const std::string& getTargetId() const { return targetId_; }
    ReportTargetType getTargetType() const { return targetType_; }
    const std::string& getReason() const { return reason_; }
    const std::string& getDescription() const { return description_; }
    ReportStatus getStatus() const { return status_; }
    std::time_t getCreatedAt() const { return createdAt_; }
    std::time_t getResolvedAt() const { return resolvedAt_; }

    bool isPending() const { return status_ == ReportStatus::PENDING; }
    bool isResolved() const { return status_ == ReportStatus::RESOLVED; }

    // Methods
    void setDescription(const std::string& description) {
        description_ = description;
    }

    void review() {
        status_ = ReportStatus::UNDER_REVIEW;
    }

    void resolve() {
        status_ = ReportStatus::RESOLVED;
        resolvedAt_ = std::time(nullptr);
    }

    void dismiss() {
        status_ = ReportStatus::DISMISSED;
        resolvedAt_ = std::time(nullptr);
    }

    std::string getStatusString() const {
        switch (status_) {
            case ReportStatus::PENDING: return "pending";
            case ReportStatus::UNDER_REVIEW: return "under_review";
            case ReportStatus::RESOLVED: return "resolved";
            case ReportStatus::DISMISSED: return "dismissed";
            default: return "unknown";
        }
    }

    std::string getTargetTypeString() const {
        switch (targetType_) {
            case ReportTargetType::USER: return "user";
            case ReportTargetType::POST: return "post";
            case ReportTargetType::COMMENT: return "comment";
            case ReportTargetType::MESSAGE: return "message";
            case ReportTargetType::GROUP: return "group";
            default: return "unknown";
        }
    }
};

#endif // REPORT_HPP
