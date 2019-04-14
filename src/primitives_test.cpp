#include <iostream>
#include <math.h>
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
    int a;
    int b;
    int c;
    int k;
    for(int i = 0; i < 100; i++)
    {
        a = i;
        for(int j = 1; j < 100; j++)
        {
            b = j;
            assert((a/b) == int(i/j));
            assert((a*b) == int(i*j));
            assert((a-b) == int(i-j));
            assert((a+b) == int(i+j));
            assert((a%b) == int(i%j));
            assert(pow(a,3)/pow(b,3) == int(pow(i,3)/pow(j,3)));
            assert(pow(a,2)*pow(b,2) == int(pow(i,2)*pow(j,2)));
            assert(pow(a,3)-pow(b,3) == int(pow(i,3)-pow(j,3)));
            assert(pow(a,3)+pow(b,3) == int(pow(i,3)+pow(j,3)));
            assert(pow(a,3)%pow(b,3) == int(pow(i,3)%pow(j,3)));
        }
        assert((--a)  ==  int(--i));
        assert((a--)  ==  int(i--));
        assert((++a)  ==  int(++i));
        assert((a++)  ==  int(i++));
        assert((a<<3) ==  int(i<<3));
        assert((a>>4) ==  int(i>>4));
        assert((a*a)  ==  int(i*i));
        assert((a-a)  ==  int(i-i));
        assert((a+a)  ==  int(i+i));
        c = sqrt(a+1);
        assert(pow(c,2) <= a+1 && pow((c+1),2) >= a+1);
        k = i*(i+2);
        a = i*(i+2);
        a >>= 1;
        k >>= 1;
        assert(a==int(k));
        a >>= int(2);
        k >>= 2;
        assert(a==int(k));
        a <<= 3;
        k <<= 3;
        assert(a==int(k));
        a <<= int(4);
        k <<= 4;
        assert(a==int(k));
        a += i;
        k += i;
        assert(a==int(k));
        a += i;
        k += i;
        assert(a==int(k));
        a -= i;
        k -= i;
        assert(a==int(k));
        a -= i;
        k -= i;
        assert(a==int(k));
        a *= i;
        k *= i;
        assert(a==int(k));
        a *= i;
        k *= i;
        assert(a==int(k));
        a /= i+1;
        k /= i+1;
        assert(a==int(k));
        a /= i+1;
        k /= i+1;
        assert(a==int(k));
        a %= i+1;
        k %= i+1;
        assert(a==int(k));
        a %= i+1;
        k %= i+1;
        assert(a==int(k));
    }
    std::cout<<"Success!\n";
    return 0;
}
