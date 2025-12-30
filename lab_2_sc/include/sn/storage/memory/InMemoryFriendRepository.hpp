#pragma once
#include <unordered_map>
#include <unordered_set>

#include "sn/storage/repositories/IFriendRepository.hpp"

namespace sn::storage::memory {

class InMemoryFriendRepository final : public sn::storage::repositories::IFriendRepository {
public:
  void add_request(const sn::domain::entities::friends::FriendRequest& req) override;
  sn::domain::entities::friends::FriendRequest get_request_by_id(const std::string& id) const override;
  void update_request(const sn::domain::entities::friends::FriendRequest& req) override;

  bool has_pending_request(const std::string& from_user_id, const std::string& to_user_id) const override;

  void add_friendship(const std::string& a, const std::string& b) override;
  bool are_friends(const std::string& a, const std::string& b) const override;
  std::vector<std::string> list_friends(const std::string& user_id) const override;

private:
  std::unordered_map<std::string, sn::domain::entities::friends::FriendRequest> requests_;
  std::unordered_map<std::string, std::unordered_set<std::string>> friends_;
};

} // namespace sn::storage::memory
