# bitsofcotton/ifloat
This is integer wrapper for working float, due to non reliable, nor complex, nor no FPU implementation.
Too slow to calculate if we use DUInt recursive, there's some much faster algorithms with large accuracy.
And, there is nice options in clang, gcc -msoft-float, we must choose them first.
This is another simpler implementation.

# Tips
(Still) not compatible with std::limits. neither not works with std::complex.
Some implementation with AMD64, there's a little possibility to break xmm0 register (not the CPU matter), so in that case, we can choose this library with -mno-sse option and so on.  
There's a little advantage to use this library when we met the condition exponent value to be large or tiny.

# How to use
    #include "ifloat.hh"
    ...
    typedef SimpleFloat<unsigned long long, DUInt<unsigned long long, 64>, 64, short> float_t;
    ...
      ...
      float_t a(1);
      float_t b(1);
      float_t c(a * b);
      ...
