#pragma once
#include <unordered_map>

#include "sn/storage/repositories/IUserRepository.hpp"

namespace sn::storage::memory {

class InMemoryUserRepository final : public sn::storage::repositories::IUserRepository {
public:
  void add_user(const sn::domain::entities::User& user) override;
  sn::domain::entities::User get_user_by_id(const std::string& id) const override;
  bool exists_user(const std::string& id) const override;
  void update_user(const sn::domain::entities::User& user) override;
  void remove_user(const std::string& id) override;

  void upsert_profile(const sn::domain::entities::Profile& profile) override;
  std::optional<sn::domain::entities::Profile> try_get_profile(const std::string& user_id) const override;

  void upsert_credentials(const sn::domain::entities::Credentials& creds) override;
  std::optional<sn::domain::entities::Credentials> try_get_credentials(const std::string& user_id) const override;

  std::vector<sn::domain::entities::User> find_by_username_prefix(const std::string& prefix) const override;

private:
  std::unordered_map<std::string, sn::domain::entities::User> users_;
  std::unordered_map<std::string, sn::domain::entities::Profile> profiles_;
  std::unordered_map<std::string, sn::domain::entities::Credentials> creds_;
};

} // namespace sn::storage::memory
