cmake_minimum_required(VERSION 3.10)

# Название проекта
project(SocialNetwork VERSION 1.0 LANGUAGES CXX)

# Стандарт C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем предупреждения
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra)
endif()

# Путь к заголовочным файлам
include_directories(${CMAKE_SOURCE_DIR}/src)

# Основная программа
add_executable(social_network src/main.cpp)

# Тесты
add_executable(tests tests/tests.cpp)
target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/tests)

# Вывод информации
message(STATUS "CMake version: ${CMAKE_VERSION}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
