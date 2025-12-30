#pragma once
#include <optional>
#include <string>
#include <vector>

#include "sn/domain/entities/User.hpp"
#include "sn/domain/entities/Profile.hpp"
#include "sn/domain/entities/Credentials.hpp"

namespace sn::storage::repositories {

class IUserRepository {
public:
  virtual ~IUserRepository() = default;

  // User
  virtual void add_user(const sn::domain::entities::User& user) = 0;
  virtual sn::domain::entities::User get_user_by_id(const std::string& id) const = 0;
  virtual bool exists_user(const std::string& id) const = 0;
  virtual void update_user(const sn::domain::entities::User& user) = 0;
  virtual void remove_user(const std::string& id) = 0;

  // Profile
  virtual void upsert_profile(const sn::domain::entities::Profile& profile) = 0;
  virtual std::optional<sn::domain::entities::Profile> try_get_profile(const std::string& user_id) const = 0;

  // Credentials
  virtual void upsert_credentials(const sn::domain::entities::Credentials& creds) = 0;
  virtual std::optional<sn::domain::entities::Credentials> try_get_credentials(const std::string& user_id) const = 0;

  // search (для будущего сервиса)
  virtual std::vector<sn::domain::entities::User> find_by_username_prefix(const std::string& prefix) const = 0;
};

} // namespace sn::storage::repositories
