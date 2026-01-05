#ifndef TAG_HPP
#define TAG_HPP

#include <string>
#include <algorithm>
#include <cctype>

/**
 * @brief Класс тега (хештега)
 */
class Tag {
private:
    std::string id_;
    std::string name_;
    int usageCount_;

    static std::string normalizeTagName(const std::string& name) {
        std::string normalized = name;
        if (!normalized.empty() && normalized[0] == '#') {
            normalized = normalized.substr(1);
        }
        std::transform(normalized.begin(), normalized.end(), 
                       normalized.begin(), ::tolower);
        return normalized;
    }

public:
    Tag(const std::string& id, const std::string& name)
        : id_(id), name_(normalizeTagName(name)), usageCount_(0) {}

    // Getters
    const std::string& getId() const { return id_; }
    const std::string& getName() const { return name_; }
    int getUsageCount() const { return usageCount_; }

    std::string getHashtag() const {
        return "#" + name_;
    }

    // Methods
    void incrementUsage() {
        usageCount_++;
    }

    void decrementUsage() {
        if (usageCount_ > 0) {
            usageCount_--;
        }
    }

    bool matchesSearch(const std::string& query) const {
        std::string normalizedQuery = normalizeTagName(query);
        return name_.find(normalizedQuery) != std::string::npos;
    }
};

#endif // TAG_HPP
