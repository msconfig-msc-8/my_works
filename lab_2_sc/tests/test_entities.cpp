#include "minitest.hpp"

#include "sn/domain/entities/User.hpp"
#include "sn/domain/entities/Profile.hpp"
#include "sn/domain/entities/Credentials.hpp"
#include "sn/domain/entities/Session.hpp"
#include "sn/domain/exceptions/Exceptions.hpp"
#include "sn/domain/value_objects/Email.hpp"
#include "sn/util/Clock.hpp"

using sn::domain::exceptions::ValidationException;

SN_TEST_CASE(User_InvalidUsername_Throws) {
  sn::util::Clock clock;
  try {
    sn::domain::entities::User u("U-1", "ab", sn::domain::value_objects::Email("a@b.com"), clock.now());
  } catch (const ValidationException&) {
    SN_REQUIRE(true);
    return;
  }
  SN_REQUIRE(false);
}

SN_TEST_CASE(User_StatusChanges) {
  sn::util::Clock clock;
  sn::domain::entities::User u("U-1", "user_01", sn::domain::value_objects::Email("a@b.com"), clock.now());
  SN_REQUIRE(u.is_active());
  u.deactivate();
  SN_REQUIRE(!u.is_active());
  u.activate();
  SN_REQUIRE(u.is_active());
}

SN_TEST_CASE(Profile_BioLimit) {
  sn::domain::entities::Profile p("U-1", "John");
  p.set_bio("hello");
  SN_REQUIRE(p.bio() == "hello");
}

SN_TEST_CASE(Session_Expired) {
  sn::util::Clock clock;
  auto now = clock.now();
  auto exp = clock.add_minutes(now, 1);
  sn::domain::entities::Session s("T-1", "U-1", exp, "DEV1");
  SN_REQUIRE(!s.is_expired(now));
  SN_REQUIRE(s.is_expired(clock.add_minutes(now, 2)));
}
