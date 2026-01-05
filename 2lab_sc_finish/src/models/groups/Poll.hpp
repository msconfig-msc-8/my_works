#ifndef POLL_HPP
#define POLL_HPP

#include <string>
#include <vector>
#include <map>
#include <ctime>

/**
 * @brief Класс опроса
 */
class Poll {
private:
    std::string id_;
    std::string question_;
    std::vector<std::string> options_;
    std::string authorId_;
    std::time_t createdAt_;
    std::time_t endsAt_;
    std::map<std::string, int> votes_;
    bool isMultipleChoice_;
    bool isAnonymous_;

public:
    Poll(const std::string& id, const std::string& question,
         const std::vector<std::string>& options, const std::string& authorId,
         std::time_t endsAt = 0)
        : id_(id), question_(question), options_(options), authorId_(authorId),
          createdAt_(std::time(nullptr)), endsAt_(endsAt),
          isMultipleChoice_(false), isAnonymous_(false) {
        for (size_t i = 0; i < options_.size(); i++) {
            votes_[std::to_string(i)] = 0;
        }
    }

    // Getters
    const std::string& getId() const { return id_; }
    const std::string& getQuestion() const { return question_; }
    const std::vector<std::string>& getOptions() const { return options_; }
    const std::string& getAuthorId() const { return authorId_; }
    std::time_t getCreatedAt() const { return createdAt_; }
    std::time_t getEndsAt() const { return endsAt_; }
    bool isMultipleChoice() const { return isMultipleChoice_; }
    bool isAnonymous() const { return isAnonymous_; }

    bool isActive() const {
        if (endsAt_ == 0) return true;
        return std::time(nullptr) < endsAt_;
    }

    int getTotalVotes() const {
        int total = 0;
        for (const auto& pair : votes_) {
            total += pair.second;
        }
        return total;
    }

    int getVotesForOption(int optionIndex) const {
        std::string key = std::to_string(optionIndex);
        auto it = votes_.find(key);
        if (it != votes_.end()) {
            return it->second;
        }
        return 0;
    }

    // Methods
    void vote(int optionIndex) {
        if (isActive() && optionIndex >= 0 && 
            optionIndex < static_cast<int>(options_.size())) {
            votes_[std::to_string(optionIndex)]++;
        }
    }

    void setMultipleChoice(bool multiple) {
        isMultipleChoice_ = multiple;
    }

    void setAnonymous(bool anonymous) {
        isAnonymous_ = anonymous;
    }

    double getPercentage(int optionIndex) const {
        int total = getTotalVotes();
        if (total == 0) return 0.0;
        return (static_cast<double>(getVotesForOption(optionIndex)) / total) * 100.0;
    }
};

#endif // POLL_HPP
