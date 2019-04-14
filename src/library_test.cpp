#include "../include/intf.hpp"
#include <cassert>

int pow(int a, int n)
{
    int result = 1;
    for(int i = 0; i < n; i++)
        result *= a;
    return result;
}

int main()
{
    intf a;
    intf b;
    intf c;
    int k;
    for(int i = 0; i < 100; i++)
    {
        a = i;
        for(int j = 1; j < 100; j++)
        {
            b = j;
            assert((a/b) == intf(i/j));
            assert((a*b) == intf(i*j));
            assert((a-b) == intf(i-j));
            assert((a+b) == intf(i+j));
            assert((a%b) == intf(i%j));
            assert(pow(a,3)/pow(b,3) == intf(pow(i,3)/pow(j,3)));
            assert(pow(a,2)*pow(b,2) == intf(pow(i,2)*pow(j,2)));
            assert(pow(a,3)-pow(b,3) == intf(pow(i,3)-pow(j,3)));
            assert(pow(a,3)+pow(b,3) == intf(pow(i,3)+pow(j,3)));
            assert(pow(a,3)%pow(b,3) == intf(pow(i,3)%pow(j,3)));
        }
        assert((--a)  ==  intf(--i));
        assert((a--)  ==  intf(i--));
        assert((++a)  ==  intf(++i));
        assert((a++)  ==  intf(i++));
        assert((a<<3) ==  intf(i<<3));
        assert((a>>4) ==  intf(i>>4));
        assert((a*a)  ==  intf(i*i));
        assert((a-a)  ==  intf(i-i));
        assert((a+a)  ==  intf(i+i));
        c = sqrt(a+1);
        assert(pow(c,2) <= a+1 && pow((c+1),2) >= a+1);
        k = i*(i+2);
        a = i*(i+2);
        a >>= 1;
        k >>= 1;
        assert(a==intf(k));
        a >>= intf(2);
        k >>= 2;
        assert(a==intf(k));
        a <<= 3;
        k <<= 3;
        assert(a==intf(k));
        a <<= intf(4);
        k <<= 4;
        assert(a==intf(k));
        a += i;
        k += i;
        assert(a==intf(k));
        a += i;
        k += i;
        assert(a==intf(k));
        a -= i;
        k -= i;
        assert(a==intf(k));
        a -= i;
        k -= i;
        assert(a==intf(k));
        a *= i;
        k *= i;
        assert(a==intf(k));
        a *= i;
        k *= i;
        assert(a==intf(k));
        a /= i+1;
        k /= i+1;
        assert(a==intf(k));
        a /= i+1;
        k /= i+1;
        assert(a==intf(k));
        a %= i+1;
        k %= i+1;
        assert(a==intf(k));
        a %= i+1;
        k %= i+1;
        assert(a==intf(k));
    }
    std::cout<<"Success!\n";
    return 0;
}
