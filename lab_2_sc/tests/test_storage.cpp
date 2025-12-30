#include "minitest.hpp"

#include "sn/storage/memory/InMemoryUserRepository.hpp"
#include "sn/domain/entities/User.hpp"
#include "sn/domain/value_objects/Email.hpp"
#include "sn/util/Clock.hpp"
#include "sn/domain/exceptions/Exceptions.hpp"

using sn::domain::exceptions::UserNotFoundException;
using sn::domain::exceptions::ValidationException;

SN_TEST_CASE(UserRepo_AddGetUpdateRemove) {
  sn::storage::memory::InMemoryUserRepository repo;
  sn::util::Clock clock;

  sn::domain::entities::User u("U-1", "user_01",
    sn::domain::value_objects::Email("a@b.com"), clock.now());

  repo.add_user(u);
  SN_REQUIRE(repo.exists_user("U-1"));

  auto got = repo.get_user_by_id("U-1");
  SN_REQUIRE(got.username() == "user_01");

  u.change_username("user_02");
  repo.update_user(u);

  auto got2 = repo.get_user_by_id("U-1");
  SN_REQUIRE(got2.username() == "user_02");

  repo.remove_user("U-1");
  SN_REQUIRE(!repo.exists_user("U-1"));
}

SN_TEST_CASE(UserRepo_GetMissing_Throws) {
  sn::storage::memory::InMemoryUserRepository repo;
  try {
    repo.get_user_by_id("NOPE");
  } catch (const UserNotFoundException&) {
    SN_REQUIRE(true);
    return;
  }
  SN_REQUIRE(false);
}

SN_TEST_CASE(UserRepo_AddDuplicate_Throws) {
  sn::storage::memory::InMemoryUserRepository repo;
  sn::util::Clock clock;

  sn::domain::entities::User u("U-1", "user_01",
    sn::domain::value_objects::Email("a@b.com"), clock.now());

  repo.add_user(u);
  try {
    repo.add_user(u);
  } catch (const ValidationException&) {
    SN_REQUIRE(true);
    return;
  }
  SN_REQUIRE(false);
}
