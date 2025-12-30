#pragma once
#include <chrono>
#include <string>

namespace sn::domain::entities::posts {

class Post {
public:
  using time_point = std::chrono::system_clock::time_point;

  Post(std::string id,
       std::string author_user_id,
       std::string content,
       time_point created_at);

  [[nodiscard]] const std::string& id() const noexcept;
  [[nodiscard]] const std::string& author_user_id() const noexcept;
  [[nodiscard]] const std::string& content() const noexcept;
  [[nodiscard]] time_point created_at() const noexcept;

  void edit(std::string new_content);

private:
  std::string id_;
  std::string author_user_id_;
  std::string content_;
  time_point created_at_;
};

} // namespace sn::domain::entities::posts
