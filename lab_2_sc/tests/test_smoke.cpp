#include "minitest.hpp"
#include "sn/sn.hpp"
#include <string_view>

SN_TEST_CASE(VersionIsNotEmpty) {
  std::string_view v = sn::version();
  SN_REQUIRE(!v.empty());
}
