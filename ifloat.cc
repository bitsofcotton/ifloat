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
    std::cout << i << " : " << f << " == " << ff << ", 2 == " << (((di_t(1) << 63) / (di_t(1) << i)) >> (63 - i - 1)) << " 0 != " << floor(f_t(1) << short(i)) << std::endl;
  }
  f_t test, test2;
  std::cin >> test;
  std::cin >> test2;
  std::cout << test << "+" << test2 << "= "<< test + test2 << std::endl;
  std::cout << test << "-" << test2 << "= "<< test - test2 << std::endl;
  std::cout << test << "*" << test2 << "= "<< test * test2 << std::endl;
  std::cout << test << "/" << test2 << "= "<< test / test2 << std::endl;
  std::cout << exp(test) << std::endl;
  std::cout << log(exp(test)) << std::endl;
  std::cout << log(test) << std::endl;
  std::cout << exp(log(test)) << std::endl;
  test = f_t(1) / test;
  std::cout << exp(test) << std::endl;
  std::cout << log(exp(test)) << std::endl;
  std::cout << log(test) << std::endl;
  std::cout << exp(log(test)) << std::endl;
  return 0;
}

