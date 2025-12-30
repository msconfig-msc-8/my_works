#include "sn/domain/entities/friends/FriendRequest.hpp"
#include "sn/domain/exceptions/Exceptions.hpp"

#include <utility>

namespace sn::domain::entities::friends {

using sn::domain::exceptions::ValidationException;

FriendRequest::FriendRequest(std::string id,
                             std::string from_user_id,
                             std::string to_user_id,
                             time_point created_at)
  : id_(std::move(id)),
    from_user_id_(std::move(from_user_id)),
    to_user_id_(std::move(to_user_id)),
    created_at_(created_at) {
  if (id_.empty()) throw ValidationException("friend request id is empty");
  if (from_user_id_.empty() || to_user_id_.empty()) throw ValidationException("user id is empty");
  if (from_user_id_ == to_user_id_) throw ValidationException("cannot friend yourself");
}

const std::string& FriendRequest::id() const noexcept { return id_; }
const std::string& FriendRequest::from_user_id() const noexcept { return from_user_id_; }
const std::string& FriendRequest::to_user_id() const noexcept { return to_user_id_; }
FriendRequestStatus FriendRequest::status() const noexcept { return status_; }
FriendRequest::time_point FriendRequest::created_at() const noexcept { return created_at_; }

void FriendRequest::accept() { status_ = FriendRequestStatus::Accepted; }
void FriendRequest::reject() { status_ = FriendRequestStatus::Rejected; }

} // namespace sn::domain::entities::friends
