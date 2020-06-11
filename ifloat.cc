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
typedef DUInt<di7_t, 8192> di8_t;
//typedef SimpleFloat<di4_t, di5_t, 1024, int> f_t;
//typedef SimpleFloat<uint64_t, DUInt<uint64_t, 64>, 64, short> f_t;
//typedef SimpleFloat<uint32_t, uint64_t, 32, short> f_t;
typedef Signed<DUInt<uint64_t, 64>, 128> i128_t;
typedef SimpleFloat<uint32_t, uint64_t, 32, i128_t> f_t;
typedef f_t T;
typedef Complex<T> U;
typedef Signed<DUInt<uint8_t, 8>, 16> ii_t;

int main() {
  ii_t ij(1);
  std::cout << ii_t(ij << 15) << std::endl;
  f_t  ff(2);
  i128_t ii(1);
  ii <<= 68;
  for(int i = 1; i < 64; i ++) {
    std::cout << pow(ff, pow(ff, f_t(i))) << std::endl;
  //  f  *= di_t(i);
  //  ff *= f_t(i);
  //  std::cout << i << " : " << f << " == " << ff << ", 2 == " << (((di_t(1) << 63) / (di_t(1) << i)) >> (63 - i - 1)) << " 0 != " << floor(f_t(1) << short(i)) << std::endl;
  }
  f_t test, test2;
 //try{
  std::cin >> test;
  std::cin >> test2;
  std::cout << test << "+" << test2 << "= "<< test + test2 << std::endl;
  std::cout << test << "-" << test2 << "= "<< test - test2 << std::endl;
  std::cout << test << "*" << test2 << "= "<< test * test2 << std::endl;
  std::cout << test << "/" << test2 << "= "<< test / test2 << std::endl;
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
/*
 } catch (const char* e) {
  std::cout << e << std::endl;
 }
*/
  return 0;
}

