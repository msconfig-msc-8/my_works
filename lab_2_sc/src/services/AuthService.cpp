#include "sn/services/AuthService.hpp"

#include "sn/config/Constants.hpp"
#include "sn/domain/entities/Profile.hpp"
#include "sn/domain/entities/User.hpp"
#include "sn/domain/entities/Credentials.hpp"
#include "sn/domain/exceptions/Exceptions.hpp"
#include "sn/domain/value_objects/Email.hpp"

namespace sn::services {

using sn::domain::exceptions::AuthenticationFailedException;
using sn::domain::exceptions::ContentTooLongException;
using sn::domain::exceptions::ValidationException;

AuthService::AuthService(sn::storage::repositories::IUserRepository& users,
                         const sn::services::security::IPasswordHasher& hasher,
                         sn::util::Clock clock)
  : users_(users), hasher_(hasher), clock_(clock) {}

std::string AuthService::register_user(const std::string& username,
                                       const std::string& email,
                                       const std::string& password,
                                       const std::string& display_name) {
  if (password.size() < sn::config::kMinPasswordLength) {
    throw ValidationException("Password is too short");
  }
  if (display_name.empty() || display_name.size() > sn::config::kMaxDisplayNameLength) {
    throw ValidationException("Invalid display name");
  }

  const std::string id = user_ids_.next();
  sn::domain::entities::User user(
    id,
    username,
    sn::domain::value_objects::Email(email),
    clock_.now()
  );

  const std::string salt = hasher_.make_salt();
  const std::string hash = hasher_.hash_password(password, salt);

  sn::domain::entities::Credentials creds(id, hash, salt, clock_.now());
  sn::domain::entities::Profile profile(id, display_name);

  users_.add_user(user);
  users_.upsert_credentials(creds);
  users_.upsert_profile(profile);

  return id;
}

void AuthService::login(const std::string& user_id, const std::string& password) {
  auto creds_opt = users_.try_get_credentials(user_id);
  if (!creds_opt.has_value()) {
    throw AuthenticationFailedException("No credentials for user");
  }
  const auto& creds = creds_opt.value();
  if (!hasher_.verify(password, creds.salt(), creds.password_hash())) {
    throw AuthenticationFailedException("Wrong password");
  }
}

void AuthService::change_password(const std::string& user_id, const std::string& new_password) {
  if (new_password.size() < sn::config::kMinPasswordLength) {
    throw ValidationException("Password is too short");
  }
  auto creds_opt = users_.try_get_credentials(user_id);
  if (!creds_opt.has_value()) {
    throw AuthenticationFailedException("No credentials for user");
  }

  auto creds = creds_opt.value();
  const std::string new_salt = hasher_.make_salt();
  const std::string new_hash = hasher_.hash_password(new_password, new_salt);
  creds.set_password_hash(new_hash, new_salt, clock_.now());

  users_.upsert_credentials(creds);
}

} // namespace sn::services
