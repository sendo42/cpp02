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
    FixedPointNum_ =  std::roundf(num * (1 << eightbits_));
}

Fixed::~Fixed()
{
    std::cout << "Destructor called" << std::endl;
}

Fixed::Fixed(const Fixed& fixed)
{
    std::cout << "Copy constructor called" << std::endl;
    // this->FixedPointNum_ = fixed.FixedPointNum_;
    *this = fixed;
}

Fixed &Fixed::operator=(const Fixed &fixed)
{
    std::cout << "Copy assignment operator called" << std::endl;
    if(this == &fixed)
        return *this;
    this->FixedPointNum_ = fixed.getRawBits();
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