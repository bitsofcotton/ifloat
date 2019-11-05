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
  // ... ==
  // d0 * s0 + (d0 * s1 + s0 * d1) * p1 +
  //   (d0 * s2 + d2 * s0 + d1 * s1) * p2 +
  //   (d0 * s3 + d2 * s1 + d1 * s2 + d3 * s0) * p3
  // N.B. not used:
  //   dk * sl + dl * sk == dk * sk + sl * dl - (dk - dl) * (sk - sl)
  return DUInt<T,bits>(d0 * s0) +
       ((DUInt<T,bits>(s0 * d1) + DUInt<T,bits>(s1 * d0)) << hbits) +
       (DUInt<T,bits>(s0 * d2 + s2 * d0 + s1 * d1) << bits) +
       (DUInt<T,bits>(s0 * d3 + s3 * d0 + s1 * d2 + s2 * d1) << (bits + hbits));
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
  if(! *this)
    return *this;
  int shift(0);
  if(! src.e[1]) {
    if(! src.e[0])
      throw "Zero division";
    for(int i = 0; i < bits; i ++)
      if(int(src.e[0] >> i) & 1)
        shift = i;
  } else {
    for(int i = 0; i < bits; i ++)
      if(int(src.e[1] >> i) & 1)
        shift = i + bits;
  }
  const auto dblocks(shift / hbits + 1);
  const auto lshift(dblocks * hbits - shift - 1);
  assert(0 <= lshift && lshift < hbits && !((shift + lshift + 1) % hbits));
  const auto dd(src << lshift);
  const auto dlast((dblocks - 1) & 1 ? dd.e[(dblocks - 1) >> 1] >> hbits
                                     : dd.e[(dblocks - 1) >> 1] &  lmask);
  assert(dlast);
  int ltshift(0);
  if(! e[1]) {
    for(int i = 0; i < bits; i ++)
      if(int(e[0] >> i) & 1)
        ltshift = i;
  } else {
    for(int i = 0; i < bits; i ++)
      if(int(e[1] >> i) & 1)
        ltshift = i + bits;
  }
  ltshift = bits * 2 - 1 - ltshift;
  *this <<= ltshift;
  assert(*this);
  // N.B.
  //   block division with better condition.
  //   de[0] ... de[n], de[n] = 0...1..., each de uses half of space.
  //                                ^ hbits - 1
  //   dlast := de[n].
  //   res = *this / (src == dd >> lshift ~= (dlast << ...))
  auto res(src ^ src);
  auto div(res);
  auto d(e[0] ^ e[0]);
  for(int i = 2; - 1 <= i; i --) {
    switch(i) {
    case - 1:
      d =  (e[0] << hbits) / dlast;
      break;
    case 0:
      d =   e[0] / dlast;
      break;
    case 1:
      d = ((e[0] >> hbits) | (e[1] << hbits)) / dlast;
      break;
    case 2:
      d =   e[1] / dlast;
      break;
    default:
      assert(0 && "Should not be reached.");
    }
    // N.B.
    //   d(0)  := original.
    //   d(k+1) = (d << tshift) * src + r + d(k) == orig.
    //   ( |r| < |src|, ((d << tshift) * src) <= orig - d(k) )
    const auto tshift(hbits * i + lshift - (dblocks - 1) * hbits);
    div = (DUInt<T,bits>(d) * src) << tshift;
    for(int j = 0; j < 4 && ! (div <= *this); j ++) {
      -- d;
      div = (DUInt<T,bits>(d) * src) << tshift;
    }
    assert(div <= *this);
    *this -= div;
    res   += DUInt<T,bits>(d) << tshift;
  }
  return *this = (res >>= ltshift);
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
  if(! b)
    return *this;
  else if(b < 0)
    return *this >>= (- b);
  else if(b > bits * 2)
    return *this ^= *this;
  else if(b > bits) {
    e[1]  = e[0] << (b - bits);
    e[0] ^= e[0];
  } else if(b == bits) {
    e[1]  = e[0];
    e[0] ^= e[0];
  } else {
    e[1] <<= b;
    e[1]  |= e[0] >> (bits - b);
    e[0] <<= b;
  }
  return *this;
}

template <typename T, int bits> inline DUInt<T,bits>  DUInt<T,bits>::operator >> (const int& b)             const {
  auto work(*this);
  return work >>= b;
}

template <typename T, int bits> inline DUInt<T,bits>& DUInt<T,bits>::operator >>= (const int& b) {
  if(! b)
    return *this;
  else if(b < 0)
    return *this <<= (- b);
  else if(b > bits * 2)
    return *this ^= *this;
  else if(b > bits) {
    e[0]  = e[1] >> (b - bits);
    e[1] ^= e[1];
  } else if(b == bits) {
    e[0]  = e[1];
    e[1] ^= e[1];
  } else {
    e[0] >>= b;
    e[0]  |= e[1] << (bits - b);
    e[1] >>= b;
  }
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
  return ! (*this - src);
}

template <typename T, int bits> inline bool      DUInt<T,bits>::operator != (const DUInt<T,bits>& src) const {
  return ! (*this == src);
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
  return int(e[0]);
}

template <typename T, int bits> std::ostream&  operator << (std::ostream& os, DUInt<T,bits> v) {
  static const DUInt<T,bits> ten(10);
  vector<char> buf;
  while(v) {
    const auto div(v / ten);
    buf.push_back(int(v - div * ten));
    v = div;
  }
  if(buf.size()) {
    for(int i = 0; i < buf.size(); i ++)
      os << int(buf[buf.size() - 1 - i]);
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


template <typename T, int bits, typename U> class SimpleFloat {
public:
  inline SimpleFloat();
  inline SimpleFloat(const int& src);
  inline SimpleFloat(const SimpleFloat<T,bits,U>& src);
  inline SimpleFloat(SimpleFloat<T,bits,U>&& src);
  inline ~SimpleFloat();
  
  inline SimpleFloat<T,bits,U>  operator -  () const;
  inline SimpleFloat<T,bits,U>  operator +  (const SimpleFloat<T,bits,U>& src) const;
         SimpleFloat<T,bits,U>& operator += (const SimpleFloat<T,bits,U>& src);
  inline SimpleFloat<T,bits,U>  operator -  (const SimpleFloat<T,bits,U>& src) const;
  inline SimpleFloat<T,bits,U>& operator -= (const SimpleFloat<T,bits,U>& src);
  inline SimpleFloat<T,bits,U>  operator *  (const SimpleFloat<T,bits,U>& src) const;
         SimpleFloat<T,bits,U>& operator *= (const SimpleFloat<T,bits,U>& src);
  inline SimpleFloat<T,bits,U>  operator /  (const SimpleFloat<T,bits,U>& src) const;
         SimpleFloat<T,bits,U>& operator /= (const SimpleFloat<T,bits,U>& src);
  inline SimpleFloat<T,bits,U>  operator <<  (const U& b) const;
  inline SimpleFloat<T,bits,U>& operator <<= (const U& b);
  inline SimpleFloat<T,bits,U>  operator >>  (const U& b) const;
  inline SimpleFloat<T,bits,U>& operator >>= (const U& b);
  inline SimpleFloat<T,bits,U>& operator =  (const SimpleFloat<T,bits,U>& src);
  inline SimpleFloat<T,bits,U>& operator =  (SimpleFloat<T,bits,U>&& src);
  inline bool             operator == (const SimpleFloat<T,bits,U>& src) const;
  inline bool             operator != (const SimpleFloat<T,bits,U>& src) const;
  inline bool             operator <  (const SimpleFloat<T,bits,U>& src) const;
  inline bool             operator <= (const SimpleFloat<T,bits,U>& src) const;
  inline bool             operator >  (const SimpleFloat<T,bits,U>& src) const;
  inline bool             operator >= (const SimpleFloat<T,bits,U>& src) const;
  inline bool             operator !  () const;
  inline                  operator bool () const;
  inline                  operator int  () const;
  inline SimpleFloat<T,bits,U>  floor() const;
  inline SimpleFloat<T,bits,U>  abs()  const;
         SimpleFloat<T,bits,U>  log()  const;
         SimpleFloat<T,bits,U>  exp()  const;
  inline SimpleFloat<T,bits,U>  sqrt() const;
  inline SimpleFloat<T,bits,U>  logsmall() const;
  inline SimpleFloat<T,bits,U>  expsmall() const;
  
/*
  friend std::ostream&    operator << (std::ostream& os, const SimpleFloat<T,bits,U>& v);
  friend std::istream&    operator >> (std::istream& is, SimpleFloat<T,bits,U>& v);
*/
  
  unsigned char s;
  typedef enum {
    INF = 0,
    NaN = 1,
    SIGN = 2,
    DWRK = 3
  } state_t;
  T m;
  U e;
private:
  template <typename V> inline int normalize(V& src) const;
  inline bool prepMul(const SimpleFloat<T,bits,U>& src);
  inline unsigned char safeAdd(U& dst, const U& src);
  inline char residue2() const;

  const vector<SimpleFloat<T,bits,U> >& exparray() const;
  const vector<SimpleFloat<T,bits,U> >& invexparray() const;
};

template <typename T, int bits, typename U> inline SimpleFloat<T,bits,U>::SimpleFloat() {
  assert(0 < bits && ! (bits & 1));
  s ^= s;
  m ^= m;
  e ^= e;
}

template <typename T, int bits, typename U> inline SimpleFloat<T,bits,U>::SimpleFloat(const int& src) {
  s ^= s;
  m  = std::abs(src);
  e ^= e;
  s |= safeAdd(e, normalize(m));
  if(src < 0)
    s |= 1 << SIGN;
}

template <typename T, int bits, typename U> inline SimpleFloat<T,bits,U>::SimpleFloat(const SimpleFloat<T,bits,U>& src) {
  *this = src;
}

template <typename T, int bits, typename U> inline SimpleFloat<T,bits,U>::SimpleFloat(SimpleFloat<T,bits,U>&& src) {
  *this = src;
}

template <typename T, int bits, typename U> inline SimpleFloat<T,bits,U>::~SimpleFloat() {
  ;
}

template <typename T, int bits, typename U> inline SimpleFloat<T,bits,U> SimpleFloat<T,bits,U>::operator -  () const {
  auto work(*this);
  work.s ^= 1 << SIGN;
  return work;
}

template <typename T, int bits, typename U> inline SimpleFloat<T,bits,U> SimpleFloat<T,bits,U>::operator +  (const SimpleFloat<T,bits,U>& src) const {
  auto work(*this);
  return work += src;
}

template <typename T, int bits, typename U>        SimpleFloat<T,bits,U>& SimpleFloat<T,bits,U>::operator += (const SimpleFloat<T,bits,U>& src) {
  s |= src.s & ((1 << INF) | (1 << NaN));
  if(! m) {
    m = src.m;
    e = src.e;
    s = src.s;
    return *this;
  }
  if(! src.m)
    return *this;
  if(! ((s & (1 << SIGN)) ^ (src.s & (1 << SIGN)))) {
    if(e >= src.e) {
      m >>= 1;
      s |= safeAdd(e, 1);
      U se(e);
      if(! safeAdd(se, - src.e) && se < bits)
        m += src.m >> se;
    } else
      return *this = src + *this;
  } else {
    if(e > src.e) {
      U se(e);
      if(! safeAdd(se, - src.e) && se < bits)
        m -= src.m >> se;
    } else if(e == src.e) {
      if(m >= src.m)
        m -= src.m;
      else
        return *this = src + *this;
    } else
      return *this = src + *this;
  }
  s |= safeAdd(e, normalize(m));
  if(!m || (s & (1 << DWRK))) {
    m ^= m;
    e ^= e;
    s &= ~ (1 << DWRK);
  }
  return *this;
}

template <typename T, int bits, typename U> inline SimpleFloat<T,bits,U> SimpleFloat<T,bits,U>::operator -  (const SimpleFloat<T,bits,U>& src) const {
  auto work(*this);
  return work -= src;
}

template <typename T, int bits, typename U> inline SimpleFloat<T,bits,U>& SimpleFloat<T,bits,U>::operator -= (const SimpleFloat<T,bits,U>& src) {
  return *this += - src;
}

template <typename T, int bits, typename U> inline SimpleFloat<T,bits,U> SimpleFloat<T,bits,U>::operator *  (const SimpleFloat<T,bits,U>& src) const {
  auto work(*this);
  return work *= src;
}

template <typename T, int bits, typename U>        SimpleFloat<T,bits,U>& SimpleFloat<T,bits,U>::operator *= (const SimpleFloat<T,bits,U>& src) {
  if(! prepMul(src))
    return *this;
  if((! m) || (! src.m)) {
    m ^= m;
    e ^= e;
    return *this;
  }
  auto mm(DUInt<T,bits>(m) * DUInt<T,bits>(src.m));
  s |= safeAdd(e, src.e);
  s |= safeAdd(e, normalize(mm));
  s |= safeAdd(e, bits);
  m  = mm.e[1];
  if(s & (1 << DWRK)) {
    e ^= e;
    m ^= m;
    s &= ~ (1 << DWRK);
  }
  return *this;
}

template <typename T, int bits, typename U> inline char SimpleFloat<T,bits,U>::residue2() const {
  if(bits <= std::abs(e))
    return 0;
  if(e < 0)
    return char(int(m >> std::abs(e)) & 1);
  return char(int(m << e) & 1);
}

template <typename T, int bits, typename U> inline SimpleFloat<T,bits,U> SimpleFloat<T,bits,U>::operator /  (const SimpleFloat<T,bits,U>& src) const {
  auto work(*this);
  return work /= src;
}

template <typename T, int bits, typename U>        SimpleFloat<T,bits,U>& SimpleFloat<T,bits,U>::operator /= (const SimpleFloat<T,bits,U>& src) {
  if(! prepMul(src))
    return *this;
  if(! src.m) {
    s |= 1 << NaN;
    return *this;
  }
  if(! m)
    return *this;
  auto mm((DUInt<T,bits>(m) << bits) / DUInt<T,bits>(src.m));
  s |= safeAdd(e, - src.e);
  s |= safeAdd(e, normalize(mm));
  m  = mm.e[1];
  if(s & (1 << DWRK)) {
    e ^= e;
    m ^= m;
    s &= ~ (1 << DWRK);
  }
  return *this;
}

template <typename T, int bits, typename U> inline SimpleFloat<T,bits,U>  SimpleFloat<T,bits,U>::operator <<  (const U& b) const {
  auto work(*this);
  return work <<= b;
}

template <typename T, int bits, typename U> inline SimpleFloat<T,bits,U>& SimpleFloat<T,bits,U>::operator <<= (const U& b) {
  s |= safeAdd(e, b);
  return *this;
}

template <typename T, int bits, typename U> inline SimpleFloat<T,bits,U>  SimpleFloat<T,bits,U>::operator >>  (const U& b) const {
  auto work(*this);
  return work >>= b;
}

template <typename T, int bits, typename U> inline SimpleFloat<T,bits,U>& SimpleFloat<T,bits,U>::operator >>= (const U& b) {
  s |= safeAdd(e, - b);
  return *this;
}

template <typename T, int bits, typename U> inline SimpleFloat<T,bits,U>& SimpleFloat<T,bits,U>::operator =  (const SimpleFloat<T,bits,U>& src) {
  s = src.s;
  e = src.e;
  m = src.m;
  return *this;
}

template <typename T, int bits, typename U> inline SimpleFloat<T,bits,U>& SimpleFloat<T,bits,U>::operator =  (SimpleFloat<T,bits,U>&& src) {
  s = move(src.s);
  e = move(src.e);
  m = move(src.m);
  return *this;
}

template <typename T, int bits, typename U> inline bool             SimpleFloat<T,bits,U>::operator == (const SimpleFloat<T,bits,U>& src) const {
  return ! (*this != src);
}

template <typename T, int bits, typename U> inline bool             SimpleFloat<T,bits,U>::operator != (const SimpleFloat<T,bits,U>& src) const {
  return s != src.s || e != src.e || m != src.m;
}

template <typename T, int bits, typename U> inline bool             SimpleFloat<T,bits,U>::operator <  (const SimpleFloat<T,bits,U>& src) const {
  if((s & (1 << SIGN)) ^ (src.s & (1 << SIGN)))
    return s & (1 << SIGN);
  if(s & (1 << SIGN))
    return - *this > - src;
  return (!m ? (!src.m ? false : true) : (!src.m ? false : (e < src.e ? true : (e == src.e ? m < src.m : false))));
}

template <typename T, int bits, typename U> inline bool             SimpleFloat<T,bits,U>::operator <= (const SimpleFloat<T,bits,U>& src) const {
  return *this < src || *this == src;
}

template <typename T, int bits, typename U> inline bool             SimpleFloat<T,bits,U>::operator >  (const SimpleFloat<T,bits,U>& src) const {
  return ! (*this <= src);
}

template <typename T, int bits, typename U> inline bool             SimpleFloat<T,bits,U>::operator >= (const SimpleFloat<T,bits,U>& src) const {
  return ! (*this < src);
}

template <typename T, int bits, typename U> inline bool             SimpleFloat<T,bits,U>::operator !  () const {
  return ! m && isfinite(*this);
}

template <typename T, int bits, typename U> inline                  SimpleFloat<T,bits,U>::operator bool () const {
  return ! (!*this);
}

template <typename T, int bits, typename U> inline                  SimpleFloat<T,bits,U>::operator int  () const {
  auto deci(*this);
  if(deci.s & ((1 << INF) || (1 << NaN)) ||
     (m && ! (deci.m <<= deci.e) ))
    throw "Overflow to convert int.";
  return deci.m;
}

template <typename T, int bits, typename U> template <typename V> inline int SimpleFloat<T,bits,U>::normalize(V& src) const {
  V   bt(1);
  int b(0);
  int tb;
  for(tb = 0; bt; tb ++) {
    if(src & bt)
      b = tb;
    bt <<= 1;
  }
  const auto shift(tb - b - 1);
  assert(0 <= shift);
  src <<= shift;
  return - shift;
}

template <typename T, int bits, typename U> inline bool SimpleFloat<T,bits,U>::prepMul(const SimpleFloat<T,bits,U>& src) {
  s ^= src.s & (1 << SIGN);
  if(! (isfinite(*this) && isfinite(src))) {
    s |= src.e & ((1 << INF) | (1 << NaN));
    return false;
  }
  return true;
}

template <typename T, int bits, typename U> inline unsigned char SimpleFloat<T,bits,U>::safeAdd(U& dst, const U& src) {
  const auto dst0(dst);
  unsigned char ss(0);
  dst += src;
  if(0 < dst0 * src && dst * src < 0) {
    if(dst < 0)
      ss |= 1 << INF;
    else
      ss |= 1 << DWRK;
  }
  return ss;
}

template <typename T, int bits, typename U> inline SimpleFloat<T,bits,U> SimpleFloat<T,bits,U>::floor() const {
  const static SimpleFloat<T,bits,U> zero(0);
  if(0 <= e)
    return *this;
  if(e <= - bits)
    return zero;
  auto deci(*this);
  deci.m >>= - deci.e;
  if(! deci.m)
    return zero;
  deci.m <<= - deci.e;
  return deci;
}

template <typename T, int bits, typename U> inline SimpleFloat<T,bits,U> SimpleFloat<T,bits,U>::abs() const {
  auto work(*this);
  work.s &= ~ (1 << SIGN);
  return work;
}

template <typename T, int bits, typename U> SimpleFloat<T,bits,U> SimpleFloat<T,bits,U>::log() const {
  const static SimpleFloat<T,bits,U> zero(0);
  const static SimpleFloat<T,bits,U> one(1);
  const static SimpleFloat<T,bits,U> einv(one / one.expsmall());
  const static SimpleFloat<T,bits,U> one_einv(one + einv);
  if(! *this) {
    auto work(*this);
    work.s |= (1 << INF) | (1 << SIGN);
    return work;
  }
  assert(zero < *this);
  if(einv <= *this && *this <= one_einv)
    return logsmall();
  SimpleFloat<T,bits,U> result(0);
        auto  work(*this);
  const auto& ea(exparray());
  const auto& iea(invexparray());
  if(one_einv < *this) {
    for(int i = ea.size() - 1; 0 < i; i --)
      if(ea[i] <= work) {
        result += one << U(i - 1);
        work   *= iea[i];
      }
    if(! (work <= one_einv)) {
      result += one;
      work   *= iea[1];
    }
  } else {
    for(int i = iea.size() - 1; 0 < i; i --)
      if(work <= iea[i]) {
        result -= one << U(i - 1);
        work   *= ea[i];
      }
    if(! (einv <= work)) {
      result -= one;
      work   *= ea[1];
    }
  }
  std::cerr << result << std::endl << work << std::endl;
  return result += work.logsmall();
}

template <typename T, int bits, typename U> SimpleFloat<T,bits,U> SimpleFloat<T,bits,U>::logsmall() const {
  const auto dx(*this - SimpleFloat<T,bits,U>(1));
  SimpleFloat<T,bits,U> x(dx);
  SimpleFloat<T,bits,U> before(1);
  SimpleFloat<T,bits,U> res(0);
  for(int t = 1; (res - before).m; t ++) {
    before = res;
    res   += x / SimpleFloat<T,bits,U>(t * pow(- 1, (t % 2) - 1));
    x     *= dx;
  }
  return res;
}

template <typename T, int bits, typename U> SimpleFloat<T,bits,U> SimpleFloat<T,bits,U>::exp() const {
  const static SimpleFloat<T,bits,U> zero(0);
  const static SimpleFloat<T,bits,U> one(1);
  const static SimpleFloat<T,bits,U> two(2);
  if(s & ((1 << INF) || (1 << NaN)))
    return *this;
  if(this->abs() <= one)
    return expsmall();
  SimpleFloat<T,bits,U> result(1);
  const auto& en(exparray());
  const auto& ien(invexparray());
        auto  work(this->abs());
        int  i;
  for(i = 1; i < en.size() && work.floor(); i ++) {
    if(work.residue2()) {
      if(s & (1 << SIGN))
        result *= ien[i];
      else
        result *= en[i];
    }
    work >>= U(1);
  }
  return result *= (*this - this->floor()).expsmall();
}

template <typename T, int bits, typename U> inline SimpleFloat<T,bits,U> SimpleFloat<T,bits,U>::expsmall() const {
  SimpleFloat<T,bits,U> denom(1);
  SimpleFloat<T,bits,U> x(*this);
  SimpleFloat<T,bits,U> before(0);
  SimpleFloat<T,bits,U> res(1);
  for(int t = 1; (res - before).m; t ++) {
    before = res;
    denom *= SimpleFloat<T,bits,U>(t);
    res   += x / denom;
    x     *= *this;
  }
  return res;
}

template <typename T, int bits, typename U> const vector<SimpleFloat<T,bits,U> >& SimpleFloat<T,bits,U>::exparray() const {
  static vector<SimpleFloat<T,bits,U> > ebuf;
  if(ebuf.size())
    return ebuf;
  ebuf.push_back(SimpleFloat<T,bits,U>(1));
  ebuf.push_back(ebuf[0].expsmall());
  for(int i = 1; 0 <= i; i ++) {
    const auto en(ebuf[ebuf.size() - 1] * ebuf[ebuf.size() - 1]);
    if(isfinite(en))
      ebuf.push_back(en);
    else
      break;
  }
  return ebuf;
}

template <typename T, int bits, typename U> const vector<SimpleFloat<T,bits,U> >& SimpleFloat<T,bits,U>::invexparray() const {
  static vector<SimpleFloat<T,bits,U> > iebuf;
  if(iebuf.size())
    return iebuf;
  const auto& ea(exparray());
  SimpleFloat<T,bits,U> one(1);
  for(int i = 0; 0 < ea.size(); i ++) {
    const auto ien(one / ea[i]);
    if(isfinite(ien))
      iebuf.push_back(ien);
    else
      break;
  }
  return iebuf;
}

template <typename T, int bits, typename U> inline SimpleFloat<T,bits,U> SimpleFloat<T,bits,U>::sqrt() const {
  if(s & ((1 << INF) | (1 << NaN)))
    return *this;
  static const auto half(SimpleFloat<T,bits,U>(1) / SimpleFloat<T,bits,U>(2));
  return (this->log() * half).exp();
}

template <typename T, int bits, typename U> std::ostream& operator << (std::ostream& os, const SimpleFloat<T,bits,U>& v) {
  if(! isfinite(v))
    return os << "NaN";
  return os << (const char*)(v.s & (1 << v.SIGN) ? "-" : "") << T(v.m) << "*2^" << int(v.e);
}

template <typename T, int bits, typename U> std::istream& operator >> (std::istream& is, SimpleFloat<T,bits,U>& v) {
  const static SimpleFloat<T,bits,U> ten(10);
               SimpleFloat<T,bits,U> e(0);
  bool mode(false);
  bool sign(false);
  bool fsign(false);
  v = SimpleFloat<T,bits,U>(0);
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
        e += SimpleFloat<T,bits,U>(int(buf - '0'));
      } else {
        v *= ten;
        v += SimpleFloat<T,bits,U>(int(buf - '0'));
      }
      fsign = true;
      break;
    default:
      goto ensure;
    }
  }
 ensure:
  if(sign) {
    if(mode)
      e = - e;
    else
      v = - v;
  }
  v *= pow(ten, e);
  return is;
}


template <typename T, int bits, typename U> inline bool isfinite(const SimpleFloat<T,bits,U>& src) {
  return ! (src.s & ((1 << src.INF) | (1 << src.NaN)));
}

template <typename T, int bits, typename U> inline bool isnan(const SimpleFloat<T,bits,U>& src) {
  return src.s & (1 << src.NaN);
}

template <typename T, int bits, typename U> inline SimpleFloat<T,bits,U> floor(const SimpleFloat<T,bits,U>& src) {
  return src.floor();
}

template <typename T, int bits, typename U> inline SimpleFloat<T,bits,U> abs(const SimpleFloat<T,bits,U>& src) {
  return src.abs();
}

template <typename T, int bits, typename U> inline SimpleFloat<T,bits,U> sqrt(const SimpleFloat<T,bits,U>& src) {
  return src.sqrt();
}

template <typename T, int bits, typename U> inline SimpleFloat<T,bits,U> exp(const SimpleFloat<T,bits,U>& src) {
  return src.exp();
}

template <typename T, int bits, typename U> inline SimpleFloat<T,bits,U> log(const SimpleFloat<T,bits,U>& src) {
  return src.log();
}

template <typename T, int bits, typename U> inline SimpleFloat<T,bits,U> pow(const SimpleFloat<T,bits,U>& src, const SimpleFloat<T,bits,U>& dst) {
  if(! dst)
    return SimpleFloat<T,bits,U>(1);
  return exp(log(src) * dst);
}

#define _INTEGER_FLOAT_
#endif

