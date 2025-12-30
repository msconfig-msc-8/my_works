#include "sn/domain/entities/Session.hpp"
#include "sn/domain/exceptions/Exceptions.hpp"

#include <utility>

namespace sn::domain::entities {

using sn::domain::exceptions::ValidationException;

Session::Session(std::string token, std::string user_id, time_point expires_at, std::string device_id)
  : token_(std::move(token)),
    user_id_(std::move(user_id)),
    expires_at_(expires_at),
    device_id_(std::move(device_id)) {
  if (token_.empty()) throw ValidationException("Session token is empty");
  if (user_id_.empty()) throw ValidationException("Session user_id is empty");
}

const std::string& Session::token() const noexcept { return token_; }
const std::string& Session::user_id() const noexcept { return user_id_; }
const std::string& Session::device_id() const noexcept { return device_id_; }
Session::time_point Session::expires_at() const noexcept { return expires_at_; }

bool Session::is_expired(time_point now) const noexcept {
  return now >= expires_at_;
}

void Session::refresh(time_point new_expires_at) {
  expires_at_ = new_expires_at;
}

} // namespace sn::domain::entities
