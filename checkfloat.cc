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
  myuint test(0);
  test = ~ test;
  for(int i = 0 ; bool(test); test >>= 1, i ++)
    if(bool(test) && !(i < _FLOAT_BITS_)) 
      std::cerr << i << " : " << (test >> i) << std::endl;
  return 0;
}

