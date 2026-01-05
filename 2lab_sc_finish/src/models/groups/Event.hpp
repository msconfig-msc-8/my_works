#ifndef EVENT_HPP
#define EVENT_HPP

#include <string>
#include <ctime>

/**
 * @brief Класс мероприятия/события
 */
class Event {
private:
    std::string id_;
    std::string title_;
    std::string description_;
    std::string organizerId_;
    std::time_t startDate_;
    std::time_t endDate_;
    std::string locationName_;
    double locationLat_;
    double locationLon_;
    bool isCancelled_;
    int attendeesCount_;

public:
    Event(const std::string& id, const std::string& title,
          const std::string& organizerId, std::time_t startDate, std::time_t endDate)
        : id_(id), title_(title), description_(""), organizerId_(organizerId),
          startDate_(startDate), endDate_(endDate), locationName_(""),
          locationLat_(0), locationLon_(0), isCancelled_(false), attendeesCount_(0) {}

    // Getters
    const std::string& getId() const { return id_; }
    const std::string& getTitle() const { return title_; }
    const std::string& getDescription() const { return description_; }
    const std::string& getOrganizerId() const { return organizerId_; }
    std::time_t getStartDate() const { return startDate_; }
    std::time_t getEndDate() const { return endDate_; }
    const std::string& getLocationName() const { return locationName_; }
    double getLocationLat() const { return locationLat_; }
    double getLocationLon() const { return locationLon_; }
    bool isCancelled() const { return isCancelled_; }
    int getAttendeesCount() const { return attendeesCount_; }

    bool isUpcoming() const {
        return std::time(nullptr) < startDate_ && !isCancelled_;
    }

    bool isOngoing() const {
        std::time_t now = std::time(nullptr);
        return now >= startDate_ && now <= endDate_ && !isCancelled_;
    }

    bool isPast() const {
        return std::time(nullptr) > endDate_;
    }

    // Methods
    void update(const std::string& title, const std::string& description) {
        title_ = title;
        description_ = description;
    }

    void setLocation(const std::string& name, double lat, double lon) {
        locationName_ = name;
        locationLat_ = lat;
        locationLon_ = lon;
    }

    void cancel() {
        isCancelled_ = true;
    }

    void incrementAttendees() {
        attendeesCount_++;
    }

    void decrementAttendees() {
        if (attendeesCount_ > 0) {
            attendeesCount_--;
        }
    }

    void reschedule(std::time_t newStart, std::time_t newEnd) {
        startDate_ = newStart;
        endDate_ = newEnd;
    }
};

#endif // EVENT_HPP
