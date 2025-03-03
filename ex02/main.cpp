#include "Fixed.hpp"

int main( void )
{
    Fixed a;
    Fixed const b( Fixed( 5.05f ) * Fixed( 2 ) );

    std::cout << a << std::endl;
    std::cout << ++a << std::endl;
    std::cout << a << std::endl;
    std::cout << a++ << std::endl;
    std::cout << a + b << std::endl;
    std::cout << b << std::endl;
    std::cout << Fixed::max( a, b ) << std::endl;
    std::cout << Fixed( 5.05f ) * Fixed( 2 ) << std::endl;

    Fixed c(3.04f);
    Fixed d(2.16f);

    std::cout << c << std::endl;
    
    std::cout << c + d << std::endl;
    std::cout << c - d << std::endl;
    std::cout << c * d << std::endl;
    std::cout << c / d << std::endl;

    std::cout << (c > d) << std::endl;
    std::cout << (c < d) << std::endl;
    std::cout << (c >= d) << std::endl;
    std::cout << (c <= d) << std::endl;
    std::cout << (c != d) << std::endl;
    std::cout << (c == d) << std::endl;

    return 0;
}
