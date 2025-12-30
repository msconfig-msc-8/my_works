#pragma once
#include <chrono>
#include <string>

namespace sn::domain::entities::messages {

class Message {
public:
  using time_point = std::chrono::system_clock::time_point;

  Message(std::string id,
          std::string from_user_id,
          std::string to_user_id,
          std::string text,
          time_point created_at);

  [[nodiscard]] const std::string& id() const noexcept;
  [[nodiscard]] const std::string& from_user_id() const noexcept;
  [[nodiscard]] const std::string& to_user_id() const noexcept;
  [[nodiscard]] const std::string& text() const noexcept;
  [[nodiscard]] time_point created_at() const noexcept;

private:
  std::string id_;
  std::string from_;
  std::string to_;
  std::string text_;
  time_point created_at_;
};

} // namespace sn::domain::entities::messages
