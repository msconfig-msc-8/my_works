#pragma once
#include <stdexcept>
#include <string>

namespace sn::domain::exceptions {

class SocialNetworkException : public std::runtime_error {
public:
  explicit SocialNetworkException(const std::string& message)
    : std::runtime_error(message) {}
};

} // namespace sn::domain::exceptions
