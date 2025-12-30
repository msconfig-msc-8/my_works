#include "sn/services/PostService.hpp"
#include "sn/domain/entities/posts/Post.hpp"

namespace sn::services {

PostService::PostService(sn::storage::repositories::IPostRepository& posts, sn::util::Clock clock)
  : posts_(posts), clock_(clock) {}

std::string PostService::create_post(const std::string& author_user_id, const std::string& content) {
  const std::string id = post_ids_.next();
  sn::domain::entities::posts::Post p(id, author_user_id, content, clock_.now());
  posts_.add(p);
  return id;
}

std::vector<std::string> PostService::list_post_ids_by_author(const std::string& author_user_id) const {
  std::vector<std::string> ids;
  for (const auto& post : posts_.list_by_author(author_user_id)) {
    ids.push_back(post.id());
  }
  return ids;
}

void PostService::delete_post(const std::string& post_id) {
  posts_.remove(post_id);
}

} // namespace sn::services
