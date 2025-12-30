#include "minitest.hpp"

#include "sn/services/AuthService.hpp"
#include "sn/services/security/SimplePasswordHasher.hpp"
#include "sn/storage/memory/InMemoryUserRepository.hpp"
#include "sn/domain/exceptions/Exceptions.hpp"

using sn::domain::exceptions::AuthenticationFailedException;
using sn::domain::exceptions::ValidationException;

SN_TEST_CASE(Auth_Register_CreatesUserAndCreds) {
  sn::storage::memory::InMemoryUserRepository repo;
  sn::services::security::SimplePasswordHasher hasher;
  sn::util::Clock clock;
  sn::services::AuthService auth(repo, hasher, clock);

  const std::string user_id = auth.register_user("user_01", "a@b.com", "password1", "John");
  SN_REQUIRE(repo.exists_user(user_id));
  SN_REQUIRE(repo.try_get_credentials(user_id).has_value());
  SN_REQUIRE(repo.try_get_profile(user_id).has_value());
}

SN_TEST_CASE(Auth_Login_WrongPassword_Throws) {
  sn::storage::memory::InMemoryUserRepository repo;
  sn::services::security::SimplePasswordHasher hasher;
  sn::util::Clock clock;
  sn::services::AuthService auth(repo, hasher, clock);

  const std::string user_id = auth.register_user("user_01", "a@b.com", "password1", "John");

  try {
    auth.login(user_id, "badpass");
  } catch (const AuthenticationFailedException&) {
    SN_REQUIRE(true);
    return;
  }
  SN_REQUIRE(false);
}

SN_TEST_CASE(Auth_ChangePassword_ThenLoginWorks) {
  sn::storage::memory::InMemoryUserRepository repo;
  sn::services::security::SimplePasswordHasher hasher;
  sn::util::Clock clock;
  sn::services::AuthService auth(repo, hasher, clock);

  const std::string user_id = auth.register_user("user_01", "a@b.com", "password1", "John");

  auth.change_password(user_id, "password2");
  auth.login(user_id, "password2");
}
