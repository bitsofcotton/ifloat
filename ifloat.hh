#if !defined(_INTEGER_FLOAT_)

using std::move;
using std::max;
using std::min;
using std::vector;

template <typename T, int bits> class DUInt {
public:
  inline DUInt();
  inline DUInt(const int& src);
  inline DUInt(const T& src);
  inline DUInt(const DUInt<T,bits>& src);
  inline DUInt(DUInt<T,bits>&& src);
  inline ~DUInt();
  
  inline DUInt<T,bits>& operator ++ ();
  inline DUInt<T,bits>  operator ++ (int);
  inline DUInt<T,bits>& operator -- ();
  inline DUInt<T,bits>  operator -- (int);
  inline DUInt<T,bits>  operator -  () const;
  inline DUInt<T,bits>  operator +  (const DUInt<T,bits>& src) const;
  inline DUInt<T,bits>& operator += (const DUInt<T,bits>& src);
  inline DUInt<T,bits>  operator -  (const DUInt<T,bits>& src) const;
  inline DUInt<T,bits>& operator -= (const DUInt<T,bits>& src);
  inline DUInt<T,bits>  operator *  (const DUInt<T,bits>& src) const;
  inline DUInt<T,bits>& operator *= (const DUInt<T,bits>& src);
  inline DUInt<T,bits>  operator /  (const DUInt<T,bits>& src) const;
  inline DUInt<T,bits>& operator /= (const DUInt<T,bits>& src);
  inline DUInt<T,bits>  operator %  (const DUInt<T,bits>& src) const;
  inline DUInt<T,bits>& operator %= (const DUInt<T,bits>& src);
  inline DUInt<T,bits>  operator << ( const int& b)            const;
  inline DUInt<T,bits>& operator <<= (const int& b);
  inline DUInt<T,bits>  operator >> ( const int& b)            const;
  inline DUInt<T,bits>& operator >>= (const int& b);
  inline DUInt<T,bits>  operator &  (const DUInt<T,bits>& src) const;
  inline DUInt<T,bits>& operator &= (const DUInt<T,bits>& src);
  inline DUInt<T,bits>  operator |  (const DUInt<T,bits>& src) const;
  inline DUInt<T,bits>& operator |= (const DUInt<T,bits>& src);
  inline DUInt<T,bits>  operator ^  (const DUInt<T,bits>& src) const;
  inline DUInt<T,bits>& operator ^= (const DUInt<T,bits>& src);
  inline DUInt<T,bits>  operator ~  ()                         const;
  inline DUInt<T,bits>& operator =  (const DUInt<T,bits>& src);
  inline DUInt<T,bits>& operator =  (const int& src);
  inline DUInt<T,bits>& operator =  (DUInt<T,bits>&& src);
  inline bool           operator <  (const DUInt<T,bits>& src) const;
  inline bool           operator <= (const DUInt<T,bits>& src) const;
  inline bool           operator >  (const DUInt<T,bits>& src) const;
  inline bool           operator >= (const DUInt<T,bits>& src) const;
  inline bool           operator == (const DUInt<T,bits>& src) const;
  inline bool           operator != (const DUInt<T,bits>& src) const;
  inline bool           operator && (const DUInt<T,bits>& src) const;
  inline bool           operator || (const DUInt<T,bits>& src) const;
  inline bool           operator !    () const;
  inline                operator bool () const;
  inline                operator int  () const;

/*
  friend std::ostream&  operator << (std::ostream& os, DUInt<T,bits>  v);
  friend std::istream&  operator >> (std::istream& is, DUInt<T,bits>& v);
*/

  T e[2];
};

template <typename T, int bits> inline DUInt<T,bits>::DUInt() {
  assert(0 < bits && ! (bits & 3));
}

template <typename T, int bits> inline DUInt<T,bits>::DUInt(const int& src) {
  *this ^= *this;
  e[0]   = src;
}

template <typename T, int bits> inline DUInt<T,bits>::DUInt(const T& src) {
  *this ^= *this;
  e[0]   = src;
}

template <typename T, int bits> inline DUInt<T,bits>::DUInt(const DUInt<T,bits>& src) {
  *this = src;
}

template <typename T, int bits> inline DUInt<T,bits>::DUInt(DUInt<T,bits>&& src) {
  *this = src;
}

template <typename T, int bits> inline DUInt<T,bits>::~DUInt() {
  ;
}

template <typename T, int bits> inline DUInt<T,bits>& DUInt<T,bits>::operator ++ () {
  ++ e[0];
  if(!e[0])
    ++ e[1];
  return *this;
}

template <typename T, int bits> inline DUInt<T,bits>  DUInt<T,bits>::operator ++ (int) {
  const auto work(*this);
  ++ *this;
  return work;
}

template <typename T, int bits> inline DUInt<T,bits>& DUInt<T,bits>::operator -- () {
  if(!e[0])
    -- e[1];
  -- e[0];
  return *this;
}

template <typename T, int bits> inline DUInt<T,bits>  DUInt<T,bits>::operator -- (int) {
  const auto work(*this);
  -- *this;
  return work;
}

template <typename T, int bits> inline DUInt<T,bits>  DUInt<T,bits>::operator -  () const {
  DUInt<T,bits> work(~ *this);
  return ++ work;
}

template <typename T, int bits> inline DUInt<T,bits>  DUInt<T,bits>::operator +  (const DUInt<T,bits>& src) const {
  auto work(*this);
  return work += src;
}

template <typename T, int bits> inline DUInt<T,bits>& DUInt<T,bits>::operator += (const DUInt<T,bits>& src) {
  // N.B. assembler can boost dramatically this code. but not here.
  const auto e0(max(e[0], src.e[0]));
  e[0] += src.e[0];
  if(e[0] < e0)
    e[1] ++;
  e[1] += src.e[1];
  return *this;
}

template <typename T, int bits> inline DUInt<T,bits>  DUInt<T,bits>::operator -  (const DUInt<T,bits>& src) const {
  auto work(*this);
  return work -= src;
}

template <typename T, int bits> inline DUInt<T,bits>& DUInt<T,bits>::operator -= (const DUInt<T,bits>& src) {
  return *this += - src;
}

template <typename T, int bits> inline DUInt<T,bits>  DUInt<T,bits>::operator *  (const DUInt<T,bits>& src) const {
  static const auto hbits(bits >> 1);
  static const auto lmask((T(1) << hbits) - T(1));
  const auto d0(e[0] & lmask);
  const auto d1(e[0] >> hbits);
  const auto d2(e[1] & lmask);
  const auto d3(e[1] >> hbits);
  const auto s0(src.e[0] & lmask);
  const auto s1(src.e[0] >> hbits);
  const auto s2(src.e[1] & lmask);
  const auto s3(src.e[1] >> hbits);
  // (d0 + d1 * p1 + d2 * p2 + d3 * p3) * (s0 + s1 * p1 + s2 * p2 + s3 * p3) ==
  // (d0 + d1 * p1) * (s0 + s1 * p1) +
  //   (d0      + d1 * p1) * (s2 * p2 + s3 * p3) +
  //   (d2 * p2 + d3 * p3) * (s0      + s1 * p1)
  //   p2 * p2 * (...) ==
  // (d0 * s0 + d0 * s1 * p1 + s0 * d1 * p1 + d1 * s1 * p1 * p1) +
  //   (d0 * s2 * p2 + d0 * s3 * p3      + d1 * s2 * p1 * p2) +
  //   (d2 * s0 * p2 + d2 * s1 * p1 * p2 + d3 * s0 * p3) +
  //   p2 * p2 * (...) + p1 * p3 * (...) ==
  // d0 * s0 + (d0 * s1 + s0 * d1) * p1 +
  //   (d0 * s2 + d2 * s0 + d1 * s1) * p2 +
  //   (d0 * s3 + d2 * s1 + d1 * s2 + d3 * s0) * p3
  // dk * sl + dl * sk == dk * dl + sk * sl - (dk - dl) * (sk - sl)
  const DUInt<T,bits> sd0(d0 * s0);
  const DUInt<T,bits> sd1(d1 * s1);
  const DUInt<T,bits> sd2(d2 * s2);
  const DUInt<T,bits> sd3(d3 * s3);
  const DUInt<T,bits> c01((d0 - d1) * (s0 - s1));
  const DUInt<T,bits> c02((d0 - d2) * (s0 - s2));
  const DUInt<T,bits> c03((d0 - d3) * (s0 - s3));
  const DUInt<T,bits> c12((d1 - d2) * (s1 - s2));
  return sd0 + ((sd0 + sd1 - c01) << hbits) +
    ((sd0 + sd2 - c02 + sd1) << bits) +
    ((sd0 + sd3 - c03 + sd1 + sd2 - c12) << (bits + hbits));
}

template <typename T, int bits> inline DUInt<T,bits>& DUInt<T,bits>::operator *= (const DUInt<T,bits>& src) {
  return *this = *this * src;
}

template <typename T, int bits> inline DUInt<T,bits>  DUInt<T,bits>::operator /  (const DUInt<T,bits>& src) const {
  auto work(*this);
  return work /= src;
}

template <typename T, int bits> inline DUInt<T,bits>& DUInt<T,bits>::operator /= (const DUInt<T,bits>& src) {
  static const auto hbits(bits >> 1);
  static const auto lmask((T(1) << hbits) - T(1));
  if(! src)
    throw "Zero division";
  if(! *this)
    return *this;
  int shift(0);
  if(! src.e[1]) {
    if(! src.e[0])
      return *this;
    for(int i = 0; i < bits; i ++)
      if(int(src.e[0] & (T(1) << i)))
        shift = i;
  } else {
    for(int i = 0; i < bits; i ++)
      if(int(src.e[1] & (T(1) << i)))
        shift = i + bits;
  }
  const auto dblocks(shift / hbits + 1);
  const auto lshift(dblocks * hbits - shift - 1);
  assert(0 <= lshift && lshift < hbits);
  const auto dd(src << lshift);
  T de[dblocks];
  for(int i = 0; i < dblocks; i ++)
    de[i] = i & 1 ? dd.e[i >> 1] >> hbits : dd.e[i >> 1] & lmask;
  // N.B.
  //   block division with better condition.
  //   de[0] ... de[n], de[n] = 0...1..., each de uses half of space.
  //                                ^ hbits - 1
  //   res = *this / (dd == de[])
  auto res(src ^ src);
  auto r(e[0] ^ e[0]);
  for(int i = 2; 0 <= i; i --) {
    switch(i) {
    case 0:
      r =  e[0];
      break;
    case 1:
      r = (e[0] >> hbits) | (e[1] << hbits);
      break;
    case 2:
      r =  e[1];
      break;
    default:
      ;
    }
    // N.B.
    //   d(0)  := original.
    //   d(k+1) = (d << (hbits * i)) * dd + r + d(k).
    // debug here: const auto d(r / (dd == de));
    const auto div(DUInt<T,bits>(d) << (hbits * i));
    *this -= div * dd;
    res   += div;
  }
  r   <<= lshift;
  res <<= lshift;
  return *this = (res += DUInt<T,bits>(r / (de[dblocks - 1] >> lshift));
}

template <typename T, int bits> inline DUInt<T,bits>  DUInt<T,bits>::operator %  (const DUInt<T,bits>& src) const {
  return *this - ((*this / src) * src);
}

template <typename T, int bits> inline DUInt<T,bits>& DUInt<T,bits>::operator %= (const DUInt<T,bits>& src) {
  return *this = *this % src;
}

template <typename T, int bits> inline DUInt<T,bits>  DUInt<T,bits>::operator << (const int& b)             const {
  auto work(*this);
  return work <<= b;
}

template <typename T, int bits> inline DUInt<T,bits>& DUInt<T,bits>::operator <<= (const int& b) {
  if(b < 0)
    return *this >>= (- b);
  if(b > bits * 2)
    return *this ^= *this;
  if(b > bits) {
    e[1]  = e[0] << (b - bits);
    e[0] ^= e[0];
    return *this;
  }
  e[1] <<= b;
  e[1]  |= e[0] >> (bits - b);
  e[0] <<= b;
  return *this;
}

template <typename T, int bits> inline DUInt<T,bits>  DUInt<T,bits>::operator >> (const int& b)             const {
  auto work(*this);
  return work >>= b;
}

template <typename T, int bits> inline DUInt<T,bits>& DUInt<T,bits>::operator >>= (const int& b) {
  if(b < 0)
    return *this <<= (- b);
  if(b > bits * 2)
    return *this ^= *this;
  if(b > bits) {
    e[0]  = e[1] >> (b - bits);
    e[1] ^= e[1];
    return *this;
  }
  e[0] >>= b;
  e[0]  |= e[1] << (bits - b);
  e[1] >>= b;
  return *this;
}

template <typename T, int bits> inline DUInt<T,bits>  DUInt<T,bits>::operator &  (const DUInt<T,bits>& src) const {
  auto work(*this);
  return work &= src;
}

template <typename T, int bits> inline DUInt<T,bits>& DUInt<T,bits>::operator &= (const DUInt<T,bits>& src) {
  e[0] &= src.e[0];
  e[1] &= src.e[1];
  return *this;
}

template <typename T, int bits> inline DUInt<T,bits>  DUInt<T,bits>::operator |  (const DUInt<T,bits>& src) const {
  auto work(*this);
  return work |= src;
}

template <typename T, int bits> inline DUInt<T,bits>& DUInt<T,bits>::operator |= (const DUInt<T,bits>& src) {
  e[0] |= src.e[0];
  e[1] |= src.e[1];
  return *this;
}

template <typename T, int bits> inline DUInt<T,bits>  DUInt<T,bits>::operator ^  (const DUInt<T,bits>& src) const {
  auto work(*this);
  return work ^= src;
}

template <typename T, int bits> inline DUInt<T,bits>& DUInt<T,bits>::operator ^= (const DUInt<T,bits>& src) {
  e[0] ^= src.e[0];
  e[1] ^= src.e[1];
  return *this;
}

template <typename T, int bits> inline DUInt<T,bits>  DUInt<T,bits>::operator ~  () const {
  DUInt<T,bits> work;
  work.e[0] = ~ e[0];
  work.e[1] = ~ e[1];
  return work;
}

template <typename T, int bits> inline DUInt<T,bits>& DUInt<T,bits>::operator =  (const DUInt<T,bits>& src) {
  e[0] = src.e[0];
  e[1] = src.e[1];
  return *this;
}

template <typename T, int bits> inline DUInt<T,bits>& DUInt<T,bits>::operator =  (const int& src) {
  e[0]  = src;
  e[1] ^= e[1];
  return *this;
}

template <typename T, int bits> inline DUInt<T,bits>& DUInt<T,bits>::operator =  (DUInt<T,bits>&& src) {
  e[0] = move(src.e[0]);
  e[1] = move(src.e[1]);
  return *this;
}

template <typename T, int bits> inline bool      DUInt<T,bits>::operator <  (const DUInt<T,bits>& src) const {
  return (!e[1] ? (!src.e[1] ? e[0] < src.e[0] : true) : (e[1] == src.e[1] ? e[0] < src.e[0] : e[1] < src.e[1]));
}

template <typename T, int bits> inline bool      DUInt<T,bits>::operator <= (const DUInt<T,bits>& src) const {
  return *this < src || *this == src;
}

template <typename T, int bits> inline bool      DUInt<T,bits>::operator >  (const DUInt<T,bits>& src) const {
  return ! (*this <= src);
}

template <typename T, int bits> inline bool      DUInt<T,bits>::operator >= (const DUInt<T,bits>& src) const {
  return ! (*this < src);
}

template <typename T, int bits> inline bool      DUInt<T,bits>::operator == (const DUInt<T,bits>& src) const {
  return ! (*this != src);
}

template <typename T, int bits> inline bool      DUInt<T,bits>::operator != (const DUInt<T,bits>& src) const {
  return ! (*this - src);
}

template <typename T, int bits> inline bool      DUInt<T,bits>::operator && (const DUInt<T,bits>& src) const {
  return ! ( (! *this) || (! src) );
}

template <typename T, int bits> inline bool      DUInt<T,bits>::operator || (const DUInt<T,bits>& src) const {
  return ! ( (! *this) && (! src) );
}

template <typename T, int bits> inline bool      DUInt<T,bits>::operator !    () const {
  return (! e[0]) && (! e[1]);
}

template <typename T, int bits> inline           DUInt<T,bits>::operator bool () const {
  return ! (! *this);
}

template <typename T, int bits> inline           DUInt<T,bits>::operator int () const {
  return e[0];
}

template <typename T, int bits> std::ostream&  operator << (std::ostream& os, DUInt<T,bits> v) {
  // XXX:
  os << v.e[0];
  return os;
  static const DUInt<T,bits> ten(10);
  vector<char> buf;
  while(! (!v)) {
    buf.push_back(int(v % ten) + char('0'));
    v /= ten;
  }
  if(buf.size()) {
    for(int i = 0; i < buf.size(); i ++)
      os << buf[buf.size() - 1 - i];
    return os;
  }
  return os << '0';
}

template <typename T, int bits> std::istream&  operator >> (std::istream& is, DUInt<T,bits>& v) {
  const static DUInt<T,bits> ten(10);
  v = DUInt<T,bits>(0);
  // skip white spaces.
  while(! is.eof()) {
    const auto buf(is.get());
    if(buf != ' ' && buf != '\t') {
      is.unget();
      break;
    }
  }
  while(! is.eof() ) {
    const auto buf(is.get());
    switch(buf) {
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
      v *= ten;
      v += DUInt<T,bits>(int(buf - '0'));
      break;
    default:
      goto ensure;
    }
  }
 ensure:
  return is;
}


template <typename T, int bits, typename U> class Float {
public:
  inline Float();
  inline Float(const int& src);
  inline Float(const Float<T,bits,U>& src);
  inline Float(Float<T,bits,U>&& src);
  inline ~Float();
  
  inline Float<T,bits,U>  operator -  () const;
  inline Float<T,bits,U>  operator +  (const Float<T,bits,U>& src) const;
  inline Float<T,bits,U>& operator += (const Float<T,bits,U>& src);
  inline Float<T,bits,U>  operator -  (const Float<T,bits,U>& src) const;
  inline Float<T,bits,U>& operator -= (const Float<T,bits,U>& src);
  inline Float<T,bits,U>  operator *  (const Float<T,bits,U>& src) const;
  inline Float<T,bits,U>& operator *= (const Float<T,bits,U>& src);
  inline Float<T,bits,U>  operator /  (const Float<T,bits,U>& src) const;
  inline Float<T,bits,U>& operator /= (const Float<T,bits,U>& src);
  inline Float<T,bits,U>& operator =  (const Float<T,bits,U>& src);
  inline Float<T,bits,U>& operator =  (Float<T,bits,U>&& src);
  inline bool             operator == (const Float<T,bits,U>& src) const;
  inline bool             operator != (const Float<T,bits,U>& src) const;
  inline bool             operator <  (const Float<T,bits,U>& src) const;
  inline bool             operator <= (const Float<T,bits,U>& src) const;
  inline bool             operator >  (const Float<T,bits,U>& src) const;
  inline bool             operator >= (const Float<T,bits,U>& src) const;
  inline bool             operator !  () const;
  inline                  operator bool () const;
  inline                  operator int  () const;
  inline Float<T,bits,U>  ceil() const;
  inline Float<T,bits,U>  abs()  const;
         Float<T,bits,U>  log()  const;
         Float<T,bits,U>  exp()  const;
  inline Float<T,bits,U>  sqrt() const;
  inline const vector<Float<T,bits,U> >& en(const int& b) const;
  inline Float<T,bits,U>  logsmall() const;
  inline Float<T,bits,U>  expsmall() const;
  
/*
  friend std::ostream&    operator << (std::ostream& os, const Float<T,bits,U>& v);
  friend std::istream&    operator >> (std::istream& is, Float<T,bits,U>& v);
*/
  
  unsigned char s;
  typedef enum {
    INF = 0,
    NaN = 1,
    SIGN = 2
  } state_t;
  T m;
  U e;
private:
  template <typename V> inline int normalize(V& src) const;
  inline bool prepMul(const Float<T,bits,U>& src);
  inline char residue2() const;
};

template <typename T, int bits, typename U> inline Float<T,bits,U>::Float() {
  assert(0 < bits && ! (bits & 1));
  s ^= s;
  m ^= m;
  e ^= e;
}

template <typename T, int bits, typename U> inline Float<T,bits,U>::Float(const int& src) {
  s ^= s;
  m  = std::abs(src);
  e ^= e;
  e += normalize(m);
  if(m < T(0))
    *this = - *this;
}

template <typename T, int bits, typename U> inline Float<T,bits,U>::Float(const Float<T,bits,U>& src) {
  *this = src;
}

template <typename T, int bits, typename U> inline Float<T,bits,U>::Float(Float<T,bits,U>&& src) {
  *this = src;
}

template <typename T, int bits, typename U> inline Float<T,bits,U>::~Float() {
  ;
}

template <typename T, int bits, typename U> inline Float<T,bits,U> Float<T,bits,U>::operator -  () const {
  auto work(*this);
  work.s ^= 1 << SIGN;
  return work;
}

template <typename T, int bits, typename U> inline Float<T,bits,U> Float<T,bits,U>::operator +  (const Float<T,bits,U>& src) const {
  auto work(*this);
  return work += src;
}

template <typename T, int bits, typename U> inline Float<T,bits,U>& Float<T,bits,U>::operator += (const Float<T,bits,U>& src) {
  s |= src.s & ((1 << INF) | (1 << NaN));
  if(! m) {
    m = src.m;
    e = src.e;
    return *this;
  }
  if(! src.m)
    return *this;
  const auto e0(e);
  if(! ((s & (1 << SIGN)) ^ (src.s & (1 << SIGN)))) {
    if(e >= src.e) {
      m >>= 1;
      ++ e;
      m += src.m >> (e - src.e);
    } else
      return *this = src + *this;
  } else {
    if(e > src.e)
      m -= src.m >> (e - src.e);
    else if(e == src.e) {
      if(m >= src.m)
        m -= src.m;
      else
        return *this = src + *this;
    } else
      return *this = src + *this;
  }
  if(!m) {
    m ^= m;
    e ^= e;
    return *this;
  }
  e += normalize(m);
  if(e * e0 < 0) {
    if(e < 0)
      s |= 1 << INF;
    else {
      e ^= e;
      m ^= m;
    }
  }
  return *this;
}

template <typename T, int bits, typename U> inline Float<T,bits,U> Float<T,bits,U>::operator -  (const Float<T,bits,U>& src) const {
  auto work(*this);
  return work -= src;
}

template <typename T, int bits, typename U> inline Float<T,bits,U>& Float<T,bits,U>::operator -= (const Float<T,bits,U>& src) {
  return *this += - src;
}

template <typename T, int bits, typename U> inline Float<T,bits,U> Float<T,bits,U>::operator *  (const Float<T,bits,U>& src) const {
  auto work(*this);
  return work *= src;
}

template <typename T, int bits, typename U> inline Float<T,bits,U>& Float<T,bits,U>::operator *= (const Float<T,bits,U>& src) {
  if(! prepMul(src))
    return *this;
  if((! m) || (! src.m)) {
    m ^= m;
    e ^= e;
    return *this;
  }
  const auto e0(e);
  auto mm(DUInt<T,bits>(m) * DUInt<T,bits>(src.m));
  // N.B.
  //   *this == src == 1 then:
  //     mm = 1 << (bits * 2 - 2), e + src.e == - (bits - 1) * 2 here.
  e += src.e + normalize(mm) + bits;
  m  = mm.e[1];
  if(e < max(e0, src.e))
    s |= 1 << INF;
  return *this;
}

template <typename T, int bits, typename U> inline char Float<T,bits,U>::residue2() const {
  return char(int(m << e)) & 1;
}

template <typename T, int bits, typename U> inline Float<T,bits,U> Float<T,bits,U>::operator /  (const Float<T,bits,U>& src) const {
  auto work(*this);
  return work /= src;
}

template <typename T, int bits, typename U> inline Float<T,bits,U>& Float<T,bits,U>::operator /= (const Float<T,bits,U>& src) {
  if(! prepMul(src))
    return *this;
  if(! src.m) {
    s |= 1 << NaN;
    return *this;
  }
  if(! m)
    return *this;
  const auto e0(e);
  auto mm((DUInt<T,bits>(m) << bits) / DUInt<T,bits>(src.m));
  // N.B.
  //   *this / src == 1 then mm = (1 << bits), e - src.e = 0 here.
  e += - src.e + normalize(mm) - (bits - 1) * 2;
  m  = mm.e[1];
  if(e < max(e0, U(- src.e))) {
    s |= 1 << NaN;
    return *this;
  } else if(min(e0, U(- src.e)) < e) {
    e ^= e;
    m ^= m;
  }
  return *this;
}

template <typename T, int bits, typename U> inline Float<T,bits,U>& Float<T,bits,U>::operator =  (const Float<T,bits,U>& src) {
  s = src.s;
  e = src.e;
  m = src.m;
  return *this;
}

template <typename T, int bits, typename U> inline Float<T,bits,U>& Float<T,bits,U>::operator =  (Float<T,bits,U>&& src) {
  s = move(src.s);
  e = move(src.e);
  m = move(src.m);
  return *this;
}

template <typename T, int bits, typename U> inline bool             Float<T,bits,U>::operator == (const Float<T,bits,U>& src) const {
  return ! (*this != src);
}

template <typename T, int bits, typename U> inline bool             Float<T,bits,U>::operator != (const Float<T,bits,U>& src) const {
  return s != src.s || e != src.e || m != src.m;
}

template <typename T, int bits, typename U> inline bool             Float<T,bits,U>::operator <  (const Float<T,bits,U>& src) const {
  if((s & (1 << SIGN)) ^ (src.s & (1 << SIGN)))
    return s & (1 << SIGN);
  if(s & (1 << SIGN))
    return - *this > - src;
  return (!m || !src.m ? (!m ? ! (!src.m) : ! (!m)) : e > src.e || m > src.m) && isfinite(m) && isfinite(src.m);
}

template <typename T, int bits, typename U> inline bool             Float<T,bits,U>::operator <= (const Float<T,bits,U>& src) const {
  return *this < src || *this == src;
}

template <typename T, int bits, typename U> inline bool             Float<T,bits,U>::operator >  (const Float<T,bits,U>& src) const {
  return ! (*this <= src);
}

template <typename T, int bits, typename U> inline bool             Float<T,bits,U>::operator >= (const Float<T,bits,U>& src) const {
  return ! (*this < src);
}

template <typename T, int bits, typename U> inline bool             Float<T,bits,U>::operator !  () const {
  return ! m && isfinite(*this);
}

template <typename T, int bits, typename U> inline                  Float<T,bits,U>::operator bool () const {
  return ! (!*this);
}

template <typename T, int bits, typename U> inline                  Float<T,bits,U>::operator int  () const {
  auto deci(*this);
  if(! (! (deci.m >> (bits - deci.e))) || ! (deci.m <<= deci.e) )
    throw "Overflow to convert int.";
  return deci.m;
}

template <typename T, int bits, typename U> template <typename V> inline int Float<T,bits,U>::normalize(V& src) const {
  V   bt(1);
  int b(0);
  int tb;
  for(tb = 0; ! (! bt); tb ++) {
    if(src & bt)
      b = tb;
    bt <<= 1;
  }
  const auto shift(tb - b - 1);
  src <<= shift;
  return - shift;
}

template <typename T, int bits, typename U> inline bool Float<T,bits,U>::prepMul(const Float<T,bits,U>& src) {
  s ^= src.s & (1 << SIGN);
  if(! (isfinite(*this) && isfinite(src))) {
    s |= src.e & ((1 << INF) | (1 << NaN));
    return false;
  }
  return true;
}

template <typename T, int bits, typename U> inline Float<T,bits,U> Float<T,bits,U>::ceil() const {
  auto deci(*this);
  deci.m <<= deci.e;
  if(! deci.m)
    return *this;
  deci.m >>= deci.e;
  if(0 < e)
    deci.m |= e & (- (U(1) << (e + 1)));
  return *this - deci;
}

template <typename T, int bits, typename U> inline Float<T,bits,U> Float<T,bits,U>::abs() const {
  auto work(*this);
  work.s &= ~ (1 << SIGN);
  return work;
}

template <typename T, int bits, typename U> Float<T,bits,U> Float<T,bits,U>::log() const {
  const static Float<T,bits,U> zero(0);
  const static Float<T,bits,U> one(1);
  const static Float<T,bits,U> two(2);
        static vector<Float<T,bits,U> > p2;
  assert(zero < *this);
  if(this->abs() <= one)
    return logsmall();
  auto work(*this);
  int  i0;
  for(i0 = 0; isfinite(en(i0 + 1)[i0]) && en(i0 + 1)[i0] < work; i0 ++) ;
  ++ i0;
  if(p2.size() <= i0) {
    Float<T,bits,U> wres(1);
    for(int i = 0; i < i0; i ++) {
      if(p2.size() <= i)
        p2.push_back(wres);
      wres *= two;
    }
  }
  const auto&     ebuf(en(i0));
  Float<T,bits,U> res(0);
  for(int i = 0; i < i0 - 1; i ++)
    if(isfinite(ebuf[i0 - i - 1]) && ebuf[i0 - i - 2] <= work && work <= ebuf[i0 - i - 1]) {
      work /= ebuf[i0 - i - 2];
      res  += p2[i0 - i - 2];
    }
  if(work.abs() > one) {
    work /= ebuf[0];
    res  += one;
  }
  return res + work.logsmall();
}

template <typename T, int bits, typename U> Float<T,bits,U> Float<T,bits,U>::logsmall() const {
  const auto dx(*this - Float<T,bits,U>(1));
  Float<T,bits,U> x(dx);
  Float<T,bits,U> before(1);
  Float<T,bits,U> res(0);
  for(int t = 1; ! !((res - before).m); t ++) {
    before = res;
    res   += x / Float<T,bits,U>(t * pow(- 1, (t % 2) - 1));
    x     *= dx;
  }
  return res;
}

template <typename T, int bits, typename U> Float<T,bits,U> Float<T,bits,U>::exp() const {
  const static Float<T,bits,U> one(1);
  const static Float<T,bits,U> two(2);
  if(this->abs() <= one)
    return expsmall();
  auto work(*this);
  vector<char> be;
  while(! (!work.ceil())) {
    be.push_back(work.residue2());
    work /= two;
  }
  const auto& ebuf(en(be.size()));
  Float<T,bits,U> result(1);
  for(int i = 0; i < be.size(); i ++)
    if(be[i])
      result *= ebuf[i];
  return result *= (*this - this->ceil()).expsmall();
}

template <typename T, int bits, typename U> inline Float<T,bits,U> Float<T,bits,U>::expsmall() const {
  Float<T,bits,U> denom(1);
  Float<T,bits,U> x(*this);
  Float<T,bits,U> before(0);
  Float<T,bits,U> res(1);
  for(int t = 1; ! !((res - before).m); t ++) {
    before = res;
    res   += x / denom;
    denom *= Float<T,bits,U>(t);
    x     *= *this;
  }
  return res;
}

template <typename T, int bits, typename U> inline const vector<Float<T,bits,U> >& Float<T,bits,U>::en(const int& b) const {
  static vector<Float<T,bits,U> > ebuf;
  if(ebuf.size() < b) {
    if(! ebuf.size())
      ebuf.push_back(Float<T,bits,U>(1));
    for(int i = 1; i <= b; i ++) {
      if(! isfinite(ebuf[ebuf.size() - 1]))
        break;
      ebuf.push_back(ebuf[i - 1] * ebuf[i - 1]);
    }
  }
  return ebuf;
}

template <typename T, int bits, typename U> inline Float<T,bits,U> Float<T,bits,U>::sqrt() const {
  static const auto half(Float<T,bits,U>(1) / Float<T,bits,U>(2));
  return (this->log() * half).exp();
}

template <typename T, int bits, typename U> std::ostream& operator << (std::ostream& os, const Float<T,bits,U>& v) {
  if(! isfinite(v))
    return os << "NaN";
  return os << (const char*)(v.s & (1 << v.SIGN) ? "-" : "") << T(v.m) << "*2^" << int(v.e);
}

template <typename T, int bits, typename U> std::istream& operator >> (std::istream& is, Float<T,bits,U>& v) {
  const static Float<T,bits,U> ten(10);
               Float<T,bits,U> e(0);
  bool mode(false);
  bool sign(false);
  bool fsign(false);
  v = Float<T,bits,U>(0);
  // skip white spaces.
  while(! is.eof()) {
    const auto buf(is.get());
    if(buf != ' ' && buf != '\t') {
      is.unget();
      break;
    }
  }
  while(! is.eof() ) {
    const auto buf(is.get());
    switch(buf) {
    case '-':
      sign  = true;
    case '+':
      if(fsign)
        throw "Wrong input";
      fsign = true;
      break;
    case 'e':
      if(mode)
        goto ensure;
      if(sign)
        v   = - v;
      mode  = true;
      sign  = false;
      fsign = false;
      break;
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
      if(mode) {
        e *= ten;
        e += Float<T,bits,U>(int(buf - '0'));
      } else {
        v *= ten;
        v += Float<T,bits,U>(int(buf - '0'));
      }
      fsign = true;
      std::cerr << v << std::endl;
      break;
    default:
      goto ensure;
    }
  }
 ensure:
  if(mode && sign)
    e = - e;
  v *= pow(ten, e);
  return is;
}


template <typename T, int bits, typename U> inline bool isfinite(const Float<T,bits,U>& src) {
  return ! (src.s & ((1 << src.INF) | (1 << src.NaN)));
}

template <typename T, int bits, typename U> inline bool isnan(const Float<T,bits,U>& src) {
  return src.s & (1 << src.NaN);
}

template <typename T, int bits, typename U> inline Float<T,bits,U> ceil(const Float<T,bits,U>& src) {
  return src.ceil();
}

template <typename T, int bits, typename U> inline Float<T,bits,U> abs(const Float<T,bits,U>& src) {
  return src.abs();
}

template <typename T, int bits, typename U> inline Float<T,bits,U> sqrt(const Float<T,bits,U>& src) {
  return src.sqrt();
}

template <typename T, int bits, typename U> inline Float<T,bits,U> exp(const Float<T,bits,U>& src) {
  return src.exp();
}

template <typename T, int bits, typename U> inline Float<T,bits,U> log(const Float<T,bits,U>& src) {
  return src.log();
}

template <typename T, int bits, typename U> inline Float<T,bits,U> pow(const Float<T,bits,U>& src, const Float<T,bits,U>& dst) {
  if(! dst)
    return Float<T,bits,U>(1);
  return exp(log(src) * dst);
}

#define _INTEGER_FLOAT_
#endif

