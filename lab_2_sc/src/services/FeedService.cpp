#include "sn/services/FeedService.hpp"

namespace sn::services {

FeedService::FeedService(sn::storage::repositories::IFriendRepository& friends,
                         sn::storage::repositories::IPostRepository& posts)
  : friends_(friends), posts_(posts) {}

std::vector<std::string> FeedService::feed_post_ids(const std::string& user_id) const {
  std::vector<std::string> out;
  for (const auto& fr : friends_.list_friends(user_id)) {
    for (const auto& post : posts_.list_by_author(fr)) {
      out.push_back(post.id());
    }
  }
  return out;
}

} // namespace sn::services
