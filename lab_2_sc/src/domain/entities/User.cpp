#include "sn/domain/entities/User.hpp"
#include "sn/config/Constants.hpp"
#include "sn/domain/exceptions/Exceptions.hpp"

#include <cctype>
#include <utility>

namespace sn::domain::entities {

using sn::domain::exceptions::ValidationException;

static bool is_allowed_username_char(unsigned char c) {
  return std::isalnum(c) || c == '_' || c == '.';
}

bool User::is_valid_username(std::string_view name) {
  if (name.size() < sn::config::kMinUsernameLength) return false;
  if (name.size() > sn::config::kMaxUsernameLength) return false;

  for (unsigned char c : name) {
    if (!is_allowed_username_char(c)) return false;
  }
  return true;
}

User::User(std::string id,
           std::string username,
           sn::domain::value_objects::Email email,
           time_point created_at)
  : id_(std::move(id)),
    username_(std::move(username)),
    email_(std::move(email)),
    created_at_(created_at) {
  if (id_.empty()) throw ValidationException("User id is empty");
  if (!is_valid_username(username_)) throw ValidationException("Invalid username: " + username_);
}

const std::string& User::id() const noexcept { return id_; }
const std::string& User::username() const noexcept { return username_; }
const sn::domain::value_objects::Email& User::email() const noexcept { return email_; }
const std::optional<sn::domain::value_objects::Phone>& User::phone() const noexcept { return phone_; }
User::time_point User::created_at() const noexcept { return created_at_; }

UserStatus User::status() const noexcept { return status_; }
bool User::is_active() const noexcept { return status_ == UserStatus::Active; }

void User::change_username(std::string new_username) {
  if (!is_valid_username(new_username)) {
    throw ValidationException("Invalid username: " + new_username);
  }
  username_ = std::move(new_username);
}

void User::change_email(sn::domain::value_objects::Email new_email) {
  email_ = std::move(new_email);
}

void User::set_phone(std::optional<sn::domain::value_objects::Phone> new_phone) {
  phone_ = std::move(new_phone);
}

void User::deactivate() { status_ = UserStatus::Deactivated; }
void User::activate() { status_ = UserStatus::Active; }

} // namespace sn::domain::entities
