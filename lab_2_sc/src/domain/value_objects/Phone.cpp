#include "sn/domain/value_objects/Phone.hpp"
#include "sn/domain/exceptions/Exceptions.hpp"

#include <cctype>

namespace sn::domain::value_objects {

using sn::domain::exceptions::InvalidPhoneException;

bool Phone::is_valid(std::string_view s) {
  // Учебная валидация:
  // - длина 7..16
  // - допустим '+' первым символом
  // - дальше только цифры
  if (s.size() < 7 || s.size() > 16) return false;

  std::size_t i = 0;
  if (s[0] == '+') {
    if (s.size() == 1) return false;
    i = 1;
  }

  for (; i < s.size(); ++i) {
    if (!std::isdigit(static_cast<unsigned char>(s[i]))) return false;
  }
  return true;
}

Phone::Phone(std::string value) {
  if (!is_valid(value)) {
    throw InvalidPhoneException("Invalid phone: " + value);
  }
  value_ = std::move(value);
}

const std::string& Phone::value() const noexcept {
  return value_;
}

bool Phone::is_verified() const noexcept {
  return verified_;
}

void Phone::set_verified(bool v) noexcept {
  verified_ = v;
}

std::string Phone::normalized() const {
  // убираем всё кроме цифр, '+' оставляем только если он первый
  std::string out;
  out.reserve(value_.size());

  std::size_t i = 0;
  if (!value_.empty() && value_[0] == '+') {
    out.push_back('+');
    i = 1;
  }
  for (; i < value_.size(); ++i) {
    if (std::isdigit(static_cast<unsigned char>(value_[i]))) out.push_back(value_[i]);
  }
  return out;
}

} // namespace sn::domain::value_objects
