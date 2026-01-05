#ifndef ADVERTISEMENT_HPP
#define ADVERTISEMENT_HPP

#include <string>
#include <vector>
#include <ctime>

enum class AdStatus {
    DRAFT,
    PENDING_REVIEW,
    ACTIVE,
    PAUSED,
    COMPLETED,
    REJECTED
};

/**
 * @brief Класс рекламного объявления
 */
class Advertisement {
private:
    std::string id_;
    std::string advertiserId_;
    std::string content_;
    std::string imageUrl_;
    std::string targetUrl_;
    std::vector<std::string> targetAudience_;
    double budget_;
    double spent_;
    int impressions_;
    int clicks_;
    AdStatus status_;
    std::time_t startDate_;
    std::time_t endDate_;

public:
    Advertisement(const std::string& id, const std::string& advertiserId,
                  const std::string& content, double budget)
        : id_(id), advertiserId_(advertiserId), content_(content),
          imageUrl_(""), targetUrl_(""), budget_(budget), spent_(0),
          impressions_(0), clicks_(0), status_(AdStatus::DRAFT),
          startDate_(0), endDate_(0) {}

    // Getters
    const std::string& getId() const { return id_; }
    const std::string& getAdvertiserId() const { return advertiserId_; }
    const std::string& getContent() const { return content_; }
    const std::string& getImageUrl() const { return imageUrl_; }
    const std::string& getTargetUrl() const { return targetUrl_; }
    const std::vector<std::string>& getTargetAudience() const { return targetAudience_; }
    double getBudget() const { return budget_; }
    double getSpent() const { return spent_; }
    int getImpressions() const { return impressions_; }
    int getClicks() const { return clicks_; }
    AdStatus getStatus() const { return status_; }

    double getRemainingBudget() const { return budget_ - spent_; }
    
    double getClickThroughRate() const {
        if (impressions_ == 0) return 0.0;
        return (static_cast<double>(clicks_) / impressions_) * 100.0;
    }

    double getCostPerClick() const {
        if (clicks_ == 0) return 0.0;
        return spent_ / clicks_;
    }

    bool isActive() const { return status_ == AdStatus::ACTIVE; }

    // Methods
    void display() {
        if (isActive() && getRemainingBudget() > 0) {
            impressions_++;
        }
    }

    void trackClick(double costPerClick) {
        clicks_++;
        spent_ += costPerClick;
        if (spent_ >= budget_) {
            status_ = AdStatus::COMPLETED;
        }
    }

    void activate() { status_ = AdStatus::ACTIVE; }
    void pause() { status_ = AdStatus::PAUSED; }
    void submit() { status_ = AdStatus::PENDING_REVIEW; }

    void setImage(const std::string& imageUrl) { imageUrl_ = imageUrl; }
    void setTargetUrl(const std::string& url) { targetUrl_ = url; }
    
    void addTargetAudience(const std::string& audience) {
        targetAudience_.push_back(audience);
    }

    void setSchedule(std::time_t start, std::time_t end) {
        startDate_ = start;
        endDate_ = end;
    }
};

#endif // ADVERTISEMENT_HPP
