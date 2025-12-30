#include "sn/domain/value_objects/Email.hpp"
#include "sn/domain/exceptions/Exceptions.hpp"

#include <algorithm>
#include <cctype>

namespace sn::domain::value_objects {

using sn::domain::exceptions::InvalidEmailException;

static std::string to_lower_copy(std::string s) {
  std::transform(s.begin(), s.end(), s.begin(),
                 [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
  return s;
}

bool Email::is_valid(std::string_view s) {
  // Простая учебная валидация:
  // - есть '@'
  // - есть '.' после '@'
  // - не начинается/не заканчивается пробелами
  if (s.empty()) return false;
  if (std::isspace(static_cast<unsigned char>(s.front())) ||
      std::isspace(static_cast<unsigned char>(s.back())))
    return false;

  const auto at = s.find('@');
  if (at == std::string_view::npos || at == 0 || at + 1 >= s.size()) return false;

  const auto dot = s.find('.', at + 1);
  if (dot == std::string_view::npos || dot + 1 >= s.size()) return false;

  return true;
}

Email::Email(std::string value) {
  if (!is_valid(value)) {
    throw InvalidEmailException("Invalid email: " + value);
  }
  value_ = std::move(value);
}

const std::string& Email::value() const noexcept {
  return value_;
}

std::string Email::normalized() const {
  return to_lower_copy(value_);
}

bool Email::is_verified() const noexcept {
  return verified_;
}

void Email::set_verified(bool v) noexcept {
  verified_ = v;
}

} // namespace sn::domain::value_objects
