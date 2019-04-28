#include <iostream>
#include <vector>
#include <random>
#include <cstdlib>
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
    friend std::ostream& operator<<(std::ostream& out, const finite_division_result& other)
    {
        out<<other.quotient<<", "<<other.remainder<<std::endl;
    }
};


template<typename int_t>
struct integral_division_result
{
    static_assert(std::is_integral<int_t>::value,
                  "value is non-integral.");
    int_t quotient;
    int_t remainder;
    friend std::ostream& operator<<(std::ostream& out, const integral_division_result& other)
    {
        out<<other.quotient<<", "<<other.remainder<<std::endl;
    }
};


template <typename int_t>
inline static integral_division_result<int_t> integral_division(int_t numerator, int_t denominator)
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
    int base = 10;
    std::vector<int> digits;
    /**
     * Internal Functions
     */
    void pacman();
    void snake(const std::string& s);
    /**
     * Legacy Functions
     */
    friend std::vector<intf> divide_slowly(intf numerator, intf denominato);
    friend intf divide_approximately(intf numerator, intf denominator);
    /**
     * IO Functions
     */
    friend std::ostream& operator<<(std::ostream &s, const intf &n);
    friend std::istream& operator>>(std::istream &s, intf &val);
    /**
     * Math Functions
     */
    friend intf pow(const intf finite, const intf finite_2);
    friend intf pow(const intf finite, const int n);
    friend intf abs(const intf finite);
    friend intf sqrt(const intf finite);
    friend int log2(const intf finite);
    friend int log10(const intf finite);
    friend intf rand(intf size_f);
    friend bool even(const intf& finite);
    friend bool odd(const intf& finite);
    friend intf multiply(const intf& lhs, const intf& rhs);
    friend finite_division_result<intf> divide(const intf& lhs, const intf& rhs);
public:
    std::string id() const;
    /**
     * constructors
     */
    intf();
    intf(const char* c);
    template<typename int_t>
    intf(const int_t& finite);
    /**
     * assignment operators
     */
    const intf& operator=(const char* c);
    template<typename int_t>
    const intf& operator=(const int_t& finite);
    /**
     * unary operators
     */
    const intf& operator++();
    const intf& operator--();
    intf operator++(int);
    intf operator--(int);
    /**
     * operational assignments
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
     * mathematical operations
     */
    intf operator-() const;
    intf operator+(const intf& rhs) const;
    intf operator-(const intf& rhs) const;
    intf operator*(const intf& rhs) const;
    intf operator/(const intf& rhs) const;
    intf operator%(const intf& rhs) const;
    intf operator*(int rhs) const;
    intf operator<<(const intf& bits) const;
    intf operator<<(int bits) const;
    intf operator>>(const intf& bits) const;
    intf operator>>(int bits) const;

    /**
     * relational operations
     */
    bool operator==(const intf& rhs) const;
    bool operator!=(const intf& rhs) const;
    bool operator<(const intf& rhs) const;
    bool operator<=(const intf& rhs) const;
    bool operator>(const intf& rhs) const;
    bool operator>=(const intf& rhs) const;
    const std::string c_str() const;
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

inline void intf::snake(const std::string& s)
{
    sign = (s[0] != '-');
    digits.clear();
    digits.reserve(s.size()-1);
    for (int i = s.size()-1; i >= 0; i--)
    {
        digits.push_back(atoi(s.substr(i, 1).c_str()));
    }
    pacman();
}

inline intf::intf(): sign(true)
{
    digits.push_back((int) 0);
}

inline intf::intf(const char* c)
{
    snake(c);
}

template<>
inline intf::intf(const std::string& s)
{
    snake(s);
}

template<>
inline intf::intf(const intf& finite):
    sign(finite.sign), digits(finite.digits)
{}

template<typename int_t>
inline intf::intf(const int_t& finite)
{
    static_assert(std::is_integral<int_t>::value,
                  "value is not intergal.");

    int_t i = finite;
    sign = (i >= 0);
    if (!sign)
        i = -i;
    do
    {
        digits.push_back((int) i%10);
        i/=10;
    }
    while (i > 0);

}

inline const intf& intf::operator=(const char* c)
{
    snake(c);
    return *this;
}

template<>
inline const intf& intf::operator=(const std::string& s)
{
    snake(s);
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
inline const intf& intf::operator=(const int_t& finite)
{
    static_assert(std::is_integral<int_t>::value,
                  "value is not intergal.");

    int_t i = finite;
    sign = (i>=0);
    if (i!=0)
        digits.clear();
    if (!sign)
        i = -i;
    while(i > 0)
    {
        digits.push_back((int) i%10);
        i/=10;
    }
    return *this;

}

inline intf intf::operator++(int)
{
    int additive = 1;
    intf result = *this;
    if (sign)
    {
        for(int i = 0; i < digits.size(); i++)
        {
            if(additive == 0)
                break;
            digits[i] += additive;
            if (digits[i] < 10)
                additive = 0;
            else
                digits[i] = 0;
        }
        if (digits[digits.size()-1] == 0)
        {
            digits.push_back((int) 1);
        }
        return result;
    }
    else
    {
        bool keep_sign = false;
        for(int i = 0; i < digits.size(); i++)
        {
            if(additive == 0)
                break;
            if (digits[i] == 0)
            {
                digits[i] = 9;
                keep_sign = true;
            }
            else
            {
                digits[i] -= additive;
                if(digits[i]>0)
                    keep_sign = true;
                additive = 0;
            }
        }
        if (digits[digits.size()-1] == 0)
        {
            if(!keep_sign)
                sign = !sign;
            digits[digits.size()-1] = 0;
            pacman();
        }
        return result;
    }
}

inline intf intf::operator--(int)
{
    int additive = 1;
    intf result = *this;
    if (sign)
    {
        bool keep_sign = false;
        if(digits.size()==1 && digits[0]==0)
        {
            digits[0] = 1;
            sign = false;
            return result;
        }
        for(int i = 0; i < digits.size(); i++)
        {
            if(additive == 0)
                break;
            if (digits[i] == 0)
            {
                digits[i] = 9;
                keep_sign = true;
            }
            else
            {
                digits[i] -= additive;
                if(digits[i]>0)
                    keep_sign = true;
                additive = 0;
            }
        }
        if (digits[digits.size()-1] == 0)
        {
            if(!keep_sign)
                sign = !sign;
            digits[digits.size()-1] = 0;
            pacman();
        }
        return result;
    }
    else
    {
        for(int i = 0; i < digits.size(); i++)
        {
            if(additive == 0)
                break;
            digits[i] += additive;
            if (digits[i] < 10)
                additive = 0;
            else
                digits[i] = 0;
        }
        if (digits[digits.size()-1] == 0)
        {
            digits.push_back((int) 1);
        }
        return result;
    }
}


inline const intf& intf::operator++()
{
    int additive = 1;
    if (sign)
    {
        for(int i = 0; i < digits.size(); i++)
        {
            if(additive == 0)
                break;
            digits[i] += additive;
            if (digits[i] < 10)
                additive = 0;
            else
                digits[i] = 0;
        }
        if (digits[digits.size()-1] == 0)
        {
            digits.push_back((int) 1);
        }
        return *this;
    }
    else
    {
        bool keep_sign = false;
        for(int i = 0; i < digits.size(); i++)
        {
            if(additive == 0)
                break;
            if (digits[i] == 0)
            {
                digits[i] = 9;
                keep_sign = true;
            }
            else
            {
                digits[i] -= additive;
                if(digits[i]>0)
                    keep_sign = true;
                additive = 0;
            }
        }
        if (digits[digits.size()-1] == 0)
        {
            if(!keep_sign)
                sign = !sign;
            digits[digits.size()-1] = 0;
            pacman();
        }
        return *this;
    }
}

inline const intf& intf::operator--()
{
    int additive = 1;
    if (sign)
    {
        bool keep_sign = false;
        if(digits.size()==1 && digits[0]==0)
        {
            digits[0] = 1;
            sign = false;
            return *this;
        }
        for(int i = 0; i < digits.size(); i++)
        {
            if(additive == 0)
                break;
            if (digits[i] == 0)
            {
                digits[i] = 9;
                keep_sign = true;
            }
            else
            {
                digits[i] -= additive;
                if(digits[i]>0)
                    keep_sign = true;
                additive = 0;
            }
        }
        if (digits[digits.size()-1] == 0)
        {
            if(!keep_sign)
                sign = !sign;
            digits[digits.size()-1] = 0;
            pacman();
        }
        return *this;
    }
    else
    {
        for(int i = 0; i < digits.size(); i++)
        {
            if(additive == 0)
                break;
            digits[i] += additive;
            if (digits[i] < 10)
                additive = 0;
            else
                digits[i] = 0;
        }
        if (digits[digits.size()-1] == 0)
        {
            digits.push_back((int) 1);
        }
        return *this;
    }
}

inline intf intf::operator-() const
{
    intf result = *this;
    result.sign = !sign;
    return result;
}

inline intf intf::operator+(const intf& rhs_const) const
{
    intf result;
    intf self = *this;
    if(self.sign != rhs_const.sign)
    {
        intf rhs = self < rhs_const? self: rhs_const;
        self = self > rhs_const? self: rhs_const;
        intf temp_this = self < 0? -self: self;
        intf temp_rhs = rhs < 0? -rhs: rhs;
        if (temp_this < temp_rhs)
        {
            intf temp_swap = self;
            self = rhs;
            rhs = temp_swap;
        }
        result = self;
        int borrow = 0;
        for (int i = 0; i < result.digits.size(); ++i)
        {
            result.digits[i] = result.digits[i] - (i < rhs.digits.size() ? rhs.digits[i] : 0);
            if(result.digits[i]<0)
            {
                result.digits[i] = 10 + result.digits[i];
                borrow++;
            }
            else
                borrow = 0;
            result.digits[i+1] -= borrow? 1:0;
        }
        if(result.digits[result.digits.size()-1] < 0)
            result.digits[result.digits.size()-1] = 0;
        result.pacman();
    }
    else
    {
        result = self;
        result.digits.resize(digits.size() > rhs_const.digits.size() ? digits.size() : rhs_const.digits.size(), 0);
        int carry = 0;
        for (int i = 0; i < result.digits.size(); ++i)
        {
            result.digits[i] += carry;
            result.digits[i] = result.digits[i] + (i < rhs_const.digits.size() ? rhs_const.digits[i] : 0);
            if(result.digits[i]>=10)
            {
                carry = result.digits[i]/10;
                result.digits[i] = result.digits[i]%10;
            }
            else
                carry = 0;

        }
        if (carry>0)
        {
            result.digits.push_back(carry);
        }
    }
    return result;
}

inline const intf& intf::operator+=(const intf& rhs_const)
{
    *this = *this + rhs_const;
    return *this;
}

inline intf intf::operator-(const intf& rhs_const) const
{
    intf result;
    intf self = *this;
    result.digits.resize(digits.size() > rhs_const.digits.size() ? digits.size() : rhs_const.digits.size(), 0);
    if(self.sign == rhs_const.sign)
    {
        intf rhs = self < rhs_const? self: rhs_const;
        self = self > rhs_const? self: rhs_const;
        intf temp_this = self < 0? -self: self;
        intf temp_rhs = rhs < 0? -rhs: rhs;
        if (temp_this < temp_rhs)
        {
            intf temp_swap = self;
            self = rhs;
            rhs = temp_swap;
        }
        result = self;
        if(result == rhs_const)
            result.sign = !result.sign;
        int borrow = 0;
        for (int i = 0; i < result.digits.size(); ++i)
        {
            result.digits[i] -= borrow? 1:0;
            result.digits[i] = result.digits[i] - (i < rhs.digits.size() ? rhs.digits[i] : 0);
            if(result.digits[i]<0)
            {
                result.digits[i] = 10 + result.digits[i];
                borrow++;
            }
            else
                borrow = 0;
        }
        if(result.digits[result.digits.size()-1] < 0)
            result.digits[result.digits.size()-1] = 0;
        result.pacman();
    }
    else
    {
        intf rhs = self < rhs_const? self: rhs_const;
        self = self > rhs_const? self: rhs_const;
        intf temp_this = self < 0? -self: self;
        intf temp_rhs = rhs < 0? -rhs: rhs;
        if (temp_this < temp_rhs)
        {
            intf temp_swap = self;
            self = rhs;
            rhs = temp_swap;
        }
        result = self;
        if(result == rhs_const)
            result.sign = !result.sign;
        int carry = 0;
        for (int i = 0; i < result.digits.size(); ++i)
        {
            result.digits[i] += carry;
            result.digits[i] = result.digits[i] + (i < rhs.digits.size() ? rhs.digits[i] : 0);
            if(result.digits[i]>=10)
            {
                carry = result.digits[i]/10;
                result.digits[i] = result.digits[i]%10;
            }
            else
                carry = 0;
        }
        if (carry>0)
            result.digits.push_back((int) carry);
        result.pacman();
    }
    return result;
}

inline const intf& intf::operator-=(const intf& rhs_const)
{
    *this = *this - rhs_const;
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

inline intf intf::operator/(const intf& rhs_const) const
{
    return divide(*this, rhs_const).quotient;
}

inline const intf& intf::operator/=(const intf& rhs_const)
{
    *this = divide(*this, rhs_const).quotient;
    return *this;
}

inline intf intf::operator%(const intf& rhs_const) const
{
    return divide(*this, rhs_const).remainder;
}

inline const intf& intf::operator%=(const intf& rhs_const)
{
    *this = divide(*this, rhs_const).remainder;
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

inline std::istream& operator>>(std::istream &input, intf &finite)
{
    std::string str;
    input >> str;
    finite.snake(str);
    return input;
}

inline std::ostream& operator<<(std::ostream &output, const intf &finite)
{
    if (!finite.sign)
        output << '-';
    for (int i = finite.digits.size() - 1; i >= 0; i--)
        output << finite.digits[i];
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

inline intf pow(const intf base, const intf exponent)
{
    intf base_t = base;
    intf exponent_t = exponent;
    intf result = 1;
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

inline intf pow(const intf base, const int exponent)
{
    intf base_t = base;
    int exponent_t = exponent;
    intf result = 1;
    do
    {
        if (exponent_t%2 == 1) // if (exponent_t&1)
        {
            result *= base_t;
        }
        base_t *= base_t;
    }
    while (exponent_t >>= 1);
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
