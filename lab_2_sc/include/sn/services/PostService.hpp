#pragma once
#include <string>
#include <vector>

#include "sn/storage/repositories/IPostRepository.hpp"
#include "sn/util/Clock.hpp"
#include "sn/util/IdGenerator.hpp"

namespace sn::services {

class PostService {
public:
  PostService(sn::storage::repositories::IPostRepository& posts, sn::util::Clock clock);

  std::string create_post(const std::string& author_user_id, const std::string& content);
  std::vector<std::string> list_post_ids_by_author(const std::string& author_user_id) const;
  void delete_post(const std::string& post_id);

private:
  sn::storage::repositories::IPostRepository& posts_;
  sn::util::Clock clock_;
  sn::util::IdGenerator post_ids_{"P"};
};

} // namespace sn::services
