#ifndef CONTENTRECOMMENDATION_HPP
#define CONTENTRECOMMENDATION_HPP

#include <string>
#include <vector>
#include <algorithm>

/**
 * @brief Класс рекомендаций контента
 */
class ContentRecommendation {
private:
    std::string userId_;
    std::vector<std::string> recommendedPostIds_;
    std::string algorithm_;
    double score_;
    std::vector<std::string> interests_;

public:
    explicit ContentRecommendation(const std::string& userId)
        : userId_(userId), algorithm_("collaborative"), score_(0.0) {}

    // Getters
    const std::string& getUserId() const { return userId_; }
    const std::vector<std::string>& getRecommendedPostIds() const { 
        return recommendedPostIds_; 
    }
    const std::string& getAlgorithm() const { return algorithm_; }
    double getScore() const { return score_; }
    const std::vector<std::string>& getInterests() const { return interests_; }

    size_t getRecommendationCount() const {
        return recommendedPostIds_.size();
    }

    // Methods
    void addRecommendation(const std::string& postId, double relevanceScore) {
        recommendedPostIds_.push_back(postId);
        score_ = (score_ + relevanceScore) / 2.0;
    }

    void removeRecommendation(const std::string& postId) {
        recommendedPostIds_.erase(
            std::remove(recommendedPostIds_.begin(), 
                       recommendedPostIds_.end(), postId),
            recommendedPostIds_.end()
        );
    }

    void clearRecommendations() {
        recommendedPostIds_.clear();
        score_ = 0.0;
    }

    void addInterest(const std::string& interest) {
        interests_.push_back(interest);
    }

    void removeInterest(const std::string& interest) {
        interests_.erase(
            std::remove(interests_.begin(), interests_.end(), interest),
            interests_.end()
        );
    }

    void setAlgorithm(const std::string& algorithm) {
        algorithm_ = algorithm;
    }

    void updatePreferences(const std::vector<std::string>& newInterests) {
        interests_ = newInterests;
    }
};

#endif // CONTENTRECOMMENDATION_HPP
