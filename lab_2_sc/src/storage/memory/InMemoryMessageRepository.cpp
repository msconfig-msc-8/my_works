#include "sn/storage/memory/InMemoryMessageRepository.hpp"

#include <algorithm>
#include <unordered_set>

namespace sn::storage::memory {

void InMemoryMessageRepository::add(const sn::domain::entities::messages::Message& m) {
  all_.push_back(m);
}

std::vector<sn::domain::entities::messages::Message>
InMemoryMessageRepository::list_between(const std::string& a, const std::string& b) const {
  std::vector<sn::domain::entities::messages::Message> out;
  for (const auto& m : all_) {
    const bool ab = (m.from_user_id() == a && m.to_user_id() == b);
    const bool ba = (m.from_user_id() == b && m.to_user_id() == a);
    if (ab || ba) out.push_back(m);
  }
  // порядок сообщений важен — сортируем по времени
  std::sort(out.begin(), out.end(),
            [](const auto& x, const auto& y) { return x.created_at() < y.created_at(); });
  return out;
}

std::vector<std::string>
InMemoryMessageRepository::list_dialog_partners(const std::string& user_id) const {
  std::unordered_set<std::string> set;
  for (const auto& m : all_) {
    if (m.from_user_id() == user_id) set.insert(m.to_user_id());
    if (m.to_user_id() == user_id) set.insert(m.from_user_id());
  }
  return std::vector<std::string>(set.begin(), set.end());
}

} // namespace sn::storage::memory
