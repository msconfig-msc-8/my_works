cmake_minimum_required(VERSION 3.20)

project(SocialNetwork LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(SN_BUILD_TESTS "Build unit tests" ON)
option(SN_ENABLE_COVERAGE "Enable coverage flags (GCC/Clang)" OFF)

if(SN_ENABLE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  add_compile_options(-O0 -g --coverage)
  add_link_options(--coverage)
endif()

add_library(sn
  src/sn.cpp
  src/util/Clock.cpp
  src/util/IdGenerator.cpp
  src/domain/value_objects/Email.cpp
  src/domain/value_objects/Phone.cpp
  src/domain/entities/User.cpp
  src/domain/entities/Profile.cpp
  src/domain/entities/Credentials.cpp
  src/domain/entities/Session.cpp
  src/storage/memory/InMemoryUserRepository.cpp
  src/services/security/SimplePasswordHasher.cpp
  src/services/AuthService.cpp
  src/domain/entities/posts/Post.cpp
  src/storage/memory/InMemoryPostRepository.cpp
  src/services/PostService.cpp
  src/domain/entities/friends/FriendRequest.cpp
  src/storage/memory/InMemoryFriendRepository.cpp
  src/services/FriendService.cpp
  src/domain/entities/messages/Message.cpp
  src/storage/memory/InMemoryMessageRepository.cpp
  src/services/MessageService.cpp
  src/services/FeedService.cpp


)
target_include_directories(sn PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(sn_cli
  cli/main.cpp
  cli/menu/ConsoleMenu.cpp
)
target_link_libraries(sn_cli PRIVATE sn)

if(SN_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
