#ifndef PAGEADMIN_HPP
#define PAGEADMIN_HPP

#include <string>
#include <ctime>

enum class PageAdminRole {
    EDITOR,
    MODERATOR,
    ADMIN
};

/**
 * @brief Класс администратора страницы
 */
class PageAdmin {
private:
    std::string pageId_;
    std::string userId_;
    PageAdminRole role_;
    std::time_t assignedAt_;

public:
    PageAdmin(const std::string& pageId, const std::string& userId,
              PageAdminRole role = PageAdminRole::EDITOR)
        : pageId_(pageId), userId_(userId), role_(role),
          assignedAt_(std::time(nullptr)) {}

    // Getters
    const std::string& getPageId() const { return pageId_; }
    const std::string& getUserId() const { return userId_; }
    PageAdminRole getRole() const { return role_; }
    std::time_t getAssignedAt() const { return assignedAt_; }

    bool isAdmin() const {
        return role_ == PageAdminRole::ADMIN;
    }

    bool canModerate() const {
        return role_ == PageAdminRole::MODERATOR || role_ == PageAdminRole::ADMIN;
    }

    bool canEdit() const {
        return true;
    }

    // Methods
    void changeRole(PageAdminRole newRole) {
        role_ = newRole;
        assignedAt_ = std::time(nullptr);
    }

    std::string getRoleString() const {
        switch (role_) {
            case PageAdminRole::ADMIN: return "admin";
            case PageAdminRole::MODERATOR: return "moderator";
            case PageAdminRole::EDITOR: return "editor";
            default: return "editor";
        }
    }
};

#endif // PAGEADMIN_HPP
