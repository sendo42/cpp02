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
        
        bool operator>(const Fixed &other) const;
        bool operator<(const Fixed &other) const;
        bool operator>=(const Fixed &other) const;
        bool operator<=(const Fixed &other) const;
        bool operator==(const Fixed &other) const;
        bool operator!=(const Fixed &other) const;
        
        Fixed operator+(const Fixed &other) const;
        Fixed operator-(const Fixed &other) const;
        Fixed operator*(const Fixed &other) const;
        Fixed operator/(const Fixed &other) const;

        Fixed operator++(int);
        Fixed operator--(int);

        Fixed &operator++();
        Fixed &operator--();

        static Fixed &min(Fixed &obj1, Fixed &obj2);
        static const Fixed &min(const Fixed &obj1, const Fixed &obj2);

        static Fixed &max(Fixed &obj1, Fixed &obj2);
        static const Fixed &max(const Fixed &obj1, const Fixed &obj2);
    };

std::ostream& operator<<(std::ostream& os,const Fixed &obj);

#endif

/*
publicなメンバ関数に
オペレータオーバーロードを
https://rinatz.github.io/cpp-book/ch07-07-operator-overloading/

>, <, >=, <=, == and !=.
https://gist.github.com/Manuel1024/4a678ea2e7d01d764dd1086da32c1cad

+, -, *, and /.
https://learn.microsoft.com/ja-jp/cpp/cpp/operator-overloading?view=msvc-170
https://brain.cc.kogakuin.ac.jp/~kanamaru/lecture/C++2/09/09-04.html
四則演算がcopyを返すべきなのは、参照私だとスコープから外れるとストックのメモリが消えてしまうから

a++ ++a, --a, ++a
https://learn.microsoft.com/ja-jp/cpp/cpp/increment-and-decrement-operator-overloading-cpp?view=msvc-170
https://mickey24.hatenablog.com/entry/20081021/1224590753
前置か後置の書き方

https://qiita.com/YukiMiyatake/items/44bfd8b4b603950b6462
前置と後置は性質が違う。
前置は自分自身をインクリメント、
後置は簡易的に元の値を保存し、自分をインクリメントし、元の値を返す。


publicにメンバ関数を
static
min
    二つ受け取って小さい方の参照を返す
min
   オーバーロード constantなやつを受け取って返す
max
    逆
    constant

https://learn.microsoft.com/ja-jp/cpp/error-messages/compiler-errors-1/compiler-error-c2352?view=msvc-170
もしstaticをつけないと、
 error: call to non-static member function without an object argument
となる
https://www.ibm.com/docs/ja/xl-c-and-cpp-aix/13.1.0?topic=members-static-member-functions
そもそもstaticな関数とは？
https://rinatz.github.io/cpp-book/ch07-10-static-members/#static_2
static メンバ関数のメリット
https://qiita.com/omuRice/items/3c40e8dde19e276ccacf

staticなメンバ関数や変数は、
各インスタンスではなく、クラス全体で共有される。
staticメンバ関数を呼び出す時には、インスタンスのアドレスを渡さずに呼ぶ仕組みになっています
プログラム全体で共有はなく、インスタンス間でのみという共有される範囲が明確であるとうメリットがあると私は思います。

https://qiita.com/rinse_/items/9d87d5cb0dc1e89d005e
https://qiita.com/negi-drums/items/fb23e7cf77eafbfa0c3a

オーバーロードの引数の部分
const Fixed &other
か
Fixed other
ではよくて
1. Fixed &other だとエラーになる理由
演算子オーバーロードは、通常 右辺値（rvalue） にも対応できる必要があります。しかし、Fixed &other のように 「非const参照」 にすると、右辺値（Fixed(5) + Fixed(3) のような式）を受け取れず、エラーになります。

Fixed a(5);
Fixed b = a + Fixed(3);  // 右辺値 `Fixed(3)` を `Fixed &other` に渡せない
Fixed(3) は一時オブジェクト（右辺値）。
一時オブジェクトは「非const参照」に渡せない。
そのため、Fixed &other の関数には渡せず、コンパイルエラー。

const を付けることで、一時オブジェクト（右辺値）でも受け取れる。
Fixed(3) のような一時オブジェクトは const & で受けることができるため、エラーにならない。

Fixed(3) のように整数 3 を渡すと、Fixed クラスの コンストラクタ が呼ばれて Fixed 型の一時オブジェクトが作られるため、Fixed &other 以外の引数なら受け取ることができる。
これは、Fixed クラスに 整数 3 を受け取るコンストラクタ がある場合に有効です。たとえば、次のようなコンストラクタが定義されているとします。

cpp
コピーする
編集する
class Fixed {
public:
    Fixed(int value) { 
        this->FixedPointNum_ = value; 
    }
};
この場合、Fixed(3) は 整数 3 から Fixed 型を生成 するコンストラクタの呼び出しになります。
つまり、Fixed(3) は Fixed 型の一時オブジェクト（右辺値） を作るということです。

https://marycore.jp/prog/cpp/converting-constructor/
暗黙のコンストラクタ呼び出し
b(9)みたいなやつ

min を呼ぶには インスタンスが必要 になる。
例えば a.min(b) のように書かないといけない。
しかし、min(a, b) のように 2つのオブジェクトを等しい立場で比較する関数 を作りたい場合、a に依存しない形が適切。
https://ytyaru.hatenablog.com/entry/2016/08/23/215752

Fixed.cpp:155:9: error: a type specifier is required for all declarations
static &Fixed Fixed::min(Fixed &obj1, Fixed &obj2)
~~~~~~  ^

staticはクラスの定義の時しか使えない
Fixed.cpp:155:1: error: 'static' can only be specified inside the class definition
static Fixed &Fixed::min(Fixed &obj1, Fixed &obj2)
^~~~~~~
*/

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
num << eightbits_ は間違い！

num は float 型 なのに ビットシフト (<<) を行おうとしている。
<< は整数型（int, long, short など）にしか適用できない。
float に対して << を使うと、コンパイルエラーや予期しない動作の原因になる。

    return (float)FixedPointNum_ / (1 << eightbits_);

    こういう書き方しないとなぜか整数で返されちゃう。

#include <iostream>
void add(const float num) {
    std::cout << "num: " << num << std::endl;
}

int main() {
    add(567.3/234); // 整数同士の割り算
    return 0;
}


コンパイラ的にこういうのは整数で返されるらしい。

*/