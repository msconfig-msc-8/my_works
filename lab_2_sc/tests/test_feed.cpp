#include "minitest.hpp"

#include "sn/services/FeedService.hpp"
#include "sn/services/PostService.hpp"
#include "sn/services/FriendService.hpp"
#include "sn/storage/memory/InMemoryPostRepository.hpp"
#include "sn/storage/memory/InMemoryFriendRepository.hpp"
#include "sn/util/Clock.hpp"

SN_TEST_CASE(Feed_ReturnsFriendsPosts) {
  sn::storage::memory::InMemoryPostRepository post_repo;
  sn::storage::memory::InMemoryFriendRepository friend_repo;
  sn::util::Clock clock;

  sn::services::PostService post_svc(post_repo, clock);
  sn::services::FriendService friend_svc(friend_repo, clock);
  sn::services::FeedService feed(friend_repo, post_repo);

  // U-1 и U-2 друзья
  auto req = friend_svc.send_request("U-1", "U-2");
  friend_svc.accept_request(req);

  // U-2 пишет 2 поста
  post_svc.create_post("U-2", "p1");
  post_svc.create_post("U-2", "p2");

  auto ids = feed.feed_post_ids("U-1");
  SN_REQUIRE(ids.size() == 2);
}
