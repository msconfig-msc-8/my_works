#pragma once
#include <string>
#include <vector>

#include "sn/storage/repositories/IFriendRepository.hpp"
#include "sn/storage/repositories/IPostRepository.hpp"

namespace sn::services {

class FeedService {
public:
  FeedService(sn::storage::repositories::IFriendRepository& friends,
              sn::storage::repositories::IPostRepository& posts);

  std::vector<std::string> feed_post_ids(const std::string& user_id) const;

private:
  sn::storage::repositories::IFriendRepository& friends_;
  sn::storage::repositories::IPostRepository& posts_;
};

} // namespace sn::services
