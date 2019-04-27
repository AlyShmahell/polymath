#include <iostream>
#include <vector>
#include <random>
#include <time.h>

#ifndef INTF_H_
#define INTF_H_


class intf
{

private:
    /**
     * the guts of intf
     */
    bool sign;
    int base = 10;
    std::vector<int> digits;
    /**
     * helper functions
     */
    void pacman();
    void snake(const std::string& s);
    /**
     * division functions
     */
    friend std::vector<intf> div(intf numerator, intf denominato);
    friend intf div_approximate(intf numerator, intf denominator);
    /**
     * IO
     */
    friend std::ostream& operator<<(std::ostream &s, const intf &n);
    friend std::istream& operator>>(std::istream &s, intf &val);
    friend intf pow(const intf finite, const intf finite_2);
    friend intf pow(const intf finite, const int n);
    friend intf abs(const intf finite);
    friend intf sqrt(const intf finite);
    friend int log2(const intf finite);
    friend int log10(const intf finite);
    friend intf rand(intf size_f);
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

inline const intf& intf::operator+=(const intf& rhs_const)
{
    digits.resize(digits.size() > rhs_const.digits.size() ? digits.size() : rhs_const.digits.size(), 0);

    if(sign != rhs_const.sign)
    {
        intf rhs = *this < rhs_const? *this: rhs_const;
        *this = *this > rhs_const? *this: rhs_const;
        intf temp_this = *this < 0? -*this: *this;
        intf temp_rhs = rhs < 0? -rhs: rhs;
        if (temp_this < temp_rhs)
        {
            intf temp_swap = *this;
            *this = rhs;
            rhs = temp_swap;
        }
        int borrow = 0;
        for (int i = 0; i < digits.size(); ++i)
        {
            digits[i] -= borrow? 1:0;
            digits[i] = digits[i] - (i < rhs.digits.size() ? rhs.digits[i] : 0);
            if(digits[i]<0)
            {
                digits[i] = 10 + digits[i];
                borrow++;
            }
            else
                borrow = 0;
        }
        if(digits[digits.size()-1] < 0)
            digits[digits.size()-1] = 0;
        pacman();
    }
    else
    {
        int carry = 0;
        for (int i = 0; i < digits.size(); ++i)
        {
            digits[i] += carry;
            digits[i] = digits[i] + (i < rhs_const.digits.size() ? rhs_const.digits[i] : 0);
            if(digits[i]>=10)
            {
                carry = digits[i]/10;
                digits[i] = digits[i]%10;
            }
            else
                carry = 0;
        }
        if (carry>0)
            digits.push_back((int) carry);
    }
    return *this;
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

inline const intf& intf::operator-=(const intf& rhs_const)
{
    digits.resize(digits.size() > rhs_const.digits.size() ? digits.size() : rhs_const.digits.size(), 0);

    if(sign == rhs_const.sign)
    {
        intf rhs = *this < rhs_const? *this: rhs_const;
        *this = *this > rhs_const? *this: rhs_const;
        intf temp_this = *this < 0? -*this: *this;
        intf temp_rhs = rhs < 0? -rhs: rhs;
        if (temp_this < temp_rhs)
        {
            intf temp_swap = *this;
            *this = rhs;
            rhs = temp_swap;
        }
        if(*this == rhs_const)
            sign = !sign;
        int borrow = 0;
        for (int i = 0; i < digits.size(); ++i)
        {
            digits[i] -= borrow? 1:0;
            digits[i] = digits[i] - (i < rhs.digits.size() ? rhs.digits[i] : 0);
            if(digits[i]<0)
            {
                digits[i] = 10 + digits[i];
                borrow++;
            }
            else
                borrow = 0;
        }
        if(digits[digits.size()-1] < 0)
            digits[digits.size()-1] = 0;
        pacman();
    }
    else
    {
        intf rhs = *this < rhs_const? *this: rhs_const;
        *this = *this > rhs_const? *this: rhs_const;
        intf temp_this = *this < 0? -*this: *this;
        intf temp_rhs = rhs < 0? -rhs: rhs;
        if (temp_this < temp_rhs)
        {
            intf temp_swap = *this;
            *this = rhs;
            rhs = temp_swap;
        }
        if(*this == rhs_const)
            sign = !sign;
        int carry = 0;
        for (int i = 0; i < digits.size(); ++i)
        {
            digits[i] += carry;
            digits[i] = digits[i] + (i < rhs.digits.size() ? rhs.digits[i] : 0);
            if(digits[i]>=10)
            {
                carry = digits[i]/10;
                digits[i] = digits[i]%10;
            }
            else
                carry = 0;
        }
        if (carry>0)
            digits.push_back((int) carry);
        pacman();
    }
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

inline const intf& intf::operator*=(const intf& rhs)
{
    intf result;
    result.digits.clear();
    std::vector<intf> temps;
    result.digits.resize(digits.size() * rhs.digits.size(), 0);
    int carry = 0;
    int digit_mult_result;
    for (int i = 0; i < digits.size(); ++i)
    {
        intf ii;
        ii.digits.clear();
        temps.push_back(ii);
        for(int k = 0; k < i; k++)
            temps[i].digits.push_back(0);
        for (int j = 0; j < rhs.digits.size(); ++j)
        {
            digit_mult_result = digits[i] * rhs.digits[j];
            temps[i].digits.push_back(digit_mult_result%10 + carry);
            carry = digit_mult_result/10;
        }
        if (carry>0)
            temps[i].digits.push_back((int) carry);
        carry = 0;
    }
    for (int i = 0; i < temps.size(); ++i)
        result += temps[i];
    if (sign!=rhs.sign)
        result.sign = false;
    *this = result;
    pacman();
    if (digits.size() == 1 && digits[0] == 0 )
        sign = true;
    return *this;
}

inline intf intf::operator*(const intf& rhs) const
{
    intf result;
    result.digits.clear();
    std::vector<intf> temps;
    result.digits.resize(digits.size() * rhs.digits.size(), 0);
    int carry = 0;
    int digit_mult_result;

    for (int i = 0; i < digits.size(); ++i)
    {
        intf ii;
        ii.digits.clear();
        temps.push_back(ii);
        for(int k = 0; k < i; k++)
            temps[i].digits.push_back(0);
        for (int j = 0; j < rhs.digits.size(); ++j)
        {
            digit_mult_result = digits[i] * rhs.digits[j];
            temps[i].digits.push_back(digit_mult_result%10 + carry);
            carry = digit_mult_result/10;
        }
        if (carry>0)
            temps[i].digits.push_back(carry);
        carry = 0;
    }
    for (int i = 0; i < temps.size(); ++i)
        result += temps[i];
    if (sign!=rhs.sign)
        result.sign = false;
    result.pacman();
    __sync_synchronize();
    if (result.digits.size() == 1 && result.digits[0] == 0 )
        result.sign = true;
    return result;
}

inline const intf& intf::operator*=(int rhs)
{
    intf new_rhs = rhs;
    *this = *this * new_rhs;
    return *this;
}

inline intf intf::operator*(int rhs) const
{
    intf result;
    intf new_rhs = rhs;
    result = *this * new_rhs;
    return result;
}

inline intf div_approximate(intf numerator, intf denominator)
{
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

inline std::vector<intf> div(intf numerator, intf denominator)
{
    std::vector<intf> result;
    intf quick_divisor = denominator;
    for(int i = 0; i < quick_divisor.digits.size()-1; i++)
        quick_divisor.digits[i] = 0;
    intf remainder = denominator + 1;
    intf self(numerator);
    intf quotient = div_approximate(self, quick_divisor);
    intf quotient_candidate;
    while(abs(remainder)>=denominator)
    {
        remainder = numerator - (quotient * denominator);
        quotient_candidate = quotient + div_approximate(remainder, quick_divisor);
        quotient = div_approximate(quotient + quotient_candidate, 2);
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

inline intf intf::operator/(const intf& rhs_const) const
{
    intf lhs = *this;
    intf rhs = rhs_const;
    if (!lhs.sign)
        lhs.sign = true;
    if (!rhs.sign)
        rhs.sign = true;
    std::vector<intf> result = div(lhs, rhs);
    if(sign != rhs_const.sign)
        result[0].sign = false;
    return result[0];
}

inline const intf& intf::operator/=(const intf& rhs_const)
{
    intf lhs = *this;
    intf rhs = rhs_const;
    if (!lhs.sign)
        lhs.sign = true;
    if (!rhs.sign)
        rhs.sign = true;
    std::vector<intf> result = div(lhs, rhs);
    if(sign != rhs_const.sign)
        result[0].sign = false;
    *this = result[0];
    return *this;
}

inline const intf& intf::operator%=(const intf& rhs_const)
{
    intf lhs = *this;
    intf rhs = rhs_const;
    if (!lhs.sign)
        lhs.sign = true;
    if (!rhs.sign)
        rhs.sign = true;
    std::vector<intf> result = div(lhs, rhs);
    if(!sign && rhs_const.sign)
        result[1].sign = false;
    *this = result[1];
    return *this;
}

inline intf intf::operator%(const intf& rhs_const) const
{
    intf lhs = *this;
    intf rhs = rhs_const;
    if (!lhs.sign)
        lhs.sign = true;
    if (!rhs.sign)
        rhs.sign = true;
    std::vector<intf> result = div(lhs, rhs);
    if(!sign && rhs_const.sign)
        result[1].sign = false;
    return result[1];
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
        result = div_approximate(result, 2);
    return result;
}

inline intf intf::operator>>(int bits) const
{
    intf result = *this;
    for (int i = 0; i < bits; i++)
        result = div_approximate(result, 2);
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
        *this = div_approximate(*this, 2);
    return *this;
}

const intf& intf::operator>>=(int bits)
{
    for (int i = 0; i < bits; i++)
        *this = div_approximate(*this, 2);
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

std::string intf::id() const
{
    std::string result = "";
    for (auto v: digits)
        result+= std::to_string(v);
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
        return hash<std::string>()(obj.id());
      }
    };
}


#endif
