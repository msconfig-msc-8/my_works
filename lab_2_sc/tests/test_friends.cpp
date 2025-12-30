#include "minitest.hpp"

#include "sn/services/FriendService.hpp"
#include "sn/storage/memory/InMemoryFriendRepository.hpp"
#include "sn/domain/exceptions/Exceptions.hpp"
#include "sn/util/Clock.hpp"

using sn::domain::exceptions::DuplicateFriendRequestException;

SN_TEST_CASE(Friends_SendAccept) {
  sn::storage::memory::InMemoryFriendRepository repo;
  sn::util::Clock clock;
  sn::services::FriendService svc(repo, clock);

  const std::string req = svc.send_request("U-1", "U-2");
  svc.accept_request(req);

  SN_REQUIRE(svc.are_friends("U-1", "U-2"));
  auto f = svc.list_friends("U-1");
  SN_REQUIRE(!f.empty());
}

SN_TEST_CASE(Friends_DuplicatePending_Throws) {
  sn::storage::memory::InMemoryFriendRepository repo;
  sn::util::Clock clock;
  sn::services::FriendService svc(repo, clock);

  svc.send_request("U-1", "U-2");

  try {
    svc.send_request("U-1", "U-2");
  } catch (const DuplicateFriendRequestException&) {
    SN_REQUIRE(true);
    return;
  }
  SN_REQUIRE(false);
}
