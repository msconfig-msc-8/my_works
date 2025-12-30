#include "minitest.hpp"

#include "sn/services/PostService.hpp"
#include "sn/storage/memory/InMemoryPostRepository.hpp"
#include "sn/domain/exceptions/Exceptions.hpp"
#include "sn/util/Clock.hpp"

using sn::domain::exceptions::PostNotFoundException;
using sn::domain::exceptions::ContentTooLongException;

SN_TEST_CASE(Posts_CreateAndList) {
  sn::storage::memory::InMemoryPostRepository repo;
  sn::util::Clock clock;
  sn::services::PostService svc(repo, clock);

  const std::string a = svc.create_post("U-1", "Hello");
  const std::string b = svc.create_post("U-1", "World");

  auto ids = svc.list_post_ids_by_author("U-1");
  SN_REQUIRE(ids.size() == 2);
}

SN_TEST_CASE(Posts_DeleteThenNotFound) {
  sn::storage::memory::InMemoryPostRepository repo;
  sn::util::Clock clock;
  sn::services::PostService svc(repo, clock);

  const std::string id = svc.create_post("U-1", "Hello");
  svc.delete_post(id);

  try {
    repo.get_by_id(id);
  } catch (const PostNotFoundException&) {
    SN_REQUIRE(true);
    return;
  }
  SN_REQUIRE(false);
}

SN_TEST_CASE(Posts_TooLong_Throws) {
  sn::storage::memory::InMemoryPostRepository repo;
  sn::util::Clock clock;
  sn::services::PostService svc(repo, clock);

  std::string long_text(1000, 'a');
  try {
    svc.create_post("U-1", long_text);
  } catch (const ContentTooLongException&) {
    SN_REQUIRE(true);
    return;
  }
  SN_REQUIRE(false);
}
