#include "all_tests.h"
#include "test_core/test_core.h"
#include "hash_test/hash_test.h"

namespace SpeedTests {

void AddAllTests(Runner &runner) {
  runner.Add(new HashTestUTHashAdd());
  runner.Add(new HashTestUTHashFind());

  runner.Add(new HashTestBoostAdd());
  runner.Add(new HashTestBoostFind());

  runner.Add(new HashTestStdAdd());
  runner.Add(new HashTestStdFind());
}

} // SpeedTests
