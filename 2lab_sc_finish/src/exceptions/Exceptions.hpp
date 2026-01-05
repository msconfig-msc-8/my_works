#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>
#include <string>

/**
 * @file Exceptions.hpp
 * @brief Файл с определениями персональных исключений социальной сети
 * @author Студент
 * @version 1.0
 */

/**
 * @brief Базовое исключение социальной сети
 * @details Все остальные исключения наследуются от этого класса.
 *          Содержит сообщение об ошибке.
 */
class SocialNetworkException : public std::exception {
protected:
    std::string message_;  ///< Сообщение об ошибке
public:
    /**
     * @brief Конструктор исключения
     * @param msg Сообщение об ошибке
     */
    explicit SocialNetworkException(const std::string& msg) : message_(msg) {}
    
    /**
     * @brief Получить сообщение об ошибке
     * @return Строка с описанием ошибки
     */
    const char* what() const noexcept override { return message_.c_str(); }
};

/**
 * @brief Исключение: пользователь не найден
 * @details Выбрасывается при попытке доступа к несуществующему пользователю
 */
class UserNotFoundException : public SocialNetworkException {
public:
    /**
     * @brief Конструктор исключения
     * @param userId Идентификатор не найденного пользователя
     */
    explicit UserNotFoundException(const std::string& userId)
        : SocialNetworkException("User not found: " + userId) {}
};

/**
 * @brief Исключение: неверные учетные данные
 * @details Выбрасывается при неудачной аутентификации пользователя
 */
class InvalidCredentialsException : public SocialNetworkException {
public:
    /**
     * @brief Конструктор исключения
     */
    InvalidCredentialsException()
        : SocialNetworkException("Invalid username or password") {}
};

/**
 * @brief Исключение: email уже используется
 * @details Выбрасывается при попытке регистрации с existing email
 */
class DuplicateEmailException : public SocialNetworkException {
public:
    /**
     * @brief Конструктор исключения
     * @param email Email-адрес, который уже используется
     */
    explicit DuplicateEmailException(const std::string& email)
        : SocialNetworkException("Email already in use: " + email) {}
};

/**
 * @brief Исключение: пост не найден
 * @details Выбрасывается при попытке доступа к несуществующей публикации
 */
class PostNotFoundException : public SocialNetworkException {
public:
    /**
     * @brief Конструктор исключения
     * @param postId Идентификатор не найденного поста
     */
    explicit PostNotFoundException(const std::string& postId)
        : SocialNetworkException("Post not found: " + postId) {}
};

/**
 * @brief Исключение: доступ запрещён
 * @details Выбрасывается при попытке выполнить действие без достаточных прав
 */
class AccessDeniedException : public SocialNetworkException {
public:
    /**
     * @brief Конструктор исключения
     * @param reason Причина отказа в доступе
     */
    explicit AccessDeniedException(const std::string& reason = "Access denied")
        : SocialNetworkException(reason) {}
};

/**
 * @brief Исключение: сообщение не найдено
 * @details Выбрасывается при попытке доступа к несуществующему сообщению
 */
class MessageNotFoundException : public SocialNetworkException {
public:
    /**
     * @brief Конструктор исключения
     * @param messageId Идентификатор не найденного сообщения
     */
    explicit MessageNotFoundException(const std::string& messageId)
        : SocialNetworkException("Message not found: " + messageId) {}
};

/**
 * @brief Исключение: некорректный контент
 * @details Выбрасывается при попытке создать контент с недопустимыми данными
 */
class InvalidContentException : public SocialNetworkException {
public:
    /**
     * @brief Конструктор исключения
     * @param reason Причина некорректности контента
     */
    explicit InvalidContentException(const std::string& reason)
        : SocialNetworkException("Invalid content: " + reason) {}
};

/**
 * @brief Исключение: группа не найдена
 * @details Выбрасывается при попытке доступа к несуществующей группе
 */
class GroupNotFoundException : public SocialNetworkException {
public:
    /**
     * @brief Конструктор исключения
     * @param groupId Идентификатор не найденной группы
     */
    explicit GroupNotFoundException(const std::string& groupId)
        : SocialNetworkException("Group not found: " + groupId) {}
};

/**
 * @brief Исключение: пользователи уже друзья
 * @details Выбрасывается при попытке добавить в друзья уже существующего друга
 */
class AlreadyFriendsException : public SocialNetworkException {
public:
    /**
     * @brief Конструктор исключения
     */
    AlreadyFriendsException()
        : SocialNetworkException("Users are already friends") {}
};

/**
 * @brief Исключение: пользователь заблокирован
 * @details Выбрасывается при попытке взаимодействия с заблокированным пользователем
 */
class BlockedUserException : public SocialNetworkException {
public:
    /**
     * @brief Конструктор исключения
     * @param userId Идентификатор заблокированного пользователя
     */
    explicit BlockedUserException(const std::string& userId)
        : SocialNetworkException("User is blocked: " + userId) {}
};

/**
 * @brief Исключение: недостаточно средств на балансе
 * @details Выбрасывается при попытке снятия суммы, превышающей баланс
 */
class InsufficientBalanceException : public SocialNetworkException {
public:
    /**
     * @brief Конструктор исключения
     * @param required Требуемая сумма
     * @param available Доступный баланс
     */
    explicit InsufficientBalanceException(double required, double available)
        : SocialNetworkException("Insufficient balance. Required: " + 
            std::to_string(required) + ", Available: " + std::to_string(available)) {}
};

#endif // EXCEPTIONS_HPP
