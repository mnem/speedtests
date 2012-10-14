include(${SPEEDTESTS_SOURCE_DIR}/tests/all_tests_includes.cmake)
file(GLOB all_tests_src *.cc)
add_library(speedtests_alltests ${all_tests_src})
