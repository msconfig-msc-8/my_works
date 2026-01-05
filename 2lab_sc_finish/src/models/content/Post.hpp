#ifndef POST_HPP
#define POST_HPP

#include <string>
#include <vector>
#include <ctime>
#include "../../exceptions/Exceptions.hpp"

/**
 * @file Post.hpp
 * @brief Определение класса Post для публикаций
 */

/**
 * @brief Класс публикации (поста)
 * @details Представляет публикацию пользователя в социальной сети.
 *          Содержит текст, изображения, дату создания и настройки видимости.
 * 
 * @par Пример использования:
 * @code
 * Post post("1", "user1", "Привет, мир!");
 * post.setImageUrl("http://example.com/image.jpg");
 * post.edit("Обновлённый текст");
 * 
 * if (!post.isDeleted()) {
 *     std::cout << post.getContent() << std::endl;
 * }
 * @endcode
 * 
 * @see Comment
 * @see Like
 */
class Post {
private:
    std::string id_;        ///< Уникальный идентификатор поста
    std::string authorId_;  ///< ID автора
    std::string content_;   ///< Текстовое содержимое
    std::string imageUrl_;  ///< URL прикреплённого изображения
    std::time_t createdAt_; ///< Дата создания
    std::time_t updatedAt_; ///< Дата последнего обновления
    bool isPublic_;         ///< Публичный ли пост
    bool isDeleted_;        ///< Удалён ли пост

public:
    /**
     * @brief Конструктор поста
     * @param id Уникальный идентификатор
     * @param authorId ID автора
     * @param content Текст публикации
     * @param isPublic Публичный ли пост (по умолчанию true)
     */
    Post(const std::string& id, const std::string& authorId, 
         const std::string& content, bool isPublic = true)
        : id_(id), authorId_(authorId), content_(content), imageUrl_(""),
          createdAt_(std::time(nullptr)), updatedAt_(std::time(nullptr)),
          isPublic_(isPublic), isDeleted_(false) {}

    /// @name Геттеры
    /// @{
    
    /**
     * @brief Получить ID поста
     * @return Константная ссылка на ID
     */
    const std::string& getId() const { return id_; }
    
    /**
     * @brief Получить ID автора
     * @return Константная ссылка на ID автора
     */
    const std::string& getAuthorId() const { return authorId_; }
    
    /**
     * @brief Получить текст поста
     * @return Константная ссылка на содержимое
     */
    const std::string& getContent() const { return content_; }
    
    /**
     * @brief Получить URL изображения
     * @return Константная ссылка на URL
     */
    const std::string& getImageUrl() const { return imageUrl_; }
    
    /**
     * @brief Получить дату создания
     * @return Время создания в формате time_t
     */
    std::time_t getCreatedAt() const { return createdAt_; }
    
    /**
     * @brief Получить дату обновления
     * @return Время обновления в формате time_t
     */
    std::time_t getUpdatedAt() const { return updatedAt_; }
    
    /**
     * @brief Проверить публичность поста
     * @return true если пост публичный
     */
    bool isPublic() const { return isPublic_; }
    
    /**
     * @brief Проверить, удалён ли пост
     * @return true если пост удалён
     */
    bool isDeleted() const { return isDeleted_; }
    
    /// @}

    /// @name Методы изменения
    /// @{
    
    /**
     * @brief Редактировать текст поста
     * @param newContent Новый текст
     * @throws PostNotFoundException Если пост удалён
     * @throws InvalidContentException Если новый текст пустой
     */
    void edit(const std::string& newContent) {
        if (isDeleted_) {
            throw PostNotFoundException(id_);
        }
        if (newContent.empty()) {
            throw InvalidContentException("Post content cannot be empty");
        }
        content_ = newContent;
        updatedAt_ = std::time(nullptr);
    }

    /**
     * @brief Установить URL изображения
     * @param url URL изображения
     */
    void setImageUrl(const std::string& url) {
        imageUrl_ = url;
        updatedAt_ = std::time(nullptr);
    }

    /**
     * @brief Удалить пост (мягкое удаление)
     */
    void deletePost() {
        isDeleted_ = true;
    }

    /**
     * @brief Изменить видимость поста
     * @param isPublic true для публичного, false для приватного
     */
    void setVisibility(bool isPublic) {
        isPublic_ = isPublic;
    }

    /**
     * @brief Восстановить удалённый пост
     */
    void restore() {
        isDeleted_ = false;
    }
    
    /// @}
};

#endif // POST_HPP
