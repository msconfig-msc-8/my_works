#pragma once
#include <chrono>

namespace sn::util {

class Clock {
public:
  using time_point = std::chrono::system_clock::time_point;

  // Текущее время (вынесено в класс для тестируемости).
  [[nodiscard]] time_point now() const;

  // Удобный хелпер: now + minutes
  [[nodiscard]] time_point add_minutes(time_point base, int minutes) const;
};

} // namespace sn::util
