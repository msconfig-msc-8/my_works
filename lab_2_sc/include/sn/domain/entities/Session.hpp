#pragma once
#include <chrono>
#include <string>

namespace sn::domain::entities {

class Session {
public:
  using time_point = std::chrono::system_clock::time_point;

  Session(std::string token, std::string user_id, time_point expires_at, std::string device_id);

  [[nodiscard]] const std::string& token() const noexcept;
  [[nodiscard]] const std::string& user_id() const noexcept;
  [[nodiscard]] const std::string& device_id() const noexcept;
  [[nodiscard]] time_point expires_at() const noexcept;

  [[nodiscard]] bool is_expired(time_point now) const noexcept;

  void refresh(time_point new_expires_at);

private:
  std::string token_;
  std::string user_id_;
  time_point expires_at_;
  std::string device_id_;
};

} // namespace sn::domain::entities
