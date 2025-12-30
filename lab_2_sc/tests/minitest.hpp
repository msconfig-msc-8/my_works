#pragma once
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace sn::test {

struct TestCase {
  std::string name;
  std::function<void()> fn;
};

inline std::vector<TestCase>& registry() {
  static std::vector<TestCase> r;
  return r;
}

struct Registrar {
  Registrar(std::string name, std::function<void()> fn) {
    registry().push_back(TestCase{std::move(name), std::move(fn)});
  }
};

inline int run_all() {
  int failed = 0;
  for (const auto& tc : registry()) {
    try {
      tc.fn();
      std::cout << "[PASS] " << tc.name << "\n";
    } catch (const std::exception& e) {
      ++failed;
      std::cout << "[FAIL] " << tc.name << " :: " << e.what() << "\n";
    } catch (...) {
      ++failed;
      std::cout << "[FAIL] " << tc.name << " :: unknown exception\n";
    }
  }
  std::cout << "\nTotal: " << registry().size()
            << ", Failed: " << failed << "\n";
  return failed == 0 ? 0 : 1;
}

} // namespace sn::test

#define SN_TEST_CASE(name) \
  static void name(); \
  static sn::test::Registrar reg_##name(#name, name); \
  static void name()

#define SN_REQUIRE(expr) \
  do { \
    if (!(expr)) { \
      throw std::runtime_error(std::string("Requirement failed: ") + #expr); \
    } \
  } while (0)
