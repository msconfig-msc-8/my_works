#pragma once
#include <chrono>
#include <optional>
#include <string>
#include <string_view>

#include "sn/domain/value_objects/Email.hpp"
#include "sn/domain/value_objects/Phone.hpp"

namespace sn::domain::entities {

enum class UserStatus {
  Active = 0,
  Deactivated = 1
};

class User {
public:
  using time_point = std::chrono::system_clock::time_point;

  User(std::string id,
       std::string username,
       sn::domain::value_objects::Email email,
       time_point created_at);

  [[nodiscard]] const std::string& id() const noexcept;
  [[nodiscard]] const std::string& username() const noexcept;
  [[nodiscard]] const sn::domain::value_objects::Email& email() const noexcept;
  [[nodiscard]] const std::optional<sn::domain::value_objects::Phone>& phone() const noexcept;
  [[nodiscard]] time_point created_at() const noexcept;

  [[nodiscard]] UserStatus status() const noexcept;
  [[nodiscard]] bool is_active() const noexcept;

  void change_username(std::string new_username);
  void change_email(sn::domain::value_objects::Email new_email);
  void set_phone(std::optional<sn::domain::value_objects::Phone> new_phone);

  void deactivate();
  void activate();

  static bool is_valid_username(std::string_view name);

private:
  std::string id_;
  std::string username_;
  sn::domain::value_objects::Email email_;
  std::optional<sn::domain::value_objects::Phone> phone_;
  time_point created_at_;
  UserStatus status_ = UserStatus::Active;
};

} // namespace sn::domain::entities
