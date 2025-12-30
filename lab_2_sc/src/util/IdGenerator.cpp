#include "sn/util/IdGenerator.hpp"

#include <utility>

namespace sn::util {

IdGenerator::IdGenerator(std::string prefix) : prefix_(std::move(prefix)) {}

std::string IdGenerator::next() {
  std::lock_guard<std::mutex> lock(mutex_);
  ++last_;
  return prefix_ + "-" + std::to_string(last_);
}

std::string IdGenerator::prefix() const {
  return prefix_;
}

unsigned long long IdGenerator::last_value() const {
  std::lock_guard<std::mutex> lock(mutex_);
  return last_;
}

} // namespace sn::util
