#include "sn/services/security/SimplePasswordHasher.hpp"
#include "sn/util/IdGenerator.hpp"

#include <sstream>

namespace sn::services::security {

std::string SimplePasswordHasher::make_salt() const {
  // соль делаем через генератор id (просто и детерминируемо по формату)
  sn::util::IdGenerator gen("S");
  return gen.next();
}

std::string SimplePasswordHasher::hash_password(const std::string& password, const std::string& salt) const {
  // "хэш" = salt + ":" + password (учебная заглушка)
  return salt + ":" + password;
}

bool SimplePasswordHasher::verify(const std::string& password,
                                  const std::string& salt,
                                  const std::string& expected_hash) const {
  return hash_password(password, salt) == expected_hash;
}

} // namespace sn::services::security
