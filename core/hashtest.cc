#include <iostream>

extern "C" void hashtest_c(void);

void hashtest_cc()
{
  std::cout << "I'm a CPP hash test" << std::endl;
}

void hashtest()
{
  hashtest_c();
  hashtest_cc();
}
