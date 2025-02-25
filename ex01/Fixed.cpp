#include "Fixed.hpp"


Fixed::Fixed()
{
    std::cout << "Default constructor called" << std::endl;
    FixedPointNum_ = 0;
}

Fixed::Fixed(const int num)
{
    std::cout << "Int constructor called" << std::endl;
    FixedPointNum_ = num  << eightbits_;
}

Fixed::Fixed(const float num)
{
    std::cout << "Float constructor called" << std::endl;
    FixedPointNum_ =  std::round(num * (1 << eightbits_));
}

Fixed::~Fixed()
{
    std::cout << "Destructor called" << std::endl;
}

Fixed::Fixed(const Fixed& fixed)
{
    std::cout << "Copy constructor called" << std::endl;
    if(this != &fixed)
    {
        *this = fixed;
    }
    // FixedPointNum_ = fixed.getRawBits();
}

Fixed &Fixed::operator=(const Fixed &fixed)
{
    std::cout << "Copy assignment operator called" << std::endl;
    if(this != &fixed)
    {
        FixedPointNum_ = fixed.getRawBits();
    }
    return *this;
}

int Fixed::getRawBits() const
{
    // std::cout << "getRawBits member function called" << std::endl;
    return FixedPointNum_;
}

void Fixed::setRawBits(int const raw)
{
    FixedPointNum_ = raw;
}

float Fixed::toFloat(void) const
{
    return (float)FixedPointNum_ / (1 << eightbits_);
}

int Fixed::toInt(void) const
{
    return FixedPointNum_ >> eightbits_;
}

std::ostream& operator<<(std::ostream& os, const Fixed &obj)
{
    os << obj.toFloat();
    return os;
}