# bitsofcotton/ifloat
This is a integer wrapper for working float, due to non reliable, nor complex, nor no FPU implementation.
Too slow to calculate if we use DUInt recursive, there's some much faster algorithms with large accuracy.
And, there is a nice options in clang, gcc -msoft-float, we must choose them first.
This is another simpler implementation.

# Tips
Not compatible with std::limits.
Some implementation with AMD64, there's a little possibility to break xmm0 register (not the CPU matter), so in that case, we can choose this library with -mno-sse option and so on.  
There's a little advantage to use this library when we met the condition exponent value to be huge or tinier.

# How to use
    #include "ifloat.hh"
    ...
    typedef SimpleFloat<DUInt<uint64_t, 64>, DUInt<DUInt<uint64_t, 64>, 128>, 128, Signed<DUInt<uint64_t, 64>, 128> > float_t;
    // or we can use compile with -D_FLOAT_BITS_=...
    //   typedef myfloat float_t;
    ...
      ...
      auto pi(atan2(float_t(1), float_t(1)) * float_t(4));
      ...

# General Tips
If we met the condition that exponent or mantissa to be float, it's not the better condition, instead of them, we can use log space or exp space to calculate what we met.

# Known Bug
We can't initialize SimpleFloat with float value, so please initialize with integer value and calculate on them.

# Another Download Sites
* https://drive.google.com/drive/folders/1B71X1BMttL6yyi76REeOTNRrpopO8EAR?usp=sharing
* https://1drv.ms/u/s!AnqkwcwMjB_PaDIfXya_M3-aLXw?e=qzfKcU
* https://ja.osdn.net/users/bitsofcotton/

# Archive
This repository is archived, so without bugreport, will no change.

