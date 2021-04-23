#include <vector>
#include <sstream>
#include <iostream>
#include <random>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include "mpa.hpp"
#ifndef INTEGER_HPP_
#define INTEGER_HPP_
/**
 * base
 */
struct
{
    const int_fast64_t value = 1e7;
    const int_fast64_t radix = 7;
    std::vector<int_fast64_t> convert(const std::vector<int_fast64_t> &vec, int_fast64_t src, int_fast64_t tgt)
    {
        std::vector<int_fast64_t> pwr(std::max(src, tgt) + 1);
        pwr[0] = 1;
        for (int_fast64_t i = 1; i < (int_fast64_t) pwr.size(); i++)
            pwr[i] = pwr[i - 1] * 10;
        std::vector<int_fast64_t> res;
        int_fast64_t cur = 0;
        int_fast64_t dig = 0;
        for (int_fast64_t i = 0; i < (int_fast64_t) vec.size(); i++)
        {
            cur += vec[i] * pwr[dig];
            dig += src;
            while (dig >= tgt)
            {
                res.push_back(int_fast64_t(cur % pwr[tgt]));
                cur /= pwr[tgt];
                dig -= tgt;
            }
        }
        res.push_back((int_fast64_t) cur);
        while (!res.empty() && !res.back())
            res.pop_back();
        return res;
    }
} base;
/**
 * quotient/remainder
 */
template<typename int_t>
struct qr
{
    int_t q,r;
};
/**
 * big integer
 */
class integer
{
private:
    std::vector<int_fast64_t> digits;
    int_fast64_t sign;
    void trim()
    {
        while (!digits.empty() && !digits.back())
            digits.pop_back();
        if (digits.empty())
            sign = 1;
    }
    void read(const std::string &str)
    {
        sign = 1;
        digits.clear();
        int_fast64_t pos = 0;
        while (pos < (int_fast64_t) str.size() && (str[pos] == '-' || str[pos] == '+'))
        {
            if (str[pos] == '-')
                sign = -sign;
            ++pos;
        }
        for (int_fast64_t i = str.size() - 1; i >= pos; i -= base.radix)
        {
            int_fast64_t x = 0;
            for (int_fast64_t j = std::max(pos, i - base.radix + 1); j <= i; j++)
                x = x * 10 + str[j] - '0';
            digits.push_back(x);
        }
        trim();
    }
public:
    friend mpa::karatsuba<integer>;
    friend mpa::srt<integer>;
    friend mpa::mul<integer, int_fast64_t>;
    friend mpa::div<integer, int_fast64_t>;
    friend mpa::mod<integer, int_fast64_t>;
    integer(): sign(1) {}
    integer(const char* str)
    {
        read(str);
    }
    integer(const std::string& str)
    {
        read(str);
    }
    integer(const integer& num):
        sign(num.sign), digits(num.digits)
    {}
    template<typename int_t>
    integer(const int_t& num)
    {
        static_assert(std::is_integral<int_t>::value,
                      "num is non-integral.");
        *this = num;
    }
    void operator=(const char* str)
    {
        read(str);
    }
    void operator=(const std::string& str)
    {
        read(str);
    }
    void operator=(const integer &num)
    {
        sign   = num.sign;
        digits = num.digits;
    }
    template<typename int_t>
    void operator=(const int_t rhs)
    {
        static_assert(std::is_integral<int_t>::value,
                      "digits is non-integral.");
        int_t num = rhs;
        sign = 1;
        digits.clear();
        if (num < 0)
            sign = -1, num = -num;
        for (; num > 0; num = num / base.value)
            digits.push_back(num % base.value);
    }
    integer operator+(const integer &rhs) const
    {
        if (sign == rhs.sign)
        {
            integer res = rhs;
            for (int_fast64_t i = 0, carry = 0; i < (int_fast64_t) std::max(digits.size(), rhs.digits.size()) || carry; ++i)
            {
                if (i == (int_fast64_t) res.digits.size())
                    res.digits.push_back(0);
                res.digits[i] += carry + (i < (int_fast64_t) digits.size() ? digits[i] : 0);
                carry = res.digits[i] >= base.value;
                if (carry)
                    res.digits[i] -= base.value;
            }
            return res;
        }
        return *this - (-rhs);
    }
    template<typename int_t,
             typename = std::enable_if_t<std::is_arithmetic<int_t>::value>
             >
    integer operator+(const int_t &rhs)
    {
        return *this + integer(rhs);
    }
    template<typename int_t>
    friend integer operator+(const int_t lhs, const integer &rhs)
    {
        return integer(lhs) + rhs;
    }
    void operator+=(const integer &rhs)
    {
        *this = *this + rhs;
    }
    integer operator ++()
    {
        *this += 1;
        return *this;
    }
    integer operator ++(int_fast32_t)
    {
        integer tmp = *this;
        *this += 1;
        return tmp;
    }
    integer operator-(const integer &rhs) const
    {
        if (sign == rhs.sign)
        {
            if (abs(*this) >= abs(rhs))
            {
                integer res = *this;
                for (int_fast64_t i = 0, carry = 0; i < (int_fast64_t) rhs.digits.size() || carry; ++i)
                {
                    res.digits[i] -= carry + (i < (int_fast64_t) rhs.digits.size() ? rhs.digits[i] : 0);
                    carry = res.digits[i] < 0;
                    if (carry)
                        res.digits[i] += base.value;
                }
                res.trim();
                return res;
            }
            return -(rhs - *this);
        }
        return *this + (-rhs);
    }
    void operator-=(const integer &rhs)
    {
        *this = *this - rhs;
    }
    integer operator --()
    {
        *this -= 1;
        return *this;
    }
    integer operator --(int_fast32_t)
    {
        integer tmp = *this;
        *this -= 1;
        return tmp;
    }
    integer operator*(const integer &rhs) const
    {
        return mpa::karatsuba<integer>()(*this, rhs, base);
    }
    void operator*=(const integer &rhs)
    {
        *this = *this * rhs;
    }
    integer operator/(const integer &rhs) const
    {
        return mpa::srt<integer>()(*this, rhs, base).q;
    }
    void operator/=(const integer &rhs)
    {
        *this = mpa::srt<integer>()(*this, rhs, base).q;
    }
    integer operator%(const integer &rhs) const
    {
        return mpa::srt<integer>()(*this, rhs, base).r;
    }
    void operator%=(const integer rhs)
    {
        *this = mpa::srt<integer>()(*this, rhs, base).r;
    }
    template<typename int_t>
    integer operator*(const int_t &rhs) const
    {
        static_assert(std::is_integral<int_t>::value,
                      "rhs is non-integral.");
        return mpa::mul<integer, int_fast64_t>()(*this, rhs, base);
    }
    template<typename int_t>
    void operator*=(int_t rhs)
    {
        static_assert(std::is_integral<int_t>::value,
                      "rhs is non-integral.");
        *this = mpa::mul<integer, int_fast64_t>()(*this, rhs, base);
    }
    template<typename int_t>
    integer operator/(const int_t &rhs) const
    {
        static_assert(std::is_integral<int_t>::value,
                      "rhs is non-integral.");
        return mpa::div<integer, int_fast64_t>()(*this, rhs, base);
    }
    template<typename int_t>
    void operator/=(const int_t &rhs)
    {
        static_assert(std::is_integral<int_t>::value,
                      "rhs is non-integral.");
        *this = mpa::div<integer, int_fast64_t>()(*this, rhs, base);
    }
    template<typename int_t>
    integer operator%(const int_t &rhs) const
    {
        static_assert(std::is_integral<int_t>::value,
                      "rhs is non-integral.");
        return mpa::mod<integer, int_fast64_t>()(*this, rhs, base);
    }
    template<typename int_t>
    void operator%=(const int_t &rhs)
    {
        static_assert(std::is_integral<int_t>::value,
                      "rhs is non-integral.");
        *this = mpa::srt<integer>()(*this, integer(rhs), base).r;
    }
    bool operator<(const integer &rhs) const
    {
        if (sign != rhs.sign)
            return sign < rhs.sign;
        if (digits.size() != rhs.digits.size())
            return digits.size() * sign < rhs.digits.size() * rhs.sign;
        for (int_fast64_t i = digits.size() - 1; i >= 0; i--)
            if (digits[i] != rhs.digits[i])
                return digits[i] * sign < rhs.digits[i] * sign;
        return false;
    }
    template<typename int_t>
    bool operator<(const int_t &rhs) const
    {
        static_assert(std::is_integral<int_t>::value,
                      "rhs is non-integral.");
        return *this < integer(rhs);
    }
    template<typename int_t>
    friend bool operator<(const int_t &lhs, const integer &rhs)
    {
        static_assert(std::is_integral<int_t>::value,
                      "rhs is non-integral.");
        return integer(lhs) < rhs;
    }
    template<typename int_t>
    bool operator>(const int_t &rhs) const
    {
        return rhs < *this;
    }
    template<typename int_t>
    bool operator<=(const int_t &rhs) const
    {
        return !(rhs < *this);
    }
    template<typename int_t>
    bool operator>=(const int_t &rhs) const
    {
        return !(*this < rhs);
    }
    template<typename int_t>
    bool operator==(const int_t &rhs) const
    {
        return !(*this < rhs) && !(rhs < *this);
    }
    template<typename int_t>
    bool operator!=(const int_t &rhs) const
    {
        return *this < rhs || rhs < *this;
    }
    integer operator-() const
    {
        integer res;
        res      = *this;
        res.sign = -sign;
        return res;
    }
    template <typename int_t>
    integer operator<<(const int_t& bits) const
    {
        if (!(std::is_same<integer, int_t>::value || std::is_integral<int_t>::value))
        {
            throw std::runtime_error("rhs is not integral");
        }
        integer res = *this;
        for (integer i = 0; i < bits; i++)
            res *= 2;
        return res;
    }
    template <typename int_t>
    integer operator>>(const int_t& bits) const
    {
        if (!(std::is_same<integer, int_t>::value || std::is_integral<int_t>::value))
        {
            throw std::runtime_error("rhs is not integral");
        }
        integer res = *this;
        for (integer i = 0; i < bits; i++)
            res = mpa::srt<integer>()(res, integer(2), base).q;
        return res;
    }
    template <typename int_t>
    const integer& operator<<=(const int_t& bits)
    {
        if (!(std::is_same<integer, int_t>::value || std::is_integral<int_t>::value))
        {
            throw std::runtime_error("rhs is not integral");
        }
        for (integer i = 0; i < bits; i++)
            *this *= 2;
        return *this;
    }
    template <typename int_t>
    const integer& operator>>=(const int_t& bits)
    {
        if (!(std::is_same<integer, int_t>::value || std::is_integral<int_t>::value))
        {
            throw std::runtime_error("rhs is not integral");
        }
        for (integer i = 0; i < bits; i++)
            *this = mpa::srt<integer>()(*this, integer(2), base).q;
        return *this;
    }
    template<typename int_t,
             typename = std::enable_if_t<std::is_arithmetic<int_t>::value>
             >
    operator int_t() const
    {
        int_t res = 0;
        for (int i = digits.size() - 1; i >= 0; i--)
            res = res * base.value + digits[i];
        return res * sign;
    }
    friend int_fast16_t size(const integer &num)
    {
        if(num.digits.empty())
            return 0;
        int_fast16_t res = (num.digits.size()-1)*base.radix;
        int_fast64_t msd = num.digits.back();
        while(msd)
        {
            res++;
            msd/=10;
        }
        return res;
    }
    const std::string c_str() const
    {
        std::stringstream ss;
        ss  << *this;
        std::string str;
        ss  >> str;
        return str;
    }
    friend integer abs(const integer &num)
    {
        integer res(num);
        res.sign = 1;
        return res;
    }
    static integer rand(int_fast64_t size_f)
    {
        static std::random_device rd;
        static std::mt19937 eng(std::time(nullptr));
        static std::uniform_int_distribution<int_fast64_t> dist(0, 9);
        std::string  tmp  = "";
        int_fast64_t upper = int_fast64_t(std::floor(size_f/3.32193));
        for(int_fast64_t i = 0; i < upper; i++)
        {
            tmp += std::to_string(dist(eng));
        }
        integer res(tmp);
        return res;
    }
    friend std::istream& operator>>(std::istream &stream, integer &rhs)
    {
        std::string s;
        stream >> s;
        rhs.read(s);
        return stream;
    }
    friend std::ostream& operator<<(std::ostream &stream, const integer &rhs)
    {
        if (rhs.sign == -1)
            stream << '-';
        stream << (rhs.digits.empty() ? 0 : rhs.digits.back());
        for (int_fast64_t i = (int_fast64_t) rhs.digits.size() - 2; i >= 0; --i)
            stream << std::setw(base.radix) << std::setfill('0') << rhs.digits[i];
        return stream;
    }
    friend int_fast64_t log10(const integer &num)
    {
        return size(num);
    }
    friend int_fast64_t log2(const integer &num)
    {
        return int_fast64_t(std::round(size(num)*3.32192809493));
    }
    friend void debug(const integer &num)
    {
        std::cout<<num.sign<<std::endl;
        for(auto v: num.digits)
            std::cout<<v<<std::endl;
    }
    friend integer min(const integer &lhs,const integer &rhs)
    {
        return mpa::min<integer>(lhs, rhs);
    }
    friend integer max(const integer &lhs,const integer &rhs)
    {
        return mpa::max<integer>(lhs, rhs);
    }
    friend integer gcd(const integer &lhs,const integer &rhs)
    {
        return mpa::gcd<integer>(lhs, rhs);
    }
    friend integer lcm(const integer &lhs,const integer &rhs)
    {
        return mpa::lcm<integer>(lhs, rhs);
    }
    friend integer sqrt(const integer &num)
    {
        return mpa::sqrt<integer>(num);
    }
    template<typename int_t>
    friend integer pow(const integer &lhs,const int_t &rhs)
    {
        return mpa::pow<integer>(lhs, integer(rhs));
    }
    friend integer modinv(const integer &lhs,const integer &rhs)
    {
        return mpa::modinv<integer>(lhs, rhs);
    }
    friend integer modexp(const integer &lhs,const integer &rhs, const integer &mod)
    {
        return mpa::modexp<integer>(lhs, rhs, mod);
    }
    friend std::vector<integer> sieve(const integer &lhs,const integer &rhs)
    {
        return mpa::sieve<integer>(lhs, rhs);
    }
};
/**
 * hash
 */
namespace std
{
template<>
struct hash<integer>
{
    size_t
    operator()(const integer & obj) const
    {
        return hash<std::string>()(obj.c_str());
    }
};
}
#endif
