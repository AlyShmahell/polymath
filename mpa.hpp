#include <vector>
#include <algorithm>
#include <stdexcept>
#ifndef MPA
#define MPA
namespace mpa
{
/**
* Sieve
*/
template<typename large>
std::vector<large> sieve(const large lower, const large upper)
{
    std::vector<large> ko;
    for(large i=2; i*i<=upper; i++)
        for(large j=(lower/i)*i; j<=upper; j+=i)
            if(j!=i&&j>=lower)
                ko.push_back(j-lower);
    std::vector<large> res;
    for(large i=0; i<=upper-lower; i++)
        if(std::find(ko.begin(), ko.end(), i) == ko.end())
            res.push_back(lower+i);
    return res;
}
/**
 * Modular Exponentiation
 */
template<typename large>
large modexp(const large bas, const large exp, const large mod)
{
    if (mod == 1)
        return 0;
    large b = bas % mod, e = exp, m = mod, r = 1;
    while(e > 0)
    {
        if (e % 2 == 1)
            r = (r * b) % m;
        e = e / 2;
        b = (b * b) % m;
    }
    return r;
}
/**
  * Modular Inverse
  */
template<typename large>
large modinv(const large a, const large m)
{
    struct
    {
        large operator()(large a, large m)
        {
            large tmp;
            if(a < m)
                std::swap(a, m);
            large x_p = 0;
            large x_c = 1;
            large r_p = a;
            large r_c = m;
            while(r_c!=0)
            {
                tmp = x_c;
                x_c = x_p-(r_p/r_c)*x_c;
                x_p = tmp;
                tmp = r_c;
                r_c = r_p%r_c;
                r_p = tmp;
            }
            if(x_p < 0)
                x_p += a;
            return x_p;
        }
    } eea;
    return eea(a, m);
}
/**
  * Long Multiplication
  */
template<typename large, typename small>
struct mul
{
public:
    large operator()(const large lhs, const small rhs, auto base)
    {
        large and = lhs; //multiplicand
        small ier = rhs; //multiplier
        if (ier < 0)
            and.sign = -and.sign, ier = -ier;
        for (small i = 0, carry = 0; i < (small) and.digits.size() || carry; ++i)
        {
            if (i == (small) and.digits.size())
                and.digits.push_back(0);
            small cur     = and.digits[i] * (small) ier + carry;
            carry         = cur / base.value;
            and.digits[i] = cur % base.value;
        }
        and.trim();
        return and;
    }
};
/**
  * Karatsuba Multiplication
  */
template<typename large>
struct karatsuba
{
public:
    large operator()(large lhs, large rhs, auto base)
    {
        large res;
        std::vector<int_fast64_t> and = lhs.digits; //multiplicand
        std::vector<int_fast64_t> ier = rhs.digits; //multiplier
        while (and.size() < ier.size())
            and.push_back(0);
        while (ier.size() < and.size())
            ier.push_back(0);
        while (and.size() & (and.size() - 1))
            and.push_back(0), ier.push_back(0);
        std::vector<int_fast64_t> tmp = op(and, ier);
        res.sign = lhs.sign * rhs.sign;
        for (int_fast64_t i = 0, carry = 0; i < tmp.size(); i++)
        {
            int_fast64_t cur = tmp[i] + carry;
            res.digits.push_back(cur % base.value);
            carry = cur / base.value;
        }
        res.trim();
        return res;
    }
    std::vector<int_fast64_t> op(const std::vector<int_fast64_t> &lhs, const std::vector<int_fast64_t> &rhs)
    {
        int_fast64_t n = lhs.size();
        std::vector<int_fast64_t> res(n + n);
        if (n <= 32)
        {
            for (int_fast64_t i = 0; i < n; i++)
                for (int_fast64_t j = 0; j < n; j++)
                    res[i + j] += lhs[i] * rhs[j];
            return res;
        }
        int_fast64_t k = n >> 1;
        std::vector<int_fast64_t> a(lhs.begin(),     lhs.begin() + k);
        std::vector<int_fast64_t> b(lhs.begin() + k, lhs.end());
        std::vector<int_fast64_t> c(rhs.begin(),     rhs.begin() + k);
        std::vector<int_fast64_t> d(rhs.begin() + k, rhs.end());
        std::vector<int_fast64_t> ac = op(a, c);
        std::vector<int_fast64_t> bd = op(b, d);
        for (int_fast64_t i = 0; i < k; i++)
        {
            b[i] += a[i];
            d[i] += c[i];
        }
        std::vector<int_fast64_t> aPbMcPd = op(b, d);
        for (int_fast64_t i = 0; i < aPbMcPd.size(); i++)
        {
            res[i]     += ac[i];
            res[i + k] += aPbMcPd[i] - ac[i] - bd[i];
            res[i + n] += bd[i];
        }
        return res;
    }
};
/**
  * Quotient/Remainder
  */
template<typename int_u>
struct qr
{
    int_u q,r;
} ;
/**
  * Long Modulo
  */
template<typename large, typename small>
struct mod
{
    small operator()(const large &lhs, const small &rhs, auto base)
    {
        large num = lhs;
        small den = rhs;
        if (den < 0)
            den = -den;
        small rem = 0;
        for (small i = num.digits.size() - 1; i >= 0; --i)
            rem = (num.digits[i] + rem * (small) base.value) % den;
        return rem * num.sign;
    }
};

/**
  * Long Division
  */
template<typename large, typename small>
struct div
{
    large operator()(const large &lhs, const small &rhs, auto base)
    {
        large num = lhs;
        small den = rhs;
        if (den < 0)
            den = -den, num.sign = -num.sign;
        for (small i = num.digits.size() - 1, rem = 0, cur=0; i >= 0; --i)
        {
            cur           = num.digits[i] + rem * base.value;
            num.digits[i] = cur / den;
            rem           = cur % den;
        }
        num.trim();
        return num;
    }
};
/**
  * SRT Division
  */
template<typename large>
class srt
{
public:
    qr<large> operator()(const large &lhs, const large &rhs, auto base)
    {
        qr<large> res;
        int_fast64_t norm = base.value / (rhs.digits.back() + 1);
        large lhsn = abs(lhs) * norm;
        large rhsn = abs(rhs) * norm;
        res.q.digits.resize(lhsn.digits.size());
        for (int_fast64_t i = lhsn.digits.size() - 1; i >= 0; i--)
        {
            res.r *= base.value;
            res.r += lhsn.digits[i];
            int_fast64_t s1 = res.r.digits.size() <= rhsn.digits.size()     ? 0 : res.r.digits[rhsn.digits.size()    ];
            int_fast64_t s2 = res.r.digits.size() <= rhsn.digits.size() - 1 ? 0 : res.r.digits[rhsn.digits.size() - 1];
            int_fast64_t q  = (base.value * s1 + s2) / rhsn.digits.back();
            res.r -= rhsn * q;
            while (res.r < 0)
                res.r += rhsn, --q;
            res.q.digits[i] = q;
        }
        res.q.sign = lhs.sign * rhs.sign;
        res.r.sign = lhs.sign;
        res.q.trim();
        res.r.trim();
        res.r /= norm;
        return res;
    }
};
/**
  * Power Function
  */
template<typename large>
large pow(const large &bas, const large &exp)
{
    if (!(std::is_same<large, large>::value || std::is_integral<large>::value))
    {
        throw std::runtime_error("rhs is not integral");
    }
    large res = 1;
    large b   = bas;
    large e   = exp;
    while(e != 0)
    {
        if(e%2)
            res *= b;
        b *= b;
        e /= 2;
    }
    return res;
}
/**
  * Square Root Function
  */
template<typename large>
large sqrt(const large &num)
{
    large high = num, low = (num+1)/2;
    while (low < high)
    {
        high = low;
        low  = (low+num/low)/2;
    }
    return high;
}
/**
  * Greatest Common Divisor Function
  */
template<typename large>
large gcd(const large &lhs, const large &rhs)
{
    return rhs == 0 ? lhs : gcd(rhs, lhs % rhs);
}
/**
  * Least Common Multiple Function
  */
template<typename large>
large lcm(const large &lhs, const large &rhs)
{
    return lhs / gcd(lhs, rhs) * rhs;
}
/**
  * Maximum Function
  */
template<typename large>
large max(const large &lhs,const large &rhs)
{
    if(lhs<rhs)
    {
        return lhs;
    }
    return rhs;
}
/**
  * Minimum Function
  */
template<typename large>
large min(const large &lhs,const large &rhs)
{
    if(lhs>rhs)
    {
        return rhs;
    }
    return lhs;
}
/**
  * Primality Test
  */
template<typename large>
struct primality
{
    large k;
    primality(large f): k(f) {}
    struct
    {
        std::vector<large> p = sieve<large>(2, 100);
        bool operator()(large num)
        {
            for (auto v: p)
                if(num%v==0)
                    return false;
            return true;
        }
    } provable;
    bool miller_rabin(large n, large d)
    {
        large a = 2 + large(std::rand()) % (n - 4);
        large x = modexp<large>(a, d, n);
        if (x == 1 || x == n-1)
            return true;
        while (d != n-1)
        {
            x = (x * x) % n;
            d *= 2;
            if (x == 1)
                return false;
            if (x == n-1)
                return true;
        }
        return false;
    }
    bool fermat(large n, large k)
    {
        if (n == 1)
            return false;
        for (large i = 0; i < k; i++)
        {
            large x = large(std::rand()) % (n - 1) + 1;
            if (modexp<large>(x, n - 1, n) != 1)
                return false;
        }
        return true;
    }
    bool operator()(large n)
    {
        if (n <= 1 || n == 4)
            return false;
        if (n <= 3)
            return true;
        if (!provable(n) || !fermat(n, k))
            return false;
        if (!fermat(n, k))
            return false;
        large d = n - 1;
        while (d % 2 == 0)
            d >>= 1;
        for (large i = 0; i < k; i++)
            if (!miller_rabin(n, d))
                return false;
        return true;
    }
};
/**
  * Prime Generation
  */
template<typename large>
large prime(int k, primality<large> check)
{
    struct
    {
        large operator()(int k)
        {
            large c = large::rand(k);
            c += (c%2-1);
            return c;
        }
    } candidate;
    large res = candidate(k);
    do
    {
        if(check(res))
            break;
        res += 2;
    }
    while(true);
    return res;
}
}
#endif
