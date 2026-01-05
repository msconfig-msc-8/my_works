#ifndef SEARCHHISTORY_HPP
#define SEARCHHISTORY_HPP

#include <string>
#include <vector>
#include <ctime>
#include <algorithm>

/**
 * @brief Класс истории поиска
 */
class SearchHistory {
private:
    std::string userId_;
    std::vector<std::pair<std::string, std::time_t>> searches_;
    static const size_t MAX_HISTORY_SIZE = 100;

public:
    explicit SearchHistory(const std::string& userId)
        : userId_(userId) {}

    // Getters
    const std::string& getUserId() const { return userId_; }
    
    std::vector<std::string> getRecentSearches(size_t count = 10) const {
        std::vector<std::string> recent;
        size_t limit = std::min(count, searches_.size());
        for (size_t i = searches_.size(); i > searches_.size() - limit; i--) {
            recent.push_back(searches_[i - 1].first);
        }
        return recent;
    }

    size_t getSearchCount() const {
        return searches_.size();
    }

    // Methods
    void addSearch(const std::string& query) {
        for (auto it = searches_.begin(); it != searches_.end(); ++it) {
            if (it->first == query) {
                searches_.erase(it);
                break;
            }
        }
        searches_.push_back({query, std::time(nullptr)});
        if (searches_.size() > MAX_HISTORY_SIZE) {
            searches_.erase(searches_.begin());
        }
    }

    void removeSearch(const std::string& query) {
        searches_.erase(
            std::remove_if(searches_.begin(), searches_.end(),
                [&query](const std::pair<std::string, std::time_t>& item) {
                    return item.first == query;
                }),
            searches_.end()
        );
    }

    void clearHistory() {
        searches_.clear();
    }

    std::vector<std::string> getSuggestions(const std::string& prefix) const {
        std::vector<std::string> suggestions;
        for (const auto& search : searches_) {
            if (search.first.find(prefix) == 0) {
                suggestions.push_back(search.first);
            }
        }
        return suggestions;
    }
};

#endif // SEARCHHISTORY_HPP
