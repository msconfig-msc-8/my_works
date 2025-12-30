#pragma once
#include <chrono>
#include <string>

namespace sn::domain::entities {

class Credentials {
public:
  using time_point = std::chrono::system_clock::time_point;

  Credentials(std::string user_id, std::string password_hash, std::string salt, time_point updated_at);

  [[nodiscard]] const std::string& user_id() const noexcept;
  [[nodiscard]] const std::string& password_hash() const noexcept;
  [[nodiscard]] const std::string& salt() const noexcept;
  [[nodiscard]] time_point updated_at() const noexcept;

  void set_password_hash(std::string new_hash, std::string new_salt, time_point updated_at);

private:
  std::string user_id_;
  std::string password_hash_;
  std::string salt_;
  time_point updated_at_;
};

} // namespace sn::domain::entities
