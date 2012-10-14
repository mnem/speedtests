#include "mathlib_test.h"
#include <assert.h>

const size_t kInternalTestIterations = 1000;

////////////////////////////////////////////////////////////////////////
// Eigen
void MathLibTestEigenBase::BeforeTestIterations()
{
  a(0,0) = 0.1234f;
  a(1,1) = 0.1234f;
  a(2,2) = 0.1234f;
  a(3,3) = 1.0f;

  b(0,0) = 0.5678f;
  b(1,1) = 0.5678f;
  b(2,2) = 0.5678f;
  b(3,3) = 1.0f;
}

void MathLibTestEigenAdd::Test()
{
  for (volatile size_t i = 0; i < kInternalTestIterations; i++) {
    result = a + b;
  }
}

void MathLibTestEigenMultiply::Test()
{
  for (volatile size_t i = 0; i < kInternalTestIterations; i++) {
    result = a * b;
  }
}

////////////////////////////////////////////////////////////////////////
// GLM
void MathLibTestGLMBase::BeforeTestIterations()
{
  a[0][0] = 0.1234f;
  a[1][1] = 0.1234f;
  a[2][2] = 0.1234f;
  a[3][3] = 1.0f;

  b[0][0] = 0.5678f;
  b[1][1] = 0.5678f;
  b[2][2] = 0.5678f;
  b[3][3] = 1.0f;
}

void MathLibTestGLMAdd::Test()
{
  for (volatile size_t i = 0; i < kInternalTestIterations; i++) {
    result = a + b;
  }
}

void MathLibTestGLMMultiply::Test()
{
  for (volatile size_t i = 0; i < kInternalTestIterations; i++) {
    result = a * b;
  }
}

////////////////////////////////////////////////////////////////////////
// CML
void MathLibTestCMLBase::BeforeTestIterations()
{
  a.set_basis_element(0, 0, 0.1234f);
  a.set_basis_element(1, 1, 0.1234f);
  a.set_basis_element(2, 2, 0.1234f);
  a.set_basis_element(3, 3, 0.1234f);

  b.set_basis_element(0, 0, 0.1234f);
  b.set_basis_element(1, 1, 0.1234f);
  b.set_basis_element(2, 2, 0.1234f);
  b.set_basis_element(3, 3, 0.1234f);
}

void MathLibTestCMLAdd::Test()
{
  for (volatile size_t i = 0; i < kInternalTestIterations; i++) {
    result = a + b;
  }
}

void MathLibTestCMLMultiply::Test()
{
  for (volatile size_t i = 0; i < kInternalTestIterations; i++) {
    result = a * b;
  }
}
