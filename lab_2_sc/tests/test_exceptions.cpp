#include "minitest.hpp"

#include "sn/domain/exceptions/Exceptions.hpp"
#include <type_traits>

using namespace sn::domain::exceptions;

SN_TEST_CASE(Exceptions_AreCatchableByBase) {
  try {
    throw UserNotFoundException("no user");
  } catch (const SocialNetworkException&) {
    SN_REQUIRE(true);
    return;
  }
  SN_REQUIRE(false);
}

SN_TEST_CASE(Exceptions_HaveCorrectTypes) {
  // просто проверим, что наследование правильное (на уровне типов)
  SN_REQUIRE((std::is_base_of_v<SocialNetworkException, ValidationException>));
  SN_REQUIRE((std::is_base_of_v<SocialNetworkException, AuthenticationFailedException>));
  SN_REQUIRE((std::is_base_of_v<SocialNetworkException, ContentTooLongException>));
}
