#ifndef SPEEDTESTS_TESTS_MATHLIB_TEST_H_
#define SPEEDTESTS_TESTS_MATHLIB_TEST_H_

#include "test_core.h"
#include "Eigen/Dense"
#include "glm/glm.hpp"
#include "cml/cml.h"

////////////////////////////////////////////////////////////////////////
// Eigen
class MathLibTestEigenBase : public SpeedTests::SpeedTest
{
 public:
  virtual void BeforeTestIterations();

 protected:
  Eigen::Matrix4f a;
  Eigen::Matrix4f b;
  Eigen::Matrix4f result;
};

class MathLibTestEigenAdd : public MathLibTestEigenBase
{
 public:
  virtual void Test();
  virtual const char* description() const { return "Eigen: Add"; };
};

class MathLibTestEigenMultiply : public MathLibTestEigenBase
{
 public:
  virtual void Test();
  virtual const char* description() const { return "Eigen: Multiply"; };
};

////////////////////////////////////////////////////////////////////////
// GLM
class MathLibTestGLMBase : public SpeedTests::SpeedTest
{
 public:
  virtual void BeforeTestIterations();

 protected:
  glm::mat4 a;
  glm::mat4 b;
  glm::mat4 result;
};

class MathLibTestGLMAdd : public MathLibTestGLMBase
{
 public:
  virtual void Test();
  virtual const char* description() const { return "GLM: Add"; };
};

class MathLibTestGLMMultiply : public MathLibTestGLMBase
{
 public:
  virtual void Test();
  virtual const char* description() const { return "GLM: Multiply"; };
};

////////////////////////////////////////////////////////////////////////
// CML
class MathLibTestCMLBase : public SpeedTests::SpeedTest
{
 public:
  virtual void BeforeTestIterations();

 protected:
  cml::matrix44f_c a;
  cml::matrix44f_c b;
  cml::matrix44f_c result;
};

class MathLibTestCMLAdd : public MathLibTestCMLBase
{
 public:
  virtual void Test();
  virtual const char* description() const { return "CML: Add"; };
};

class MathLibTestCMLMultiply : public MathLibTestCMLBase
{
 public:
  virtual void Test();
  virtual const char* description() const { return "CML: Multiply"; };
};

#endif // SPEEDTESTS_TESTS_MATHLIB_TEST_H_
