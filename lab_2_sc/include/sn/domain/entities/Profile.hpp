#pragma once
#include <string>

namespace sn::domain::entities {

class Profile {
public:
  Profile(std::string user_id, std::string display_name);

  [[nodiscard]] const std::string& user_id() const noexcept;
  [[nodiscard]] const std::string& display_name() const noexcept;
  [[nodiscard]] const std::string& bio() const noexcept;

  void set_display_name(std::string name);
  void set_bio(std::string bio);

private:
  std::string user_id_;
  std::string display_name_;
  std::string bio_;
};

} // namespace sn::domain::entities
