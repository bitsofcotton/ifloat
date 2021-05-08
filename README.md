# bitsofcotton/ifloat
This is a simple slow integer wrapper for working float, for the subsystem that not implement float.

# Tips
There's a little advantage to use this library when we met the condition exponent value to be huge or tinier.

# How to use
    #include "lieonn.hh"
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
And input/output on SimpleFloat is very simple slow one we have.

# Another Download Sites
* https://drive.google.com/drive/folders/1B71X1BMttL6yyi76REeOTNRrpopO8EAR?usp=sharing
* https://1drv.ms/u/s!AnqkwcwMjB_PaDIfXya_M3-aLXw?e=qzfKcU
* https://ja.osdn.net/users/bitsofcotton/

