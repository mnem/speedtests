//
// # All speed tests
//
#include "all_tests.h"
#include "test_core.h"
#include "hash_test.h"
#include "mathlib_test.h"

namespace SpeedTests {

void AddAllTests(Runner &runner)
{
  // ## Hash map tests
  runner.Add(new HashTestUTHashAdd());
  runner.Add(new HashTestUTHashFind());
  runner.Add(new HashTestBoostAdd());
  runner.Add(new HashTestBoostFind());
  runner.Add(new HashTestStdAdd());
  runner.Add(new HashTestStdFind());

  // ## Math lib tests
  runner.Add(new MathLibTestEigenAdd());
  runner.Add(new MathLibTestEigenMultiply());
  runner.Add(new MathLibTestGLMAdd());
  runner.Add(new MathLibTestGLMMultiply());
  runner.Add(new MathLibTestCMLAdd());
  runner.Add(new MathLibTestCMLMultiply());
}

} // namespace SpeedTests
