#include <cstdio>
#include <cmath>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include "ifloat.hh"

typedef SimpleFloat<uint32_t, uint64_t, 32, myint> fshort_t;
typedef myfloat f_t;
typedef f_t T;
typedef complex<T> U;

int main() {
  for(int i = 1; i < 256; i ++)
    try {
      myint    f(1);
      fshort_t ff(1);
      std::cout << i << " : 1 == " << ((f  << i) >> i) << std::endl;
      std::cout << i << " : 1 == " << ((ff << (myint(1) << i)) >> (myint(1) << i)) << std::endl;
    } catch(const char* e) {
      std::cout << e << std::endl;
    }
  try {
    f_t test, test2;
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
    test = f_t(1) / test;
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

