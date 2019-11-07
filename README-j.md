# bitsofcotton/ifloat
信用できないまたは複雑すぎる浮動小数点実装または FPU が存在しない環境をラップする形で全て整数演算で演算する際のライブラリです。
とても遅いです。また、gcc または clang には -msoft-float というとても良いオプションがあります。煩雑さの回避にははじめにそれを試すべきです。
これは簡単な構造を仮定した整数を浮動小数点数として扱うクラスです。

# Tips
std::limits に(まだ)対応していません。std::complex とは現状うまく動きません。  
AMD64 の処理系ととある実装によっては xmm0 レジスタの信頼性が損なわれる危険性がある場合があります。
その場合には clang に -mno-sse などの複数のオプションを付加して、簡易的にそれが影響しているかをデバグできます。

# 使い方
    #include "ifloat.hh"
    ...
    typedef SimpleFloat<unsigned long long, DUInt<unsigned long long, 64>, 64, short> float_t;
    ...
      ...
      float_t a(1);
      float_t b(1);
      float_t c(a * b);
      ...
