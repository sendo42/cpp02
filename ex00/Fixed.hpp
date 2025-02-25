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
        ~Fixed();
        Fixed(const Fixed& fixed);
        Fixed &operator=(const Fixed &fixed);

        int getRawBits() const;
        void setRawBits(int const raw);
};

#endif

/*

この課題の目的は固定小数点を作ること。


https://rinatz.github.io/cpp-book/ch07-05-constructors/
デフォルトコンストラクタは
値を1つも受け取らないコンストラクタをデフォルトコンストラクタといいます。

コピーコンストラクタとは？
そのクラスの参照だけを受け取るコンストラクタをコピーコンストラクタといいます。
https://brain.cc.kogakuin.ac.jp/~kanamaru/lecture/C++2/09/09-03.html

class Copyable {
 public:
    Copyable();  // デフォルトコンストラクタ
    Copyable(const Copyable& c);  // コピーコンストラクタ
};

https://rinatz.github.io/cpp-book/ch07-08-assignment-operator/
copy assignment operator overload.
コピー代入演算子

https://qiita.com/luftfararen/items/1de032bc6e3eb69ca672
右辺値左辺値とは？


コピーコンストラクタは、クラスのプロパティとメソッドのみをコピーし、その値はコピーしません
クラスのパラメーター（属性）の値をコピーするには、各パラメータをコピーコンストラクタに追加し、以下のように設定する必要があります。
myclass(const myclass& a) // Copy Constructor
{
   param = a.param; // we need to copy properties as in here
};

コピー代入演算子は、動的メモリとかで二重解放やデータ破損を防ぐために使われる。

https://www.ibm.com/docs/ja/i/7.4?topic=only-overloading-assignments-c
https://www.ibm.com/docs/ja/i/7.4?topic=only-copy-assignment-operators-c#cplr392

https://brain.cc.kogakuin.ac.jp/~kanamaru/lecture/C++2/09/09-03.html
コピー代入演算子　オーバーロード

https://www.ibm.com/docs/ja/i/7.3?topic=only-static-data-members-c
クラスのメンバー・リストにおける静的データ・メンバーの宣言は、定義ではありません。
静的メンバーは、ネーム・スペース・スコープのクラス宣言の外側で定義することが必要です。
class X
{
public:
   static int i;
};
int X::i = 0; // definition outside class declaration

初めて気づいたけど、thisはなくてもいい
基本的に動的確保だったり、非静的なものに使う

コピーコンストラクタはなぜ必要か？
https://zenn.dev/masahiro_toba/articles/c66972e20d6ee7
コピーコンストラクタが必要になるのは「クラスが外部の資源を管理するとき」です。
具体的には「クラスがポインタを持っていた場合」などです。
「アドレスの共有・勝手な書き換え」が問題になるのは、クラスの管理する資源が外部ある場合です。
わかりやすいのがクラス内にポインタがある場合です。
コピーコンストラクタが使えるのは初期化のときだけで、代入には使えない。

結論からいえば、
初期化：コピーコンストラクタ
代入：演算子のオーバーロード
と、それぞれ別々の仕組みで「外部資源の共有」という問題に対処する必要があります。
コピーコンストラクタは「初期化」の際に、外部資源の共有問題へ対処するために必要な仕組みです。
しかし「代入」にコピーコンストラクタを使うことはできません。
代入の際にも資源の勝手な書き換えを防ぎたい場合、演算子のオーバーロードの仕組みが必要となります。



Default constructor called     Fixed a;
Copy constructor called     Fixed b( a );
Copy assignment operator called // <-- This line may be missing depending on your implementation
Fixed::Fixed(const Fixed& fixed)
{
    std::cout << "Copy constructor called" << std::endl;
    *this = fixed; //こう実装しようとすると、コピー代入演算子を呼べるが、なぜかFixedvalue が1になってしまう。
    
}


getRawBits member function called
Default constructor called        Fixed c;
Copy assignment operator called     c = b;
getRawBits member function called


ここから下は単純
getRawBits member function called
0
getRawBits member function called
1
getRawBits member function called
0
Destructor called
Destructor called
Destructor called

*/