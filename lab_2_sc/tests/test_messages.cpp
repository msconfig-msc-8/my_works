#include "minitest.hpp"

#include "sn/services/MessageService.hpp"
#include "sn/storage/memory/InMemoryMessageRepository.hpp"
#include "sn/util/Clock.hpp"
#include "sn/domain/exceptions/Exceptions.hpp"

using sn::domain::exceptions::ValidationException;

SN_TEST_CASE(Messages_SendAndListBetween) {
  sn::storage::memory::InMemoryMessageRepository repo;
  sn::util::Clock clock;
  sn::services::MessageService svc(repo, clock);

  svc.send("U-1", "U-2", "hi");
  svc.send("U-2", "U-1", "hello");

  auto msgs = svc.messages_between("U-1", "U-2");
  SN_REQUIRE(msgs.size() == 2);
}

SN_TEST_CASE(Messages_DialogPartners) {
  sn::storage::memory::InMemoryMessageRepository repo;
  sn::util::Clock clock;
  sn::services::MessageService svc(repo, clock);

  svc.send("U-1", "U-2", "hi");
  svc.send("U-1", "U-3", "yo");

  auto d = svc.dialogs("U-1");
  SN_REQUIRE(d.size() == 2);
}

SN_TEST_CASE(Messages_EmptyText_Throws) {
  sn::storage::memory::InMemoryMessageRepository repo;
  sn::util::Clock clock;
  sn::services::MessageService svc(repo, clock);

  try {
    svc.send("U-1", "U-2", "");
  } catch (const ValidationException&) {
    SN_REQUIRE(true);
    return;
  }
  SN_REQUIRE(false);
}
