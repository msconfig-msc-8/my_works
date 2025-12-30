#pragma once
#include "SocialNetworkException.hpp"
#include <string>

namespace sn::domain::exceptions {

// 1) общие/валидация
class ValidationException : public SocialNetworkException {
public: explicit ValidationException(const std::string& m) : SocialNetworkException(m) {}
};

class InvalidEmailException : public SocialNetworkException {
public: explicit InvalidEmailException(const std::string& m) : SocialNetworkException(m) {}
};

class InvalidPhoneException : public SocialNetworkException {
public: explicit InvalidPhoneException(const std::string& m) : SocialNetworkException(m) {}
};

// 2) доступ/аутентификация
class AuthenticationFailedException : public SocialNetworkException {
public: explicit AuthenticationFailedException(const std::string& m) : SocialNetworkException(m) {}
};

class PermissionDeniedException : public SocialNetworkException {
public: explicit PermissionDeniedException(const std::string& m) : SocialNetworkException(m) {}
};

// 3) not found
class UserNotFoundException : public SocialNetworkException {
public: explicit UserNotFoundException(const std::string& m) : SocialNetworkException(m) {}
};

class PostNotFoundException : public SocialNetworkException {
public: explicit PostNotFoundException(const std::string& m) : SocialNetworkException(m) {}
};

class ChatNotFoundException : public SocialNetworkException {
public: explicit ChatNotFoundException(const std::string& m) : SocialNetworkException(m) {}
};

// 4) конфликты/лимиты
class DuplicateFriendRequestException : public SocialNetworkException {
public: explicit DuplicateFriendRequestException(const std::string& m) : SocialNetworkException(m) {}
};

class AlreadyMemberException : public SocialNetworkException {
public: explicit AlreadyMemberException(const std::string& m) : SocialNetworkException(m) {}
};

class ContentTooLongException : public SocialNetworkException {
public: explicit ContentTooLongException(const std::string& m) : SocialNetworkException(m) {}
};

class RateLimitExceededException : public SocialNetworkException {
public: explicit RateLimitExceededException(const std::string& m) : SocialNetworkException(m) {}
};

} // namespace sn::domain::exceptions
