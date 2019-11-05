#include <cstdio>
#include <cmath>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include "ifloat.hh"

typedef DUInt<unsigned long long, 64> di_t;
typedef SimpleFloat<unsigned long long, 64, short> f_t;

int main() {
  di_t f(1);
  for(int i = 1; i < 128; i ++) {
    f *= di_t(i);
    std::cout << i << " : " << f << std::endl;
  }
  f_t test, test2;
  std::cin >> test;
  std::cin >> test2;
  //std::cout << test << (((unsigned long long)1) << 63) << std::endl;
  std::cout << test << "+" << test2 << "= "<< test + test2 << std::endl;
  std::cout << test << "-" << test2 << "= "<< test - test2 << std::endl;
  std::cout << test << "*" << test2 << "= "<< test * test2 << std::endl;
  std::cout << test << "/" << test2 << "= "<< test / test2 << std::endl;
//  std::cout << test.exp() << std::endl;
  return 0;
}

