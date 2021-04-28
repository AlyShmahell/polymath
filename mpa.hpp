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
