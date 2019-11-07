# bitsofcotton/ifloat
This is integer wrapper for working float, due to non reliable, nor complex, nor no FPU implementation.
Too slow to calculate...
And, there is nice option in clang, gcc -msoft-float, we must choose them first.
This is another simpler implementation.

# Tips
(Still) not compatible with std::limits. neither not works with std::complex.

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
