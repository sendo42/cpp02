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


bool Fixed::operator>(const Fixed &other)
{
    return this->FixedPointNum_ > other.FixedPointNum_;
}

bool Fixed::operator<(const Fixed &other)
{
    return this->FixedPointNum_ < other.FixedPointNum_;
}

bool Fixed::operator>=(const Fixed &other)
{
    return this->FixedPointNum_ >= other.FixedPointNum_;
}

bool Fixed::operator<=(const Fixed &other)
{
    return this->FixedPointNum_ <= other.FixedPointNum_;
}

bool Fixed::operator==(const Fixed &other)
{
    return this->FixedPointNum_ == other.FixedPointNum_;
}

bool Fixed::operator!=(const Fixed &other)
{
    return this->FixedPointNum_ != other.FixedPointNum_;
}


Fixed Fixed::operator+(const Fixed &other)
{
    Fixed result;
    result.FixedPointNum_ = this->FixedPointNum_ + other.FixedPointNum_;
    return result;
}

Fixed Fixed::operator-(const Fixed &other)
{
    Fixed result;
    result.FixedPointNum_ = this->FixedPointNum_ - other.FixedPointNum_;
    return result;
}

Fixed Fixed::operator*(const Fixed &other)
{
    Fixed result;
    result.FixedPointNum_ = this->FixedPointNum_ * other.FixedPointNum_;
    std::cout << result.FixedPointNum_ << ' ' << this->FixedPointNum_ << ' ' << other.FixedPointNum_ << ' '<< std::endl;
    result.FixedPointNum_ = result.FixedPointNum_ / (1 << eightbits_); 
    return result.toFloat();
}

Fixed Fixed::operator/(const Fixed &other)
{
    Fixed result;
    float temp;

    temp = this->FixedPointNum_;
    temp /= 256;
    std::cout << temp << std::endl;
    
    temp = other.FixedPointNum_;
    std::cout <<  temp/256 << std::endl;
    result.FixedPointNum_ = (this->FixedPointNum_ / other.FixedPointNum_);
    std::cout << "zyo" << std::endl;
    return result;
}


Fixed Fixed::operator++(int)
{
    this->FixedPointNum_++;
    return *this;
}

Fixed Fixed::operator--(int)
{
    this->FixedPointNum_--;
    return *this;
}


Fixed &Fixed::operator++()
{
    this->FixedPointNum_++;
    return *this;
}

Fixed &Fixed::operator--()
{
    this->FixedPointNum_--;
    return *this;
}


Fixed &Fixed::min(Fixed &obj1, Fixed &obj2)
{
    if(obj1 > obj2)
        return obj2;
    else
        return obj1;
}

const Fixed &Fixed::min(const Fixed &obj1, const Fixed &obj2)
{
    if(obj1.getRawBits() > obj2.getRawBits())
        return obj2;
    else
        return obj1;
}


Fixed &Fixed::max(Fixed &obj1, Fixed &obj2)
{
    if(obj1 < obj2)
        return obj2;
    else
        return obj1;
}

const Fixed &Fixed::max(const Fixed &obj1, const Fixed &obj2)
{
    if(obj1.getRawBits() < obj2.getRawBits())
        return obj2;
    else
        return obj1;
}


std::ostream& operator<<(std::ostream& os, const Fixed &obj)
{
    os << obj.toFloat();
    return os;
}




