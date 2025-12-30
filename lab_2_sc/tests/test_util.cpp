#include "minitest.hpp"

#include "sn/config/Constants.hpp"
#include "sn/util/Clock.hpp"
#include "sn/util/IdGenerator.hpp"

#include <chrono>
#include <string>

SN_TEST_CASE(Constants_AreReasonable) {
  SN_REQUIRE(sn::config::kMaxUsernameLength >= 3);
  SN_REQUIRE(sn::config::kMaxPostLength >= 50);
  SN_REQUIRE(sn::config::kDefaultSessionMinutes > 0);
}

SN_TEST_CASE(IdGenerator_Increments) {
  sn::util::IdGenerator gen("U");
  const std::string a = gen.next();
  const std::string b = gen.next();

  SN_REQUIRE(a == "U-1");
  SN_REQUIRE(b == "U-2");
  SN_REQUIRE(gen.last_value() == 2);
}

SN_TEST_CASE(Clock_AddMinutes_Works) {
  sn::util::Clock clock;
  const auto t1 = clock.now();
  const auto t2 = clock.add_minutes(t1, 10);

  const auto diff = std::chrono::duration_cast<std::chrono::minutes>(t2 - t1).count();
  SN_REQUIRE(diff == 10);
}
