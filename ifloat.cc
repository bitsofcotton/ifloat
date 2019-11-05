#include <cstdio>
#include <cmath>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include "ifloat.hh"

typedef DUInt<uint64_t, 64> di_t;
typedef SimpleFloat<uint64_t, 64, short> f_t;

int main() {
  di_t f(1);
  f_t  ff(1);
  for(int i = 1; i < 64; i ++) {
    f  *= di_t(i);
    ff *= f_t(i);
    std::cout << i << " : " << f << " == " << ff << ", 2 == " << (((di_t(1) << 63) / (di_t(1) << i)) >> (63 - i - 1)) << std::endl;
  }
  std::cout << log(exp(f_t(- 1) / f_t(2))) << std::endl;
  return 0;
  f_t test, test2;
  std::cin >> test;
  std::cin >> test2;
  std::cout << test << "+" << test2 << "= "<< test + test2 << std::endl;
  std::cout << test << "-" << test2 << "= "<< test - test2 << std::endl;
  std::cout << test << "*" << test2 << "= "<< test * test2 << std::endl;
  std::cout << test << "/" << test2 << "= "<< test / test2 << std::endl;
  std::cout << test.exp() << std::endl;
  std::cout << test.log() << std::endl;
  return 0;
}

