#pragma once
#include "sn/services/security/IPasswordHasher.hpp"

namespace sn::services::security {

// Учебная реализация (не для реальной безопасности).
class SimplePasswordHasher final : public IPasswordHasher {
public:
  std::string make_salt() const override;
  std::string hash_password(const std::string& password, const std::string& salt) const override;
  bool verify(const std::string& password,
              const std::string& salt,
              const std::string& expected_hash) const override;
};

} // namespace sn::services::security
