#include "../include/intf.hpp"
#include <cassert>
#include <unordered_map>

int pow(int a, int n)
{
    int result = 1;
    for(int i = 0; i < n; i++)
        result *= a;
    return result;
}

int main()
{
    intf x = "3425";
    x = "3425";
    assert(x==intf(3425));
    x = rand(128);
    assert(log2(x)<=128);
    assert(log10(x)<=int(128/3.322));

    int r1;
    int t1;
    intf t1f;
    int r2;
    int t2;
    intf t2f;

    intf a;
    intf b;
    intf c;
    int k;
    std::vector<intf> v;
    std::unordered_map<intf, intf> umap;
    for(int i = 0; i < 100; i++)
    {
        a = i;
        for(int j = 1; j < 100; j++)
        {
            r1 = rand();
            t1  = -j-r1;
            t1f = -j-r1;
            r2 = rand();
            t2  = i - r2;
            t2f = i - r2;
            //exit(0);
            assert((t1f-t2f) == intf(t1-t2));
            t1-=t2;
            t1f-=t2f;
            assert((t1f) == intf(t1));


            assert(std::max(t1f, t2f) == intf(std::max(t1, t2)));
            assert(std::min(t1f, t2f) == intf(std::min(t1, t2)));
            assert(std::min(t1f, t2f) <= intf(std::max(t1, t2)));

            b = j;
            v.push_back(b);
            assert(v[v.size()-1] == b);
            umap.insert({b, b});
            assert(umap[b] == b);
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
