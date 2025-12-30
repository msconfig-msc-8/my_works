#include "minitest.hpp"

#include "sn/domain/value_objects/Email.hpp"
#include "sn/domain/value_objects/Phone.hpp"
#include "sn/domain/exceptions/Exceptions.hpp"

using sn::domain::exceptions::InvalidEmailException;
using sn::domain::exceptions::InvalidPhoneException;

SN_TEST_CASE(Email_Valid) {
  sn::domain::value_objects::Email e("Test.User@Example.com");
  SN_REQUIRE(e.value() == "Test.User@Example.com");
  SN_REQUIRE(e.normalized() == "test.user@example.com");
  SN_REQUIRE(!e.is_verified());
  e.set_verified(true);
  SN_REQUIRE(e.is_verified());
}

SN_TEST_CASE(Email_Invalid_Throws) {
  try {
    sn::domain::value_objects::Email e("no-at-symbol");
  } catch (const InvalidEmailException&) {
    SN_REQUIRE(true);
    return;
  }
  SN_REQUIRE(false);
}

SN_TEST_CASE(Phone_Valid) {
  sn::domain::value_objects::Phone p("+31612345678");
  SN_REQUIRE(p.normalized() == "+31612345678");
  SN_REQUIRE(!p.is_verified());
  p.set_verified(true);
  SN_REQUIRE(p.is_verified());
}

SN_TEST_CASE(Phone_Invalid_Throws) {
  try {
    sn::domain::value_objects::Phone p("12-34");
  } catch (const InvalidPhoneException&) {
    SN_REQUIRE(true);
    return;
  }
  SN_REQUIRE(false);
}
