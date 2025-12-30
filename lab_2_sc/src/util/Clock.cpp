#include "sn/util/Clock.hpp"

namespace sn::util {

Clock::time_point Clock::now() const {
  return std::chrono::system_clock::now();
}

Clock::time_point Clock::add_minutes(time_point base, int minutes) const {
  return base + std::chrono::minutes(minutes);
}

} // namespace sn::util
