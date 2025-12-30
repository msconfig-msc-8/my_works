#pragma once
#include <mutex>
#include <string>

namespace sn::util {

// Генератор строковых ID вида: "U-1", "U-2", ...
// Простой, потокобезопасный, тестируемый.
class IdGenerator {
public:
  explicit IdGenerator(std::string prefix);

  [[nodiscard]] std::string next();

  [[nodiscard]] std::string prefix() const;
  [[nodiscard]] unsigned long long last_value() const;

private:
  std::string prefix_;
  unsigned long long last_ = 0;
  mutable std::mutex mutex_;
};

} // namespace sn::util
