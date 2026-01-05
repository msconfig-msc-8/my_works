#ifndef COMMENT_HPP
#define COMMENT_HPP

#include <string>
#include <ctime>
#include "../../exceptions/Exceptions.hpp"

/**
 * @brief Класс комментария к публикации
 */
class Comment {
private:
    std::string id_;
    std::string postId_;
    std::string authorId_;
    std::string text_;
    std::string parentId_;
    std::time_t createdAt_;
    bool isEdited_;
    bool isDeleted_;

public:
    Comment(const std::string& id, const std::string& postId,
            const std::string& authorId, const std::string& text,
            const std::string& parentId = "")
        : id_(id), postId_(postId), authorId_(authorId), text_(text),
          parentId_(parentId), createdAt_(std::time(nullptr)),
          isEdited_(false), isDeleted_(false) {}

    // Getters
    const std::string& getId() const { return id_; }
    const std::string& getPostId() const { return postId_; }
    const std::string& getAuthorId() const { return authorId_; }
    const std::string& getText() const { return text_; }
    const std::string& getParentId() const { return parentId_; }
    std::time_t getCreatedAt() const { return createdAt_; }
    bool isEdited() const { return isEdited_; }
    bool isDeleted() const { return isDeleted_; }
    bool isReply() const { return !parentId_.empty(); }

    // Methods
    void edit(const std::string& newText) {
        if (newText.empty()) {
            throw InvalidContentException("Comment text cannot be empty");
        }
        text_ = newText;
        isEdited_ = true;
    }

    void deleteComment() {
        isDeleted_ = true;
    }

    void restore() {
        isDeleted_ = false;
    }
};

#endif // COMMENT_HPP
