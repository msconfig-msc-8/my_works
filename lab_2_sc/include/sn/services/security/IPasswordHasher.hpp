#pragma once
#include <string>

namespace sn::services::security {

class IPasswordHasher {
public:
  virtual ~IPasswordHasher() = default;

  virtual std::string make_salt() const = 0;
  virtual std::string hash_password(const std::string& password, const std::string& salt) const = 0;
  virtual bool verify(const std::string& password,
                      const std::string& salt,
                      const std::string& expected_hash) const = 0;
};

} // namespace sn::services::security
