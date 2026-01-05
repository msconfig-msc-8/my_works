#ifndef TWOFACTORAUTH_HPP
#define TWOFACTORAUTH_HPP

#include <string>
#include <vector>

/**
 * @brief Класс двухфакторной аутентификации
 */
class TwoFactorAuth {
private:
    std::string userId_;
    std::string secret_;
    bool isEnabled_;
    std::vector<std::string> backupCodes_;
    std::string phoneNumber_;

    std::string generateCode() const {
        std::string code;
        for (int i = 0; i < 6; i++) {
            code += std::to_string(rand() % 10);
        }
        return code;
    }

public:
    explicit TwoFactorAuth(const std::string& userId)
        : userId_(userId), secret_(""), isEnabled_(false), phoneNumber_("") {}

    // Getters
    const std::string& getUserId() const { return userId_; }
    const std::string& getSecret() const { return secret_; }
    bool isEnabled() const { return isEnabled_; }
    const std::vector<std::string>& getBackupCodes() const { return backupCodes_; }
    const std::string& getPhoneNumber() const { return phoneNumber_; }

    // Methods
    void enable(const std::string& secret) {
        secret_ = secret;
        isEnabled_ = true;
        generateBackupCodes();
    }

    void disable() {
        isEnabled_ = false;
        secret_ = "";
        backupCodes_.clear();
    }

    bool verify(const std::string& code) const {
        if (!isEnabled_) return true;
        return code == generateCode();
    }

    bool verifyBackupCode(const std::string& code) {
        for (auto it = backupCodes_.begin(); it != backupCodes_.end(); ++it) {
            if (*it == code) {
                backupCodes_.erase(it);
                return true;
            }
        }
        return false;
    }

    void generateBackupCodes() {
        backupCodes_.clear();
        const int backupCodeCount = 10;
        for (int i = 0; i < backupCodeCount; i++) {
            std::string code;
            for (int j = 0; j < 8; j++) {
                code += static_cast<char>('A' + rand() % 26);
            }
            backupCodes_.push_back(code);
        }
    }

    void setPhoneNumber(const std::string& phone) {
        phoneNumber_ = phone;
    }
};

#endif // TWOFACTORAUTH_HPP
