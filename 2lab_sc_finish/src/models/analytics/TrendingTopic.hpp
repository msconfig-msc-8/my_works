#ifndef TRENDINGTOPIC_HPP
#define TRENDINGTOPIC_HPP

#include <string>
#include <ctime>

/**
 * @brief Класс трендовой темы
 */
class TrendingTopic {
private:
    std::string id_;
    std::string tag_;
    int score_;
    int postCount_;
    std::time_t peakTime_;
    std::string category_;

public:
    TrendingTopic(const std::string& id, const std::string& tag)
        : id_(id), tag_(tag), score_(0), postCount_(0),
          peakTime_(std::time(nullptr)), category_("") {}

    // Getters
    const std::string& getId() const { return id_; }
    const std::string& getTag() const { return tag_; }
    int getScore() const { return score_; }
    int getPostCount() const { return postCount_; }
    std::time_t getPeakTime() const { return peakTime_; }
    const std::string& getCategory() const { return category_; }

    std::string getHashtag() const {
        return "#" + tag_;
    }

    bool isHot() const {
        return score_ > 1000;
    }

    // Methods
    void calculateScore(int recentPosts, int recentEngagement) {
        const int postWeight = 10;
        const int engagementWeight = 5;
        int oldScore = score_;
        score_ = (recentPosts * postWeight) + (recentEngagement * engagementWeight);
        if (score_ > oldScore) {
            peakTime_ = std::time(nullptr);
        }
    }

    void incrementPostCount() {
        postCount_++;
    }

    void updateScore(int delta) {
        score_ += delta;
        if (score_ < 0) score_ = 0;
    }

    void setCategory(const std::string& category) {
        category_ = category;
    }

    void decay(double factor = 0.9) {
        score_ = static_cast<int>(score_ * factor);
    }
};

#endif // TRENDINGTOPIC_HPP
