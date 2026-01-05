#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <ctime>
#include "../../exceptions/Exceptions.hpp"

class Profile;
class Settings;

/**
 * @file User.hpp
 * @brief Определение класса User
 */

/**
 * @brief Класс пользователя социальной сети
 * @details Содержит основные данные учётной записи пользователя,
 *          включая логин, email, хеш пароля и статус онлайн.
 * 
 * @par Пример использования:
 * @code
 * User user("1", "ivan", "ivan@example.com", "hash123");
 * user.authenticate("hash123");
 * if (user.isOnline()) {
 *     // Пользователь онлайн
 * }
 * user.logout();
 * @endcode
 * 
 * @see Profile
 * @see Settings
 */
class User {
private:
    std::string id_;           ///< Уникальный идентификатор пользователя
    std::string username_;     ///< Имя пользователя (логин)
    std::string email_;        ///< Email адрес
    std::string passwordHash_; ///< Хеш пароля
    std::time_t createdAt_;    ///< Дата создания аккаунта
    bool isOnline_;            ///< Статус онлайн

public:
    /**
     * @brief Конструктор пользователя
     * @param id Уникальный идентификатор
     * @param username Имя пользователя
     * @param email Email адрес
     * @param passwordHash Хеш пароля
     */
    User(const std::string& id, const std::string& username, 
         const std::string& email, const std::string& passwordHash)
        : id_(id), username_(username), email_(email), 
          passwordHash_(passwordHash), createdAt_(std::time(nullptr)), isOnline_(false) {}

    /**
     * @brief Получить ID пользователя
     * @return Константная ссылка на ID
     */
    const std::string& getId() const { return id_; }
    
    /**
     * @brief Получить имя пользователя
     * @return Константная ссылка на username
     */
    const std::string& getUsername() const { return username_; }
    
    /**
     * @brief Получить email пользователя
     * @return Константная ссылка на email
     */
    const std::string& getEmail() const { return email_; }
    
    /**
     * @brief Получить дату создания аккаунта
     * @return Время создания в формате time_t
     */
    std::time_t getCreatedAt() const { return createdAt_; }
    
    /**
     * @brief Проверить, онлайн ли пользователь
     * @return true если пользователь онлайн, false иначе
     */
    bool isOnline() const { return isOnline_; }

    /**
     * @brief Аутентификация пользователя
     * @param passwordHash Хеш введённого пароля
     * @return true при успешной аутентификации
     * @throws InvalidCredentialsException При неверном пароле
     * 
     * @par Пример:
     * @code
     * try {
     *     user.authenticate("correctHash");
     * } catch (const InvalidCredentialsException& e) {
     *     std::cout << "Неверный пароль" << std::endl;
     * }
     * @endcode
     */
    bool authenticate(const std::string& passwordHash) {
        if (passwordHash != passwordHash_) {
            throw InvalidCredentialsException();
        }
        isOnline_ = true;
        return true;
    }

    /**
     * @brief Выход из системы
     * @details Устанавливает статус пользователя в offline
     */
    void logout() {
        isOnline_ = false;
    }

    /**
     * @brief Обновить статус онлайн
     * @param online Новый статус
     */
    void updateStatus(bool online) {
        isOnline_ = online;
    }

    /**
     * @brief Обновить email пользователя
     * @param newEmail Новый email адрес
     */
    void updateEmail(const std::string& newEmail) {
        email_ = newEmail;
    }

    /**
     * @brief Обновить хеш пароля
     * @param newHash Новый хеш пароля
     */
    void updatePasswordHash(const std::string& newHash) {
        passwordHash_ = newHash;
    }
};

#endif // USER_HPP
