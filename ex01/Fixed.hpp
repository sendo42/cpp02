#ifndef __FIXED_HPP__
#define __FIXED_HPP__

#include <iostream>

class Fixed
{
    private:
        int FixedPointNum_;
        static const int eightbits_ = 8;
    public:
        Fixed();
        Fixed(const int num);
        Fixed(const float num);
        ~Fixed();
        Fixed(const Fixed& fixed);
        Fixed &operator=(const Fixed &fixed);

        int getRawBits() const;
        void setRawBits(int const raw);

        float toFloat(void ) const;
        int toInt(void) const;

        friend std::ostream& operator<<(std::ostream& os,const Fixed &obj);

};

#endif

/*
42.42fのような引数が使われている。
floating-point number浮動小数点である。
それを固定小数点に変換する。

const メンバ関数とは
https://flat-leon.hatenablog.com/entry/cpp_const_member_function
メンバ関数の右側にconstをつけうrと、
そのメンバ関数ないではメンバ変数の変更ができなくなる。
つまり。メンバ変数を変えたくない時に使う。

https://www.ibm.com/docs/ja/i/7.3?topic=only-user-defined-conversions-c
オブジェクト自体が変数ってどういうことや？

Overloading the << Operator for Your Own Classes
これが近い。
https://learn.microsoft.com/en-us/cpp/standard-library/overloading-the-output-operator-for-your-own-classes?view=msvc-170
https://docs.oracle.com/cd/E19957-01/805-7889/z4000016dc5a6/index.html
https://cpp-lang.sevendays-study.com/ex-day7.html

https://learn.microsoft.com/ja-jp/cpp/cpp/operator-overloading?view=msvc-170
operatorとは？
http://stlalv.la.coocan.jp/Operator.html
これはすごいわかりやすい。operatorの概念とその使い方がわかる。
C++ でマニアックといえば、オペレータのオーバーロードは絶対に外せない存在です。オペレータを自然に使いこなせるようにならないと、C++ を C++ らしく使えないといっても過言ではない存在です。
operator キーワードは、クラスのインスタンスに適用されたときの operator-symbol の意味を指定する関数を宣言します。 これによって、演算子に複数の意味を与えます (つまり、"オーバーロード" します)。 コンパイラは、オペランドの型を検査することにより、演算子の異なる意味を区別します。
operator<< は、最初の引数として ostream& (ostream への参照) を受け取り、同じ ostream を返します。このため、次のように 1 つの文で挿入演算子を続けて使用することができます。


operatorはFixed::operatorとすると、コンパイルされない。
error: overloaded 'operator<<' must be a binary operator (has 3 parameters)
https://stackoverflow.com/questions/23335209/error-overloaded-operator-must-be-a-binary-operator-has-3-parameters
これが原因
https://www.reddit.com/r/cpp_questions/comments/3lc6om/operator_must_be_a_binary_operator_has_3/
直接的ではないが、メンバ関数にいれるなら、引数の数を考える必要がある。
https://stackoverflow.com/questions/42521787/overloading-operator-must-be-a-binary-operator/42521809
friendをつけるとメンバ関数に入れる。

friendとは
https://learn.microsoft.com/ja-jp/cpp/cpp/friend-cpp?view=msvc-170
https://programgenjin.hatenablog.com/entry/2019/04/04/084204
C++ではクラスの外部で定義した関数をクラスのprivateメンバにアクセスできるようにすることができます。
そのような関数をフレンド関数と呼びます。friend修飾子を使ってフレンド関数を作ることができます。フレンド関数はクラスのメンバ関数になる訳ではないことに注意。

https://teratail.com/questions/304567
浮動小数<->固定小数
https://azelpg.gitlab.io/azsky2/note/prog/paint/004_fixedarith.html
これわかりやすい

https://qiita.com/qiita_kuru/items/7f12e8f29058c3141f08
https://qiita.com/choo/items/e40d52f983945708e6ae
浮動小数店の限界と定義、ビット円山load

std::round(num * (1 << eightbits_));
こういう書き方じゃないとだめ
num << eightbits_
だとinvalidになる。演算の型がちがうから
    return (float)FixedPointNum_ / (1 << eightbits_);

    こういう書き方しないとなぜか整数で返されちゃう。
*/