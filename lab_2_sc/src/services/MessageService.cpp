#include "sn/services/MessageService.hpp"
#include "sn/domain/entities/messages/Message.hpp"

namespace sn::services {

MessageService::MessageService(sn::storage::repositories::IMessageRepository& repo, sn::util::Clock clock)
  : repo_(repo), clock_(clock) {}

std::string MessageService::send(const std::string& from, const std::string& to, const std::string& text) {
  const std::string id = msg_ids_.next();
  sn::domain::entities::messages::Message m(id, from, to, text, clock_.now());
  repo_.add(m);
  return id;
}

std::vector<std::string> MessageService::dialogs(const std::string& user_id) const {
  return repo_.list_dialog_partners(user_id);
}

std::vector<std::string> MessageService::messages_between(const std::string& a, const std::string& b) const {
  std::vector<std::string> out;
  for (const auto& m : repo_.list_between(a, b)) {
    out.push_back(m.text());
  }
  return out;
}

} // namespace sn::services
