#include <cstdio>
#include <cmath>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include "ifloat.hh"

typedef DUInt<unsigned long long, 64> di_t;
typedef Float<unsigned long long, 64, short> f_t;

int main() {
  di_t t0(1);
  std::cout << (((t0 << 31) / t0) >> 31) << std::endl;
  std::cout << (((t0 << 63) / t0) >> 31) << std::endl;
  std::cout << (((t0 << 127) / t0) >> 31) << std::endl;
  std::cout << (((t0 << 63) / t0) >> 63) << std::endl;
  std::cout << (((t0 << 64) / t0) >> 64) << std::endl;
  return 0;
  f_t test, test2;
  std::cin >> test;
  std::cin >> test2;
  //std::cout << test << (((unsigned long long)1) << 63) << std::endl;
  std::cout << test << "+" << test2 << "= "<< test + test2 << std::endl;
  std::cout << test << "-" << test2 << "= "<< test - test2 << std::endl;
  std::cout << test << "*" << test2 << "= "<< test * test2 << std::endl;
  std::cout << test << "/" << test2 << "= "<< test / test2 << std::endl;
  return 0;
}

