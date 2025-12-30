#pragma once
#include <string>
#include <vector>

#include "sn/domain/entities/messages/Message.hpp"

namespace sn::storage::repositories {

class IMessageRepository {
public:
  virtual ~IMessageRepository() = default;

  virtual void add(const sn::domain::entities::messages::Message& m) = 0;

  virtual std::vector<sn::domain::entities::messages::Message>
  list_between(const std::string& a, const std::string& b) const = 0;

  virtual std::vector<std::string>
  list_dialog_partners(const std::string& user_id) const = 0;
};

} // namespace sn::storage::repositories
