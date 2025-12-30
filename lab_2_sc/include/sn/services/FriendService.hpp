#pragma once
#include <string>
#include <vector>

#include "sn/storage/repositories/IFriendRepository.hpp"
#include "sn/util/Clock.hpp"
#include "sn/util/IdGenerator.hpp"

namespace sn::services {

class FriendService {
public:
  FriendService(sn::storage::repositories::IFriendRepository& repo, sn::util::Clock clock);

  std::string send_request(const std::string& from_user_id, const std::string& to_user_id);
  void accept_request(const std::string& request_id);
  void reject_request(const std::string& request_id);

  bool are_friends(const std::string& a, const std::string& b) const;
  std::vector<std::string> list_friends(const std::string& user_id) const;

private:
  sn::storage::repositories::IFriendRepository& repo_;
  sn::util::Clock clock_;
  sn::util::IdGenerator req_ids_{"FR"};
};

} // namespace sn::services
