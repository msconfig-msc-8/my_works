#ifndef PROFILE_HPP
#define PROFILE_HPP

#include <string>
#include <ctime>

/**
 * @brief Класс профиля пользователя
 */
class Profile {
private:
    std::string userId_;
    std::string firstName_;
    std::string lastName_;
    std::string bio_;
    std::string avatarUrl_;
    std::string coverUrl_;
    std::time_t birthDate_;

public:
    Profile(const std::string& userId, const std::string& firstName, 
            const std::string& lastName)
        : userId_(userId), firstName_(firstName), lastName_(lastName),
          bio_(""), avatarUrl_(""), coverUrl_(""), birthDate_(0) {}

    // Getters
    const std::string& getUserId() const { return userId_; }
    const std::string& getFirstName() const { return firstName_; }
    const std::string& getLastName() const { return lastName_; }
    const std::string& getBio() const { return bio_; }
    const std::string& getAvatarUrl() const { return avatarUrl_; }
    const std::string& getCoverUrl() const { return coverUrl_; }
    std::time_t getBirthDate() const { return birthDate_; }

    std::string getFullName() const {
        return firstName_ + " " + lastName_;
    }

    int getAge() const {
        if (birthDate_ == 0) return 0;
        std::time_t now = std::time(nullptr);
        const int secondsInYear = 31536000;
        return static_cast<int>((now - birthDate_) / secondsInYear);
    }

    // Setters/Updaters
    void updateBio(const std::string& bio) {
        bio_ = bio;
    }

    void updateAvatar(const std::string& avatarUrl) {
        avatarUrl_ = avatarUrl;
    }

    void updateCover(const std::string& coverUrl) {
        coverUrl_ = coverUrl;
    }

    void updateName(const std::string& firstName, const std::string& lastName) {
        firstName_ = firstName;
        lastName_ = lastName;
    }

    void setBirthDate(std::time_t birthDate) {
        birthDate_ = birthDate;
    }
};

#endif // PROFILE_HPP
