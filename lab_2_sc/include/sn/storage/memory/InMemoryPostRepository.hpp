#pragma once
#include <unordered_map>

#include "sn/storage/repositories/IPostRepository.hpp"

namespace sn::storage::memory {

class InMemoryPostRepository final : public sn::storage::repositories::IPostRepository {
public:
  void add(const sn::domain::entities::posts::Post& post) override;
  sn::domain::entities::posts::Post get_by_id(const std::string& id) const override;
  void update(const sn::domain::entities::posts::Post& post) override;
  void remove(const std::string& id) override;

  std::vector<sn::domain::entities::posts::Post> list_by_author(const std::string& author_user_id) const override;

private:
  std::unordered_map<std::string, sn::domain::entities::posts::Post> posts_;
};

} // namespace sn::storage::memory
