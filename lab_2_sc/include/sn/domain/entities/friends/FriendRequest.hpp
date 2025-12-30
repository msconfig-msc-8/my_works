#pragma once
#include <chrono>
#include <string>

namespace sn::domain::entities::friends {

enum class FriendRequestStatus {
  Pending = 0,
  Accepted = 1,
  Rejected = 2
};

class FriendRequest {
public:
  using time_point = std::chrono::system_clock::time_point;

  FriendRequest(std::string id,
                std::string from_user_id,
                std::string to_user_id,
                time_point created_at);

  [[nodiscard]] const std::string& id() const noexcept;
  [[nodiscard]] const std::string& from_user_id() const noexcept;
  [[nodiscard]] const std::string& to_user_id() const noexcept;
  [[nodiscard]] FriendRequestStatus status() const noexcept;
  [[nodiscard]] time_point created_at() const noexcept;

  void accept();
  void reject();

private:
  std::string id_;
  std::string from_user_id_;
  std::string to_user_id_;
  FriendRequestStatus status_ = FriendRequestStatus::Pending;
  time_point created_at_;
};

} // namespace sn::domain::entities::friends
