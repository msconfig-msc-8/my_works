#include "sn/storage/memory/InMemoryPostRepository.hpp"
#include "sn/domain/exceptions/Exceptions.hpp"

namespace sn::storage::memory {

using sn::domain::exceptions::PostNotFoundException;
using sn::domain::exceptions::ValidationException;

void InMemoryPostRepository::add(const sn::domain::entities::posts::Post& post) {
  if (posts_.contains(post.id())) {
    throw ValidationException("Post already exists: " + post.id());
  }
  posts_.emplace(post.id(), post);
}

sn::domain::entities::posts::Post InMemoryPostRepository::get_by_id(const std::string& id) const {
  auto it = posts_.find(id);
  if (it == posts_.end()) throw PostNotFoundException("Post not found: " + id);
  return it->second;
}

void InMemoryPostRepository::update(const sn::domain::entities::posts::Post& post) {
  auto it = posts_.find(post.id());
  if (it == posts_.end()) throw PostNotFoundException("Post not found: " + post.id());
  it->second = post;
}

void InMemoryPostRepository::remove(const std::string& id) {
  auto it = posts_.find(id);
  if (it == posts_.end()) throw PostNotFoundException("Post not found: " + id);
  posts_.erase(it);
}

std::vector<sn::domain::entities::posts::Post>
InMemoryPostRepository::list_by_author(const std::string& author_user_id) const {
  std::vector<sn::domain::entities::posts::Post> out;
  for (const auto& [id, post] : posts_) {
    if (post.author_user_id() == author_user_id) out.push_back(post);
  }
  return out;
}

} // namespace sn::storage::memory
