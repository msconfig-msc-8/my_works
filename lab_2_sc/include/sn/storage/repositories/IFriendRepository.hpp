#pragma once
#include <string>
#include <vector>

#include "sn/domain/entities/friends/FriendRequest.hpp"

namespace sn::storage::repositories {

class IFriendRepository {
public:
  virtual ~IFriendRepository() = default;

  virtual void add_request(const sn::domain::entities::friends::FriendRequest& req) = 0;
  virtual sn::domain::entities::friends::FriendRequest get_request_by_id(const std::string& id) const = 0;
  virtual void update_request(const sn::domain::entities::friends::FriendRequest& req) = 0;

  virtual bool has_pending_request(const std::string& from_user_id, const std::string& to_user_id) const = 0;

  virtual void add_friendship(const std::string& a, const std::string& b) = 0;
  virtual bool are_friends(const std::string& a, const std::string& b) const = 0;
  virtual std::vector<std::string> list_friends(const std::string& user_id) const = 0;
};

} // namespace sn::storage::repositories
