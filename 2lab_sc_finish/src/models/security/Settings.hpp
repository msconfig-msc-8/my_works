#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <string>

enum class Theme {
    LIGHT,
    DARK,
    SYSTEM
};

/**
 * @brief Класс настроек пользователя
 */
class Settings {
private:
    std::string userId_;
    Theme theme_;
    std::string language_;
    std::string timezone_;
    bool autoPlayVideos_;
    bool showOnlineStatus_;

public:
    explicit Settings(const std::string& userId)
        : userId_(userId), theme_(Theme::SYSTEM), language_("ru"),
          timezone_("UTC"), autoPlayVideos_(true), showOnlineStatus_(true) {}

    // Getters
    const std::string& getUserId() const { return userId_; }
    Theme getTheme() const { return theme_; }
    const std::string& getLanguage() const { return language_; }
    const std::string& getTimezone() const { return timezone_; }
    bool isAutoPlayVideos() const { return autoPlayVideos_; }
    bool isShowOnlineStatus() const { return showOnlineStatus_; }

    std::string getThemeString() const {
        switch (theme_) {
            case Theme::LIGHT: return "light";
            case Theme::DARK: return "dark";
            case Theme::SYSTEM: return "system";
            default: return "system";
        }
    }

    // Methods
    void setTheme(Theme theme) {
        theme_ = theme;
    }

    void setLanguage(const std::string& language) {
        language_ = language;
    }

    void setTimezone(const std::string& timezone) {
        timezone_ = timezone;
    }

    void toggleAutoPlayVideos() {
        autoPlayVideos_ = !autoPlayVideos_;
    }

    void toggleShowOnlineStatus() {
        showOnlineStatus_ = !showOnlineStatus_;
    }

    void reset() {
        theme_ = Theme::SYSTEM;
        language_ = "ru";
        timezone_ = "UTC";
        autoPlayVideos_ = true;
        showOnlineStatus_ = true;
    }
};

#endif // SETTINGS_HPP
