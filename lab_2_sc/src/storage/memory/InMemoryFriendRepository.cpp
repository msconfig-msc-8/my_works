#include "sn/storage/memory/InMemoryFriendRepository.hpp"
#include "sn/domain/exceptions/Exceptions.hpp"

namespace sn::storage::memory {

using sn::domain::exceptions::ValidationException;
using sn::domain::exceptions::UserNotFoundException;

void InMemoryFriendRepository::add_request(const sn::domain::entities::friends::FriendRequest& req) {
  if (requests_.contains(req.id())) throw ValidationException("Request exists: " + req.id());
  requests_.emplace(req.id(), req);
}

sn::domain::entities::friends::FriendRequest
InMemoryFriendRepository::get_request_by_id(const std::string& id) const {
  auto it = requests_.find(id);
  if (it == requests_.end()) throw ValidationException("Request not found: " + id);
  return it->second;
}

void InMemoryFriendRepository::update_request(const sn::domain::entities::friends::FriendRequest& req) {
  auto it = requests_.find(req.id());
  if (it == requests_.end()) throw ValidationException("Request not found: " + req.id());
  it->second = req;
}

bool InMemoryFriendRepository::has_pending_request(const std::string& from_user_id,
                                                   const std::string& to_user_id) const {
  for (const auto& [id, req] : requests_) {
    if (req.from_user_id() == from_user_id &&
        req.to_user_id() == to_user_id &&
        req.status() == sn::domain::entities::friends::FriendRequestStatus::Pending) {
      return true;
    }
  }
  return false;
}

void InMemoryFriendRepository::add_friendship(const std::string& a, const std::string& b) {
  friends_[a].insert(b);
  friends_[b].insert(a);
}

bool InMemoryFriendRepository::are_friends(const std::string& a, const std::string& b) const {
  auto it = friends_.find(a);
  if (it == friends_.end()) return false;
  return it->second.contains(b);
}

std::vector<std::string> InMemoryFriendRepository::list_friends(const std::string& user_id) const {
  std::vector<std::string> out;
  auto it = friends_.find(user_id);
  if (it == friends_.end()) return out;
  out.assign(it->second.begin(), it->second.end());
  return out;
}

} // namespace sn::storage::memory
