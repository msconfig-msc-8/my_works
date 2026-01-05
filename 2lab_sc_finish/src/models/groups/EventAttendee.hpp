#ifndef EVENTATTENDEE_HPP
#define EVENTATTENDEE_HPP

#include <string>
#include <ctime>

enum class AttendeeStatus {
    GOING,
    MAYBE,
    NOT_GOING,
    INVITED
};

/**
 * @brief Класс участника мероприятия
 */
class EventAttendee {
private:
    std::string eventId_;
    std::string userId_;
    AttendeeStatus status_;
    std::time_t respondedAt_;

public:
    EventAttendee(const std::string& eventId, const std::string& userId)
        : eventId_(eventId), userId_(userId), status_(AttendeeStatus::INVITED),
          respondedAt_(0) {}

    // Getters
    const std::string& getEventId() const { return eventId_; }
    const std::string& getUserId() const { return userId_; }
    AttendeeStatus getStatus() const { return status_; }
    std::time_t getRespondedAt() const { return respondedAt_; }

    bool isGoing() const { return status_ == AttendeeStatus::GOING; }
    bool isMaybe() const { return status_ == AttendeeStatus::MAYBE; }
    bool isNotGoing() const { return status_ == AttendeeStatus::NOT_GOING; }
    bool hasResponded() const { return respondedAt_ != 0; }

    // Methods
    void attend() {
        status_ = AttendeeStatus::GOING;
        respondedAt_ = std::time(nullptr);
    }

    void maybe() {
        status_ = AttendeeStatus::MAYBE;
        respondedAt_ = std::time(nullptr);
    }

    void decline() {
        status_ = AttendeeStatus::NOT_GOING;
        respondedAt_ = std::time(nullptr);
    }

    std::string getStatusString() const {
        switch (status_) {
            case AttendeeStatus::GOING: return "going";
            case AttendeeStatus::MAYBE: return "maybe";
            case AttendeeStatus::NOT_GOING: return "not_going";
            case AttendeeStatus::INVITED: return "invited";
            default: return "unknown";
        }
    }
};

#endif // EVENTATTENDEE_HPP
