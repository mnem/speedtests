include_directories(${SPEEDTESTS_SOURCE_DIR}/external/boost/1_51_0)
include_directories(${SPEEDTESTS_SOURCE_DIR}/external/uthash/1_9_6)

set(TESTLIBS
  testcore
  hashtest
)

foreach(testlib ${TESTLIBS})
  add_library(${testlib} ${testlib}/${testlib}.cc)
endforeach(testlib)

set(TESTLIBS ${TESTLIBS} PARENT_SCOPE)
