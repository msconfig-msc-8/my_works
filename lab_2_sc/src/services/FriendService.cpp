#include "sn/services/FriendService.hpp"
#include "sn/domain/exceptions/Exceptions.hpp"

namespace sn::services {

using sn::domain::exceptions::DuplicateFriendRequestException;

FriendService::FriendService(sn::storage::repositories::IFriendRepository& repo, sn::util::Clock clock)
  : repo_(repo), clock_(clock) {}

std::string FriendService::send_request(const std::string& from_user_id, const std::string& to_user_id) {
  if (repo_.has_pending_request(from_user_id, to_user_id)) {
    throw DuplicateFriendRequestException("Request already pending");
  }
  const std::string id = req_ids_.next();
  sn::domain::entities::friends::FriendRequest req(id, from_user_id, to_user_id, clock_.now());
  repo_.add_request(req);
  return id;
}

void FriendService::accept_request(const std::string& request_id) {
  auto req = repo_.get_request_by_id(request_id);
  req.accept();
  repo_.update_request(req);
  repo_.add_friendship(req.from_user_id(), req.to_user_id());
}

void FriendService::reject_request(const std::string& request_id) {
  auto req = repo_.get_request_by_id(request_id);
  req.reject();
  repo_.update_request(req);
}

bool FriendService::are_friends(const std::string& a, const std::string& b) const {
  return repo_.are_friends(a, b);
}

std::vector<std::string> FriendService::list_friends(const std::string& user_id) const {
  return repo_.list_friends(user_id);
}

} // namespace sn::services
