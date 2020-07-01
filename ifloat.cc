#include <cstdio>
#include <cmath>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include "ifloat.hh"

typedef DUInt<uint64_t, 64> di_t;
typedef DUInt<di_t,  128> di2_t;
typedef DUInt<di2_t, 256> di3_t;
typedef DUInt<di3_t, 512> di4_t;
typedef DUInt<di4_t, 1024> di5_t;
typedef DUInt<di5_t, 2048> di6_t;
typedef DUInt<di6_t, 4096> di7_t;
typedef Signed<DUInt<uint64_t, 64>, 128> i128_t;
typedef SimpleFloat<uint32_t, uint64_t, 32, i128_t> fshort_t;
typedef SimpleFloat<di6_t, di7_t, 4096, i128_t> f_t;
typedef f_t T;
typedef Complex<T> U;

int main() {
  for(int i = 1; i < 256; i ++)
    try {
      i128_t   f(1);
      fshort_t ff(1);
      std::cout << i << " : 1 == " << ((f  << i) >> i) << std::endl;
      std::cout << i << " : 1 == " << ((ff << (i128_t(1) << i)) >> (i128_t(1) << i)) << std::endl;
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

