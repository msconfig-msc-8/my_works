#pragma once
#include <string>
#include <string_view>

namespace sn::domain::value_objects {

class Email {
public:
  Email() = default;
  explicit Email(std::string value);   // валидирует, иначе кидает InvalidEmailException

  [[nodiscard]] const std::string& value() const noexcept;

  // полезные методы (это уже "поведения")
  [[nodiscard]] std::string normalized() const;     // lower-case
  [[nodiscard]] bool is_verified() const noexcept;
  void set_verified(bool v) noexcept;

  static bool is_valid(std::string_view s);

private:
  std::string value_;
  bool verified_ = false;
};

} // namespace sn::domain::value_objects
