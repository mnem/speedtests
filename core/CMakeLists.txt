set(TESTLIBS hashtest)

foreach(testlib ${TESTLIBS})
  add_library(${testlib} ${testlib}.cc ${testlib}.c)
endforeach(testlib)

set(TESTLIBS ${TESTLIBS} PARENT_SCOPE)
