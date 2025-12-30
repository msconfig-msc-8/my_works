#include "sn/domain/entities/Profile.hpp"
#include "sn/config/Constants.hpp"
#include "sn/domain/exceptions/Exceptions.hpp"

#include <utility>

namespace sn::domain::entities {

using sn::domain::exceptions::ValidationException;

Profile::Profile(std::string user_id, std::string display_name)
  : user_id_(std::move(user_id)),
    display_name_(std::move(display_name)) {
  if (user_id_.empty()) throw ValidationException("Profile user_id is empty");
  if (display_name_.empty() || display_name_.size() > sn::config::kMaxDisplayNameLength) {
    throw ValidationException("Invalid display name");
  }
}

const std::string& Profile::user_id() const noexcept { return user_id_; }
const std::string& Profile::display_name() const noexcept { return display_name_; }
const std::string& Profile::bio() const noexcept { return bio_; }

void Profile::set_display_name(std::string name) {
  if (name.empty() || name.size() > sn::config::kMaxDisplayNameLength) {
    throw ValidationException("Invalid display name");
  }
  display_name_ = std::move(name);
}

void Profile::set_bio(std::string bio) {
  if (bio.size() > sn::config::kMaxBioLength) {
    throw ValidationException("Bio too long");
  }
  bio_ = std::move(bio);
}

} // namespace sn::domain::entities
