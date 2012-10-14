include(${SPEEDTESTS_SOURCE_DIR}/tests/all_tests_includes.cmake)
link_directories(${SPEEDTESTS_BINARY_DIR}/hosts/cli)
add_executable(speedy main.cc  cli_test_monitor.cc)
target_link_libraries(speedy speedtests_core speedtests_alltests)
