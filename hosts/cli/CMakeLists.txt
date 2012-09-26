include_directories(${SPEEDTESTS_SOURCE_DIR}/external/uthash/1_9_6)
include_directories(${SPEEDTESTS_SOURCE_DIR}/external/boost/1_51_0)
include_directories(${SPEEDTESTS_SOURCE_DIR}/hosts/cli)
include_directories(${SPEEDTESTS_SOURCE_DIR}/core)

link_directories(${SPEEDTESTS_BINARY_DIR}/hosts/cli)

add_executable(speedy main.cc)
target_link_libraries(speedy ${TESTLIBS})
