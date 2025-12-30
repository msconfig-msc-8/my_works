#pragma once
#include <string>
#include <string_view>

namespace sn::domain::value_objects {

class Phone {
public:
  Phone() = default;
  explicit Phone(std::string value);   // валидирует, иначе кидает InvalidPhoneException

  [[nodiscard]] const std::string& value() const noexcept;

  [[nodiscard]] bool is_verified() const noexcept;
  void set_verified(bool v) noexcept;

  // Оставляем только цифры и '+' в начале (для хранения "нормализованного" вида)
  [[nodiscard]] std::string normalized() const;

  static bool is_valid(std::string_view s);

private:
  std::string value_;
  bool verified_ = false;
};

} // namespace sn::domain::value_objects
