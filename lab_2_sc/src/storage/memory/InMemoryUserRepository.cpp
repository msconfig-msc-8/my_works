#include "sn/storage/memory/InMemoryUserRepository.hpp"
#include "sn/domain/exceptions/Exceptions.hpp"

namespace sn::storage::memory {

using sn::domain::exceptions::UserNotFoundException;
using sn::domain::exceptions::ValidationException;

void InMemoryUserRepository::add_user(const sn::domain::entities::User& user) {
  if (users_.contains(user.id())) {
    throw ValidationException("User already exists: " + user.id());
  }
  users_.emplace(user.id(), user);
}

sn::domain::entities::User InMemoryUserRepository::get_user_by_id(const std::string& id) const {
  auto it = users_.find(id);
  if (it == users_.end()) {
    throw UserNotFoundException("User not found: " + id);
  }
  return it->second;
}

bool InMemoryUserRepository::exists_user(const std::string& id) const {
  return users_.find(id) != users_.end();
}

void InMemoryUserRepository::update_user(const sn::domain::entities::User& user) {
  auto it = users_.find(user.id());
  if (it == users_.end()) {
    throw UserNotFoundException("User not found: " + user.id());
  }
  it->second = user;
}

void InMemoryUserRepository::remove_user(const std::string& id) {
  auto it = users_.find(id);
  if (it == users_.end()) {
    throw UserNotFoundException("User not found: " + id);
  }
  users_.erase(it);
  profiles_.erase(id);
  creds_.erase(id);
}

void InMemoryUserRepository::upsert_profile(const sn::domain::entities::Profile& profile) {
  profiles_.insert_or_assign(profile.user_id(), profile);

}

std::optional<sn::domain::entities::Profile>
InMemoryUserRepository::try_get_profile(const std::string& user_id) const {
  auto it = profiles_.find(user_id);
  if (it == profiles_.end()) return std::nullopt;
  return it->second;
}

void InMemoryUserRepository::upsert_credentials(const sn::domain::entities::Credentials& creds) {
  creds_.insert_or_assign(creds.user_id(), creds);

}

std::optional<sn::domain::entities::Credentials>
InMemoryUserRepository::try_get_credentials(const std::string& user_id) const {
  auto it = creds_.find(user_id);
  if (it == creds_.end()) return std::nullopt;
  return it->second;
}

std::vector<sn::domain::entities::User>
InMemoryUserRepository::find_by_username_prefix(const std::string& prefix) const {
  std::vector<sn::domain::entities::User> out;
  for (const auto& [id, user] : users_) {
    if (user.username().rfind(prefix, 0) == 0) { // starts_with
      out.push_back(user);
    }
  }
  return out;
}

} // namespace sn::storage::memory
