#pragma once
#include <vector>

#include "sn/storage/repositories/IMessageRepository.hpp"

namespace sn::storage::memory {

class InMemoryMessageRepository final : public sn::storage::repositories::IMessageRepository {
public:
  void add(const sn::domain::entities::messages::Message& m) override;

  std::vector<sn::domain::entities::messages::Message>
  list_between(const std::string& a, const std::string& b) const override;

  std::vector<std::string>
  list_dialog_partners(const std::string& user_id) const override;

private:
  std::vector<sn::domain::entities::messages::Message> all_;
};

} // namespace sn::storage::memory
