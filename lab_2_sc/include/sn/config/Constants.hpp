#pragma once
#include <cstddef>

namespace sn::config {

// Сюда выносим любые "магические числа" проекта.
// Потом будем расширять по мере роста функционала. :contentReference[oaicite:3]{index=3}

inline constexpr std::size_t kMaxUsernameLength = 24;
inline constexpr std::size_t kMinPasswordLength = 8;

inline constexpr std::size_t kMaxPostLength = 280;
inline constexpr std::size_t kMaxCommentLength = 500;

inline constexpr int kDefaultSessionMinutes = 60;

inline constexpr std::size_t kMinUsernameLength = 3;
inline constexpr std::size_t kMaxDisplayNameLength = 32;
inline constexpr std::size_t kMaxBioLength = 160;

inline constexpr std::size_t kMaxMessageLength = 500;


} // namespace sn::config
