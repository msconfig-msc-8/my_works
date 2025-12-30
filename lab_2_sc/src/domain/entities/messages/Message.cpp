#include "sn/domain/entities/messages/Message.hpp"
#include "sn/config/Constants.hpp"
#include "sn/domain/exceptions/Exceptions.hpp"

#include <utility>

namespace sn::domain::entities::messages {

using sn::domain::exceptions::ValidationException;
using sn::domain::exceptions::ContentTooLongException;

Message::Message(std::string id,
                 std::string from_user_id,
                 std::string to_user_id,
                 std::string text,
                 time_point created_at)
  : id_(std::move(id)),
    from_(std::move(from_user_id)),
    to_(std::move(to_user_id)),
    text_(std::move(text)),
    created_at_(created_at) {
  if (id_.empty()) throw ValidationException("message id is empty");
  if (from_.empty() || to_.empty()) throw ValidationException("user id is empty");
  if (from_ == to_) throw ValidationException("cannot send message to yourself");
  if (text_.empty()) throw ValidationException("message text is empty");
  if (text_.size() > sn::config::kMaxMessageLength) throw ContentTooLongException("message too long");
}

const std::string& Message::id() const noexcept { return id_; }
const std::string& Message::from_user_id() const noexcept { return from_; }
const std::string& Message::to_user_id() const noexcept { return to_; }
const std::string& Message::text() const noexcept { return text_; }
Message::time_point Message::created_at() const noexcept { return created_at_; }

} // namespace sn::domain::entities::messages
