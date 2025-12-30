#include "sn/domain/entities/posts/Post.hpp"
#include "sn/config/Constants.hpp"
#include "sn/domain/exceptions/Exceptions.hpp"

#include <utility>

namespace sn::domain::entities::posts {

using sn::domain::exceptions::ContentTooLongException;
using sn::domain::exceptions::ValidationException;

static void validate(const std::string& author_user_id, const std::string& content) {
  if (author_user_id.empty()) throw ValidationException("author_user_id is empty");
  if (content.empty()) throw ValidationException("content is empty");
  if (content.size() > sn::config::kMaxPostLength) throw ContentTooLongException("post content too long");
}

Post::Post(std::string id,
           std::string author_user_id,
           std::string content,
           time_point created_at)
  : id_(std::move(id)),
    author_user_id_(std::move(author_user_id)),
    content_(std::move(content)),
    created_at_(created_at) {
  if (id_.empty()) throw ValidationException("post id is empty");
  validate(author_user_id_, content_);
}

const std::string& Post::id() const noexcept { return id_; }
const std::string& Post::author_user_id() const noexcept { return author_user_id_; }
const std::string& Post::content() const noexcept { return content_; }
Post::time_point Post::created_at() const noexcept { return created_at_; }

void Post::edit(std::string new_content) {
  validate(author_user_id_, new_content);
  content_ = std::move(new_content);
}

} // namespace sn::domain::entities::posts
