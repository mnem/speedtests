set(TESTLIBS
  testcore
  hashtest
)

foreach(testlib ${TESTLIBS})
  add_library(${testlib} ${testlib}/${testlib}.cc ${testlib}/${testlib}.c)
endforeach(testlib)

set(TESTLIBS ${TESTLIBS} PARENT_SCOPE)
