#ifndef PRIVACYSETTINGS_HPP
#define PRIVACYSETTINGS_HPP

#include <string>

enum class ProfileVisibility {
    PUBLIC,
    FRIENDS_ONLY,
    PRIVATE
};

enum class MessagePrivacy {
    EVERYONE,
    FRIENDS_ONLY,
    NOBODY
};

/**
 * @brief Класс настроек приватности
 */
class PrivacySettings {
private:
    std::string userId_;
    ProfileVisibility profileVisibility_;
    MessagePrivacy messagePrivacy_;
    bool searchable_;
    bool showActivity_;
    bool showFriendsList_;
    bool allowTagging_;

public:
    explicit PrivacySettings(const std::string& userId)
        : userId_(userId), profileVisibility_(ProfileVisibility::PUBLIC),
          messagePrivacy_(MessagePrivacy::EVERYONE), searchable_(true),
          showActivity_(true), showFriendsList_(true), allowTagging_(true) {}

    // Getters
    const std::string& getUserId() const { return userId_; }
    ProfileVisibility getProfileVisibility() const { return profileVisibility_; }
    MessagePrivacy getMessagePrivacy() const { return messagePrivacy_; }
    bool isSearchable() const { return searchable_; }
    bool isShowActivity() const { return showActivity_; }
    bool isShowFriendsList() const { return showFriendsList_; }
    bool isAllowTagging() const { return allowTagging_; }

    // Methods
    void setProfileVisibility(ProfileVisibility visibility) {
        profileVisibility_ = visibility;
    }

    void setMessagePrivacy(MessagePrivacy privacy) {
        messagePrivacy_ = privacy;
    }

    void makePrivate() {
        profileVisibility_ = ProfileVisibility::PRIVATE;
        messagePrivacy_ = MessagePrivacy::FRIENDS_ONLY;
        searchable_ = false;
        showActivity_ = false;
    }

    void makePublic() {
        profileVisibility_ = ProfileVisibility::PUBLIC;
        messagePrivacy_ = MessagePrivacy::EVERYONE;
        searchable_ = true;
        showActivity_ = true;
    }

    void toggleSearchable() { searchable_ = !searchable_; }
    void toggleShowActivity() { showActivity_ = !showActivity_; }
    void toggleShowFriendsList() { showFriendsList_ = !showFriendsList_; }
    void toggleAllowTagging() { allowTagging_ = !allowTagging_; }

    std::string getVisibilityString() const {
        switch (profileVisibility_) {
            case ProfileVisibility::PUBLIC: return "public";
            case ProfileVisibility::FRIENDS_ONLY: return "friends_only";
            case ProfileVisibility::PRIVATE: return "private";
            default: return "public";
        }
    }
};

#endif // PRIVACYSETTINGS_HPP
