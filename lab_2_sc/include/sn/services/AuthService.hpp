#pragma once
#include <string>

#include "sn/services/security/IPasswordHasher.hpp"
#include "sn/storage/repositories/IUserRepository.hpp"
#include "sn/util/Clock.hpp"
#include "sn/util/IdGenerator.hpp"

namespace sn::services {

class AuthService {
public:
  AuthService(sn::storage::repositories::IUserRepository& users,
              const sn::services::security::IPasswordHasher& hasher,
              sn::util::Clock clock);

  // регистрируем нового пользователя: User + Profile + Credentials
  std::string register_user(const std::string& username,
                            const std::string& email,
                            const std::string& password,
                            const std::string& display_name);

  // логин: проверка пароля
  void login(const std::string& user_id, const std::string& password);

  // смена пароля
  void change_password(const std::string& user_id, const std::string& new_password);

private:
  sn::storage::repositories::IUserRepository& users_;
  const sn::services::security::IPasswordHasher& hasher_;
  sn::util::Clock clock_;
  sn::util::IdGenerator user_ids_{"U"};
};

} // namespace sn::services
