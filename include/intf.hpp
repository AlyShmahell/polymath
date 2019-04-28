#include <iostream>
#include <vector>
#include <time.h>

#ifndef INTF_H_
#define INTF_H_


class intf;


template<typename int_t>
struct finite_division_result
{
    static_assert(std::is_base_of<intf, int_t>::value,
                  "value is non-intf.");
    int_t quotient;
    int_t remainder;
    friend std::ostream& operator<<(std::ostream& out,
                                    const finite_division_result& other)
    {
        out<<other.quotient
           <<", "
           <<other.remainder
           <<std::endl;
    }
};


template<typename int_t>
struct integral_division_result
{
    static_assert(std::is_integral<int_t>::value,
                  "value is non-integral.");
    int_t quotient;
    int_t remainder;
    friend std::ostream& operator<<(std::ostream& out,
                                    const integral_division_result& other)
    {
        out<<other.quotient
           <<", "
           <<other.remainder
           <<std::endl;
    }
};


template <typename int_t>
inline static integral_division_result<int_t> integral_division(int_t numerator,
                                                                int_t denominator)
{
    static_assert(std::is_integral<int_t>::value,
                  "value is non-integral.");
    integral_division_result<int_t> result;
    result.quotient = numerator / denominator;
    result.remainder = numerator % denominator;
    return result;
}


class intf
{

private:
    /**
     * Internal Values
     */
    bool sign;
    std::vector<int> digits;
    /**
     * Internal Functions
     */
    void snake(const std::string& s);
    void pacman();
    void twenty48();
    /**
     * Legacy Functions (To be phased out later)
     */
    friend intf divide_approximately(intf numerator, intf denominator);
    friend std::vector<intf> divide_slowly(intf numerator, intf denominato);
    /**
     * IO Functions
     */
    friend std::istream& operator>>(std::istream &input, intf &other);
    friend std::ostream& operator<<(std::ostream &output, const intf &other);
    /**
     * Math Functions
     */
    template<typename int_t, typename int_u>
    friend intf pow(const int_t base, const int_u exponent);
    friend intf abs(const intf finite);
    friend intf sqrt(const intf finite);
    friend int log2(const intf finite);
    friend int log10(const intf finite);
    friend intf rand(intf size_f);
    friend bool even(const intf& finite);
    friend bool odd(const intf& finite);
    friend intf multiply(const intf& lhs, const intf& rhs);
    friend finite_division_result<intf> divide(const intf& lhs, const intf& rhs);
    friend const intf& max( const intf& a, const intf& b );
    friend const intf& min( const intf& a, const intf& b );
public:
    /**
     * Constructors
     */
    intf();
    intf(const char* cstr);
    template<typename int_t>
    intf(const int_t& finite);
    /**
     * Assignment Operators
     */
    const intf& operator=(const char* cstr);
    template<typename int_t>
    const intf& operator=(const int_t& finite);
    /**
     * Unary Operators
     */
    const intf& operator++();
    const intf& operator--();
    intf operator++(int);
    intf operator--(int);
    /**
     * Mathematical Operators
     */
    intf operator-() const;
    intf operator+(const intf& rhs) const;
    intf operator-(const intf& rhs) const;
    intf operator*(const intf& rhs) const;
    intf operator/(const intf& rhs) const;
    intf operator%(const intf& rhs) const;
    intf operator*(int rhs) const;
    /**
     * Shift Operators
     */
    intf operator<<(const intf& bits) const;
    intf operator<<(int bits) const;
    intf operator>>(const intf& bits) const;
    intf operator>>(int bits) const;
    /**
     * Operational Assignments
     */
    const intf& operator+=(const intf& rhs);
    const intf& operator-=(const intf& rhs);
    const intf& operator*=(const intf& rhs);
    const intf& operator/=(const intf& rhs);
    const intf& operator%=(const intf& rhs);
    const intf& operator*=(int rhs);
    const intf& operator<<=(const intf& bits);
    const intf& operator<<=(int bits);
    const intf& operator>>=(const intf& bits);
    const intf& operator>>=(int bits);
    /**
     * Relational Operators
     */
    bool operator==(const intf& rhs) const;
    bool operator!=(const intf& rhs) const;
    bool operator<(const intf& rhs) const;
    bool operator<=(const intf& rhs) const;
    bool operator>(const intf& rhs) const;
    bool operator>=(const intf& rhs) const;
    /**
     * Helper Functions
     */
    const std::string c_str() const;
    void debug();
};

inline void intf::pacman()
{
    for(int i=digits.size()-1; i>=0; i--)
        if (digits[i] != 0)
            return;
        else
            digits.erase(digits.begin()+i);
    if(!digits.size())
    {
        digits.push_back((int) 0);
        sign = true;
    }
}

inline void intf::snake(const std::string& str)
{
    sign = (str[0] != '-');
    digits.clear();
    digits.reserve(str.size()-1);
    for (int i = str.size()-1; i >= 0; i--)
    {
        digits.push_back(atoi(str.substr(i, 1).c_str()));
    }
    pacman();
}

inline void intf::twenty48()
{
    pacman();
    for (int i = 0; i < digits.size(); i++)
    {
        if(digits[i] < 0)
        {
            if(i+1 < digits.size())
            {
                digits[i+1] --;
                digits[i] += 10;
            }
            else
            {
                digits[i] = -digits[i];
                sign = !sign;
            }
        }
        else if (digits[i] > 9)
        {
            if(i+1 < digits.size())
            {
                digits[i+1] += digits[i] / 10;
            }
            else
            {
                digits.push_back((digits[i] / 10));
            }
            digits[i] %= 10;
        }
    }
    pacman();
}

inline intf::intf(): sign(true)
{
    digits.push_back((int) 0);
}

inline intf::intf(const char* cstr)
{
    snake(cstr);
}

template<>
inline intf::intf(const std::string& str)
{
    snake(str);
}

template<>
inline intf::intf(const intf& finite):
    sign(finite.sign), digits(finite.digits)
{}

template<typename int_t>
inline intf::intf(const int_t& integral)
{
    static_assert(std::is_integral<int_t>::value,
                  "value is non-integral.");

    int_t other = integral;
    sign = (other >= 0);
    if (!sign)
        other = -other;
    do
    {
        digits.push_back((int) other%10);
        other /= 10;
    }
    while (other > 0);

}

inline const intf& intf::operator=(const char* cstr)
{
    snake(cstr);
    return *this;
}

template<>
inline const intf& intf::operator=(const std::string& str)
{
    snake(str);
    return *this;
}

template<>
inline const intf& intf::operator=(const intf& finite)
{
    sign = finite.sign;
    digits = finite.digits;
    return *this;
}

template<typename int_t>
inline const intf& intf::operator=(const int_t& integral)
{
    static_assert(std::is_integral<int_t>::value,
                  "value is non-integral.");

    int_t other = integral;
    sign = (other >= 0);
    digits.clear();
    if (!sign)
        other = -other;
    do
    {
        digits.push_back((int) other%10);
        other /= 10;
    }
    while(other > 0);
    return *this;

}

inline intf intf::operator++(int)
{
    intf self = *this;
    digits[0] += (sign ? 1 : -1);
    twenty48();
    return self;
}

inline intf intf::operator--(int)
{
    intf self = *this;
    digits[0] -= (sign ? 1 : -1);
    twenty48();
    return self;
}


inline const intf& intf::operator++()
{
    digits[0] += (sign ? 1 : -1);
    twenty48();
    return *this;
}

inline const intf& intf::operator--()
{
    digits[0] -= (sign ? 1 : -1);
    twenty48();
    return *this;
}

inline intf intf::operator-() const
{
    intf result = *this;
    result.sign = !sign;
    return result;
}

inline intf intf::operator+(const intf& rhs) const
{
    struct
    {
        intf operator()(const intf& lhs, const intf& rhs)
        {
            intf self;
            self.digits.resize(std::max(lhs.digits.size(), rhs.digits.size()), 0);
            for (size_t i = 0;
                    i < std::max(lhs.digits.size(), rhs.digits.size());
                    ++i)
            {
                int first  = i < lhs.digits.size() ? (lhs.sign ? lhs.digits[i] : -lhs.digits[i]) : 0;
                int second = i < rhs.digits.size() ? (rhs.sign ? rhs.digits[i] : -rhs.digits[i]) : 0;
                self.digits[i] = first + second;
            }
            self.twenty48();
            return self;
        }
    } stackup;
    intf result;
    if(rhs.sign != sign)
    {
        intf abs_this = abs(*this);
        intf abs_rhs  = abs(rhs);
        if(abs_this == max(abs_this, abs_rhs))
        {
            abs_rhs.sign = (rhs < *this)? rhs.sign : sign;
            result = stackup(abs_this, abs_rhs);
            result.sign = (abs_rhs > abs_this)? rhs.sign : sign;
        }
        else
        {
            abs_this.sign = (rhs > *this)? sign : rhs.sign;
            result = stackup(abs_this, abs_rhs);
            result.sign = (abs_rhs > abs_this)? rhs.sign : sign;
        }
    }
    else
    {
        result = stackup(abs(*this), abs(rhs));
        result.sign = sign;
    }
    result.pacman();
    return result;
}

inline const intf& intf::operator+=(const intf& rhs_const)
{
    *this = *this + rhs_const;
    return *this;
}

inline intf intf::operator-(const intf& rhs) const
{
    intf self;
    self = *this + (-rhs);
    return self;
}

inline const intf& intf::operator-=(const intf& rhs)
{
    *this = *this - rhs;
    return *this;
}

inline intf intf::operator*(const intf& rhs) const
{
    return multiply(*this, rhs);
}

inline intf intf::operator*(int rhs) const
{
    intf result;
    intf new_rhs = rhs;
    result = *this * new_rhs;
    return result;
}

inline const intf& intf::operator*=(const intf& rhs)
{
    *this = *this * rhs;
    return *this;
}

inline const intf& intf::operator*=(int rhs)
{
    intf new_rhs = rhs;
    *this = *this * new_rhs;
    return *this;
}

inline intf intf::operator/(const intf& rhs) const
{
    return divide(*this, rhs).quotient;
}

inline const intf& intf::operator/=(const intf& rhs)
{
    *this = divide(*this, rhs).quotient;
    return *this;
}

inline intf intf::operator%(const intf& rhs) const
{
    return divide(*this, rhs).remainder;
}

inline const intf& intf::operator%=(const intf& rhs)
{
    *this = divide(*this, rhs).remainder;
    return *this;
}

inline intf intf::operator<<(const intf& bits) const
{
    intf result = *this;
    for (intf i = 0; i < bits; i++)
        result *= 2;
    return result;
}

inline intf intf::operator<<(int bits) const
{
    intf result = *this;
    for (int i = 0; i < bits; i++)
        result *= 2;
    return result;
}

inline intf intf::operator>>(const intf& bits) const
{
    intf result = *this;
    for (intf i = 0; i < bits; i++)
        result = divide_approximately(result, 2);
    return result;
}

inline intf intf::operator>>(int bits) const
{
    intf result = *this;
    for (int i = 0; i < bits; i++)
        result = divide_approximately(result, 2);
    return result;
}

const intf& intf::operator<<=(const intf& bits)
{
    for (intf i = 0; i < bits; i++)
        *this *= 2;
    return *this;
}

const intf& intf::operator<<=(int bits)
{
    for (int i = 0; i < bits; i++)
        *this *= 2;
    return *this;
}

const intf& intf::operator>>=(const intf& bits)
{
    for (intf i = 0; i < bits; i++)
        *this = divide_approximately(*this, 2);
    return *this;
}

const intf& intf::operator>>=(int bits)
{
    for (int i = 0; i < bits; i++)
        *this = divide_approximately(*this, 2);
    return *this;
}

inline bool intf::operator>(const intf& rhs) const
{
    if (sign && !rhs.sign)
        return true;
    if (!sign && rhs.sign)
        return false;
    if (digits.size() > rhs.digits.size())
        return sign ? true : false;
    if (digits.size() < rhs.digits.size())
        return sign ? false : true;
    for (int i = (int) digits.size() - 1; i >= 0; --i)
    {
        if (digits[i] < rhs.digits[i])
            return sign ? false : true;
        if (digits[i] > rhs.digits[i])
            return sign ? true : false;
    }
    return false;
}

inline bool intf::operator>=(const intf& rhs) const
{
    if (sign && !rhs.sign)
        return true;
    if (!sign && rhs.sign)
        return false;
    if (digits.size() > rhs.digits.size())
        return sign ? true : false;
    if (digits.size() < rhs.digits.size())
        return sign ? false : true;
    for (int i = digits.size() - 1; i >= 0; --i)
    {
        if (digits[i] < rhs.digits[i])
            return sign ? false : true;
        if (digits[i] > rhs.digits[i])
            return sign ? true : false;
    }
    return true;
}


inline bool intf::operator<(const intf& rhs) const
{
    if (sign && !rhs.sign)
        return false;
    if (!sign && rhs.sign)
        return true;
    if (digits.size() > rhs.digits.size())
        return sign ? false : true;
    if (digits.size() < rhs.digits.size())
        return sign ? true : false;
    for (int i = (int) digits.size() - 1; i >= 0; --i)
    {
        if (digits[i] < rhs.digits[i])
            return sign ? true : false;
        if (digits[i] > rhs.digits[i])
            return sign ? false : true;
    }
    return false;
}

inline bool intf::operator<=(const intf& rhs) const
{
    if (sign && !rhs.sign)
        return false;
    if (!sign && rhs.sign)
        return true;
    if (digits.size() > rhs.digits.size())
        return sign ? false : true;
    if (digits.size() < rhs.digits.size())
        return sign ? true : false;
    for (int i = (int) digits.size() - 1; i >= 0; --i)
    {
        if (digits[i] < rhs.digits[i])
            return sign ? true : false;
        if (digits[i] > rhs.digits[i])
            return sign ? false : true;
    }
    return true;
}

inline bool intf::operator!=(const intf& rhs) const
{
    if (sign != rhs.sign)
        return true;
    if (digits.size() != rhs.digits.size())
        return true;
    for (int i = (int) digits.size() - 1; i >= 0; --i)
    {
        if (digits[i] != rhs.digits[i])
            return true;
    }
    return false;
}

inline bool intf::operator==(const intf& rhs) const
{
    if (sign != rhs.sign)
        return false;
    if (digits.size() != rhs.digits.size())
        return false;
    for (int i = (int) digits.size() - 1; i >= 0; --i)
    {
        if (digits[i] != rhs.digits[i])
            return false;
    }
    return true;
}

inline std::istream& operator>>(std::istream &input, intf &other)
{
    std::string str;
    input >> str;
    other.snake(str);
    return input;
}

inline std::ostream& operator<<(std::ostream &output, const intf &other)
{
    if (!other.sign)
        output << '-';
    for (int i = other.digits.size() - 1; i >= 0; i--)
        output << other.digits[i];
    return output;
}

inline const std::string intf::c_str() const
{
    std::string result = "";
    if (!this->sign)
        result = "-";
    for (int i = this->digits.size() - 1; i >= 0; i--)
        result += std::to_string(this->digits[i]);
    return result;
}


void intf::debug()
{
    std::cout<<"sign::: "<<sign<<", digits";
    for(auto d: digits)
        std::cout<<"[ "<<d<<" ]";
    std::cout<<std::endl;
}


template<typename int_t, typename int_u>
inline intf pow(const int_t base, const int_u exponent)
{
    int_t base_t = base;
    int_u exponent_t = exponent;
    int_t result = 1;
    do
    {
        if (exponent_t%2 == 1) // if (exponent_t&1)
        {
            result *= base_t;
        }
        base_t *= base_t;
        exponent_t >>= 1;
    }
    while (exponent_t>0);
    return result;
}

inline intf abs(const intf finite)
{
    intf result = finite;
    result.sign = true;
    return result;
}

inline intf sqrt(const intf finite)
{
    if (finite <= 0)
    {
        std::cerr<<finite.c_str() + " is non-positive";
        exit(1);
    }
    intf low = 0;
    intf high = finite / 2 + 1;
    intf hidden = 1;
    for (int i = finite.digits.size() / 2; i >= 2; --i)
    {
        hidden *= 10;
    }
    if (low < hidden)
    {
        low = hidden;
    }
    hidden *= 100;
    if (high > hidden)
    {
        high = hidden;
    }
    intf mid;
    intf square;
    do
    {
        mid = (high + low) / 2;
        square = mid * mid;
        if (square == finite)
            return mid;
        if (square < finite)
        {
            low = mid;
        }
        else
        {
            high = mid;
        }
    }
    while (low < high - 1 && square != finite);
    return low;
}

inline int log2(const intf finite)
{
    return (finite.digits.size()-1) * 3.322;
}

inline int log10(const intf finite)
{
    return finite.digits.size()-1;
}

inline intf rand(intf size_f)
{
    srand(time(NULL));
    intf result = pow(intf(2), size_f);
    int digit;
    for(int i = 0; i < result.digits.size()-1; i++)
    {
        digit = rand()%9+1;
        result.digits[i] = digit;
    }
    return result;
}

bool even(const intf& finite)
{
    if(finite.digits[0]%2==0)
        return true;
    return false;
}

bool odd(const intf& finite)
{
    if(finite.digits[0]%2==0)
        return false;
    return true;
}

inline intf divide_approximately(intf numerator, intf denominator)
{
    if (denominator == 0)
    {
        throw std::runtime_error("division by zero.");
    }
    if(abs(numerator)<abs(denominator))
        return intf(0);
    intf result;
    result.digits.clear();
    if(numerator.sign != denominator.sign)
        result.sign = false;
    int remainder = 0;
    int result_digit;
    int numerator_digit;
    int denominator_digit = (int) denominator.digits[denominator.digits.size()-1];
    while(abs(numerator) >= 0)
    {

        numerator_digit    = (remainder * 10) + (int) numerator.digits[numerator.digits.size()-1];
        numerator.digits.erase(numerator.digits.begin() + numerator.digits.size()-1);
        result_digit = numerator_digit/denominator_digit;
        remainder = numerator_digit%denominator_digit;
        result.digits.insert(result.digits.begin(), result_digit);
        if(numerator.digits.size()==0)
            break;
    }
    for(int i = 0; i < denominator.digits.size()-1; i++)
        result.digits.erase(result.digits.begin());
    result.pacman();
    if(result.digits.size() == 1 && result.digits[0] == 0)
        result.sign = true;
    return result;
}

inline std::vector<intf> divide_slowly(intf numerator, intf denominator)
{
    if (denominator == 0)
    {
        throw std::runtime_error("division by zero.");
    }
    std::vector<intf> result;
    intf quick_divisor = denominator;
    for(int i = 0; i < quick_divisor.digits.size()-1; i++)
        quick_divisor.digits[i] = 0;
    intf remainder = denominator + 1;
    intf self(numerator);
    intf quotient = divide_approximately(self, quick_divisor);
    intf quotient_candidate;
    while(abs(remainder)>=denominator)
    {
        remainder = numerator - (quotient * denominator);
        quotient_candidate = quotient + divide_approximately(remainder, quick_divisor);
        quotient = divide_approximately(quotient + quotient_candidate, 2);
    }
    remainder = numerator - (quotient * denominator);
    if (remainder<0)
    {
        quotient = quotient - 1;
        remainder=remainder+denominator;
    }
    result.push_back(quotient);
    result.push_back(remainder);
    return result;
}

inline finite_division_result<intf> divide(const intf& lhs, const intf& rhs)
{
    if (rhs == 0)
    {
        throw std::runtime_error("division by zero.");
    }
    struct
    {
        inline int operator() (const intf& remainder, const intf& denominator)
        {
            int low = 0, high = 9;
            while (high > low)
            {
                int mid = high + low;
                integral_division_result<int> determinant = integral_division(mid, 2);
                mid = determinant.remainder ?
                      (determinant.quotient + 1) : determinant.quotient;
                intf product = multiply(denominator, mid) ;
                if (remainder == product)
                {
                    return mid;
                }
                else if (remainder > product)
                {
                    low = mid;
                }
                else
                {
                    high = mid - 1;
                }
            }
            return low;
        }
    } find_division_candidate;
    intf numerator = (lhs.sign ? lhs : -lhs);
    intf denominator = (rhs.sign ? rhs : -rhs);
    intf quotient, remainder;
    quotient.digits.resize(numerator.digits.size(), 0);
    for (int i = numerator.digits.size() - 1; i >= 0; --i)
    {
        remainder.digits.insert(remainder.digits.begin(), numerator.digits[i]);
        remainder.pacman();
        int candidate = find_division_candidate(remainder, denominator);
        remainder -= multiply(denominator, candidate);
        quotient.digits[i] += candidate;
    }
    quotient.pacman();
    quotient.sign = (quotient.digits.size() == 1
                     && quotient.digits[0] == 0) ?
                    true : (lhs.sign == rhs.sign);
    finite_division_result<intf> result;
    result.quotient = quotient;
    result.remainder = remainder;
    return result;
}

inline intf multiply(const intf& lhs, const intf& rhs)
{
    intf result;
    result.digits.resize(lhs.digits.size() + rhs.digits.size(), 0);
    int carry = 0;
    int index = 0;
    for (; ; index++)
    {
        integral_division_result<int> determinant = integral_division(carry, int(10));
        carry = determinant.quotient;
        result.digits[index] = (int) determinant.remainder;
        int i = index < rhs.digits.size() ?
                0 : index - rhs.digits.size() + 1;
        if(!(i < lhs.digits.size() && i <= index))
            break;
        for (i; i < lhs.digits.size() && i <= index; ++i)
        {
            int digit = result.digits[index] + lhs.digits[i]
                        * rhs.digits[index - i];
            if (digit >= 10 || digit <= -10)
            {
                integral_division_result<int> determinant = integral_division(digit, int(10));
                carry += determinant.quotient;
                digit = determinant.remainder;
            }
            result.digits[index] = digit;
        }
    }
    for (; carry > 0; index++)
    {
        integral_division_result<int> determinant = integral_division(carry, int(10));
        result.digits[index] = determinant.remainder;
        carry = determinant.quotient;
    }
    result.pacman();
    result.sign = (result.digits.size() == 1
                   && result.digits[0] == 0) ?
                  true : (lhs.sign == rhs.sign);
    return result;
}

const intf& max( const intf& a, const intf& b )
{
    if(a>=b)
        return a;
    else
        return b;
}

const intf& min( const intf& a, const intf& b )
{
    if(a<=b)
        return a;
    else
        return b;
}

namespace std
{
    template<>
    struct hash<intf>
    {
        size_t
        operator()(const intf & obj) const
        {
            return hash<std::string>()(obj.c_str());
        }
    };
}


#endif
