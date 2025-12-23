cmake_minimum_required(VERSION 3.16)
project(lab11 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(fifteen_lib
    src/fifteen/fifteen.cpp
)
target_include_directories(fifteen_lib PUBLIC include)

add_executable(fifteen_app
    app/fifteen_main.cpp
)
target_link_libraries(fifteen_app PRIVATE fifteen_lib)

enable_testing()

find_package(UnitTest++ REQUIRED)

add_executable(unit_tests
    tests/tests.cpp
)
target_link_libraries(unit_tests PRIVATE fifteen_lib UnitTest++)
add_test(NAME run_unit_tests COMMAND unit_tests)
