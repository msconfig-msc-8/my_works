#pragma once
#include <string>
#include <vector>

#include "sn/storage/repositories/IMessageRepository.hpp"
#include "sn/util/Clock.hpp"
#include "sn/util/IdGenerator.hpp"

namespace sn::services {

class MessageService {
public:
  MessageService(sn::storage::repositories::IMessageRepository& repo, sn::util::Clock clock);

  std::string send(const std::string& from, const std::string& to, const std::string& text);

  std::vector<std::string> dialogs(const std::string& user_id) const;

  std::vector<std::string> messages_between(const std::string& a, const std::string& b) const;

private:
  sn::storage::repositories::IMessageRepository& repo_;
  sn::util::Clock clock_;
  sn::util::IdGenerator msg_ids_{"M"};
};

} // namespace sn::services
