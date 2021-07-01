#include <cstdio>
#include <cmath>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <assert.h>
#include "lieonn.hh"

int main() {
  for(int i = 0; i < max(64, _FLOAT_BITS_) * 2; i ++)
    try {
      myint   f(1);
      myfloat ff(1);
      std::cout << i << " : 1 == " << ((f  << i) >> i) << std::endl;
      std::cout << i << " : 1 == " << ((ff << (int64_t(1) << i)) >> (int64_t(1) << i)) << std::endl;
    } catch(const char* e) {
      std::cout << e << std::endl;
    }
  myint test_init(1);
  std::cout << test_init << std::endl;
  try {
    myfloat test, test2;
    std::cin >> test;
    std::cin >> test2;
    std::cout << test << "+" << test2 << "="<< test + test2 << std::endl;
    std::cout << test << "-" << test2 << "="<< test - test2 << std::endl;
    std::cout << test << "*" << test2 << "="<< test * test2 << std::endl;
    std::cout << test << "/" << test2 << "="<< test / test2 << std::endl;
    std::cout << "exp(test)      : " << exp(test) << std::endl;
    std::cout << "log(exp(test)) : " << log(exp(test)) << std::endl;
    std::cout << "log(test)      : " << log(test) << std::endl;
    std::cout << "exp(log(test)) : " << exp(log(test)) << std::endl;
    test = myfloat(1) / test;
    std::cout << "exp(1/test)       : " << exp(test) << std::endl;
    std::cout << "log(exp(1/test))  : " << log(exp(test)) << std::endl;
    std::cout << "log(1/test)       : " << log(test) << std::endl;
    std::cout << "exp(log(1/test))  : " << exp(log(test)) << std::endl;
    std::cout << "atan(1/test)      : " << test.atan() << std::endl;
    std::cout << "tan(atan(1/test)) : " << tan(test.atan()) << std::endl;
    std::cout << "atan(tan(1/test)) : " << (tan(test)).atan() << std::endl;
  } catch (const char* e) {
    std::cout << e << std::endl;
  }
  return 0;
}

