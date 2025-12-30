#include "sn/domain/entities/Credentials.hpp"
#include "sn/domain/exceptions/Exceptions.hpp"

#include <utility>

namespace sn::domain::entities {

using sn::domain::exceptions::ValidationException;

Credentials::Credentials(std::string user_id, std::string password_hash, std::string salt, time_point updated_at)
  : user_id_(std::move(user_id)),
    password_hash_(std::move(password_hash)),
    salt_(std::move(salt)),
    updated_at_(updated_at) {
  if (user_id_.empty()) throw ValidationException("Credentials user_id is empty");
  if (password_hash_.empty()) throw ValidationException("Password hash is empty");
}

const std::string& Credentials::user_id() const noexcept { return user_id_; }
const std::string& Credentials::password_hash() const noexcept { return password_hash_; }
const std::string& Credentials::salt() const noexcept { return salt_; }
Credentials::time_point Credentials::updated_at() const noexcept { return updated_at_; }

void Credentials::set_password_hash(std::string new_hash, std::string new_salt, time_point updated_at) {
  if (new_hash.empty()) throw ValidationException("Password hash is empty");
  password_hash_ = std::move(new_hash);
  salt_ = std::move(new_salt);
  updated_at_ = updated_at;
}

} // namespace sn::domain::entities
