# bitsofcotton/ifloat
This is integer wrapper for working float, due to non reliable, nor complex, nor no FPU implementation.
Too slow to calculate...

# Tips
(Still) not compatible with std::limits.

# Bugs
(Still) not works, debugging SimpleFloat::operator +,*,/.

# How to use
    #include "ifloat.hh"
    ...
    typedef Float<unsigned long long, 64, short> float_t;
    ...
      ...
      float_t a(1);
      float_t b(1);
      float_t c(a * b);
      ...
