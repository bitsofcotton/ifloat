# bitsofcotton/ifloat
信用できないまたは複雑すぎる浮動小数点実装または FPU が存在しない環境をラップする形で全て整数演算で演算する際のライブラリです。
とても遅いです。

# Tips
std::limits に(まだ)対応していません。

# バグ
他の実装と一緒に動かすことができるか検討中です。

# 使い方
    #include "ifloat.hh"
    ...
    typedef SimpleFloat<unsigned long long, 64, short> float_t;
    ...
      ...
      float_t a(1);
      float_t b(1);
      float_t c(a * b);
      ...
