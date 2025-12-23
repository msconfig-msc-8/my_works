cmake_minimum_required(VERSION 3.20)
project(Lab1_Markov LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --- ТВОЯ библиотека/код проекта ---
file(GLOB MARKOV_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

add_library(markov_lib ${MARKOV_SOURCES})

target_include_directories(markov_lib
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)

# --- ПРИЛОЖЕНИЕ (CLI) ---
file(GLOB APP_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/app/*.cpp"
)

add_executable(markov_cli ${APP_SOURCES})
target_link_libraries(markov_cli PRIVATE markov_lib)

# --- UnitTest++ (MSYS2 UCRT64) ---
set(UNITTESTPP_ROOT "C:/msys64/ucrt64" CACHE PATH "MSYS2 ucrt64 prefix")

find_path(UNITTESTPP_INCLUDE_DIR
    NAMES UnitTest++/UnitTest++.h
    PATHS "${UNITTESTPP_ROOT}/include"
    NO_DEFAULT_PATH
    REQUIRED
)

find_library(UNITTESTPP_LIBRARY
    NAMES UnitTest++
    PATHS "${UNITTESTPP_ROOT}/lib"
    NO_DEFAULT_PATH
    REQUIRED
)

add_library(UnitTestPP::UnitTestPP UNKNOWN IMPORTED)
set_target_properties(UnitTestPP::UnitTestPP PROPERTIES
    IMPORTED_LOCATION "${UNITTESTPP_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${UNITTESTPP_INCLUDE_DIR}"
)

# --- ТЕСТЫ ---
enable_testing()

add_executable(markov_tests
    tests/tests_markov.cpp
)

target_link_libraries(markov_tests
    PRIVATE
        markov_lib
        UnitTestPP::UnitTestPP
)

add_test(NAME markov_tests COMMAND markov_tests)
