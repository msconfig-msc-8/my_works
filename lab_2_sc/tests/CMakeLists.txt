add_executable(sn_tests
  test_main.cpp
  test_smoke.cpp
  test_util.cpp
  test_exceptions.cpp
  test_value_objects.cpp
  test_entities.cpp
  test_storage.cpp
  test_services.cpp
  test_posts.cpp
  test_friends.cpp
  test_messages.cpp
  test_feed.cpp


)
target_link_libraries(sn_tests PRIVATE sn)
target_include_directories(sn_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_test(NAME sn_tests COMMAND sn_tests)
