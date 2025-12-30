cmake_minimum_required(VERSION 3.24)

set(MODULE_NAME network_resilience_module)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
  "*.cpp"
  "*.hpp"
)


# IMPORTANT: don't compile tests into the module library
list(FILTER SOURCES EXCLUDE REGEX ".*/test/.*")

add_library(${MODULE_NAME} SHARED ${SOURCES})

target_include_directories(${MODULE_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# sc-machine provides headers and runtime for agents/modules
# Targets are supplied by Conan package sc-machine.
target_link_libraries(${MODULE_NAME}
  PRIVATE
    sc-machine::sc-memory
    sc-machine::sc-agents-common
)

# Put extension into folder that is in extensions search path in scripts/start.sh
set_target_properties(${MODULE_NAME} PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/extensions"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/extensions"
)

if(SC_BUILD_TESTS)
  include(${CMAKE_MODULE_PATH}/tests.cmake)

  make_tests_from_folder(
    ${CMAKE_CURRENT_SOURCE_DIR}/test
    NAME test_network_resilience
    DEPENDS ${MODULE_NAME} sc-machine::sc-memory sc-machine::sc-agents-common
    INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}
  )
endif()
