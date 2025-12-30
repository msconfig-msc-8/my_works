#pragma once
#include <string>
#include <vector>

#include "sn/domain/entities/posts/Post.hpp"

namespace sn::storage::repositories {

class IPostRepository {
public:
  virtual ~IPostRepository() = default;

  virtual void add(const sn::domain::entities::posts::Post& post) = 0;
  virtual sn::domain::entities::posts::Post get_by_id(const std::string& id) const = 0;
  virtual void update(const sn::domain::entities::posts::Post& post) = 0;
  virtual void remove(const std::string& id) = 0;

  virtual std::vector<sn::domain::entities::posts::Post> list_by_author(const std::string& author_user_id) const = 0;
};

} // namespace sn::storage::repositories
