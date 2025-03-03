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
    FixedPointNum_ =  std::round(num *(1 << eightbits_));
}

Fixed::~Fixed()
{
    std::cout << "Destructor called" << std::endl;
}

Fixed::Fixed(const Fixed& fixed)
{
    std::cout << "Copy constructor called" << std::endl;
    this->FixedPointNum_ = fixed.FixedPointNum_;
}

Fixed &Fixed::operator=(const Fixed &fixed)
{
    std::cout << "Copy assignment operator called" << std::endl;
    if(this != &fixed)
    {
        this->FixedPointNum_ = fixed.getRawBits();
    }
    return *this;
}

int Fixed::getRawBits() const
{
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


bool Fixed::operator>(const Fixed &other) const
{
    return this->FixedPointNum_ > other.FixedPointNum_;
}

bool Fixed::operator<(const Fixed &other) const
{
    return this->FixedPointNum_ < other.FixedPointNum_;
}

bool Fixed::operator>=(const Fixed &other) const
{
    return this->FixedPointNum_ >= other.FixedPointNum_;
}

bool Fixed::operator<=(const Fixed &other) const
{
    return this->FixedPointNum_ <= other.FixedPointNum_;
}

bool Fixed::operator==(const Fixed &other) const
{
    return this->FixedPointNum_ == other.FixedPointNum_;
}

bool Fixed::operator!=(const Fixed &other) const
{
    return this->FixedPointNum_ != other.FixedPointNum_;
}


Fixed Fixed::operator+(const Fixed &other) const
{
    Fixed temp(*this);

    temp.FixedPointNum_ = this->FixedPointNum_ + other.FixedPointNum_;
    return temp;
}

Fixed Fixed::operator-(const Fixed &other) const
{
    Fixed temp(*this);

    temp.FixedPointNum_ = this->FixedPointNum_ - other.FixedPointNum_;
    return temp;
}

Fixed Fixed::operator*(const Fixed &other) const
{
    Fixed temp(*this);

    temp.FixedPointNum_ = (this->FixedPointNum_ * other.FixedPointNum_) >> this->eightbits_;
    return temp.toFloat();
}

Fixed Fixed::operator/(const Fixed &other) const
{
    Fixed temp(*this);

    temp.FixedPointNum_ = ((float )this->FixedPointNum_ / other.FixedPointNum_) * (1 << this->eightbits_);
    return temp.toFloat();
}


Fixed Fixed::operator++(int)
{
    Fixed tmp(*this);
    this->FixedPointNum_++;
    return tmp;
}

Fixed Fixed::operator--(int)
{
    Fixed tmp(*this);
    this->FixedPointNum_--;
    return tmp;
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




