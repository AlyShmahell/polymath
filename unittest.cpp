#include "integer.hpp"
#include <cassert>
#include <unordered_map>

int main()
{
    integer x = "3425";
    x = "3425";
    int r1;
    int t1;
    integer t1f;
    int r2;
    int t2;
    integer t2f;
    integer a;
    integer b;
    integer c;
    int k;
    std::vector<integer> v;
    std::unordered_map<integer, integer> umap;
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
            assert((t1f-t2f) == integer(t1-t2));
            t1-=t2;
            t1f-=t2f;
            assert((t1f) == integer(t1));
            assert(std::max(t1f, t2f) == integer(std::max(t1, t2)));
            assert(std::min(t1f, t2f) == integer(std::min(t1, t2)));
            assert(std::min(t1f, t2f) <= integer(std::max(t1, t2)));
            b = j;
            v.push_back(b);
            assert(v[v.size()-1] == b);
            umap.insert({b, b});
            assert(umap[b] == b);
            assert((a/b) == integer(i/j));
            assert((a*b) == integer(i*j));
            assert((a-b) == integer(i-j));
            assert((a+b) == integer(i+j));
            assert((a%b) == integer(i%j));
            assert(pow(a,3)/pow(b,3) == integer((int)pow(i,3)/(int)pow(j,3)));
            assert(pow(a,2)*pow(b,2) == integer((int)pow(i,2)*(int)pow(j,2)));
            assert(pow(a,3)-pow(b,3) == integer((int)pow(i,3)-(int)pow(j,3)));
            assert(pow(a,3)+pow(b,3) == integer((int)pow(i,3)+(int)pow(j,3)));
            assert(pow(a,3)%pow(b,3) == integer((int)pow(i,3)%(int)pow(j,3)));
            x = integer::rand(i*j);
            assert(log2(x)<=i*j);
            assert(log10(x)<=int(i*j/3.32193));
        }
        assert((--a)  ==  integer(--i));
        assert((a--)  ==  integer(i--));
        assert((++a)  ==  integer(++i));
        assert((a++)  ==  integer(i++));
        assert((a<<3) ==  integer(i<<3));
        assert((a>>4) ==  integer(i>>4));
        assert((a*a)  ==  integer(i*i));
        assert((a-a)  ==  integer(i-i));
        assert((a+a)  ==  integer(i+i));
        c = sqrt(a+1);
        assert(pow(c,2) <= a+1 && pow((c+1),2) >= a+1);
        k = i*(i+2);
        a = i*(i+2);
        a >>= 1;
        k >>= 1;
        assert(a==integer(k));
        a >>= integer(2);
        k >>= 2;
        assert(a==integer(k));
        a <<= 3;
        k <<= 3;
        assert(a==integer(k));
        a <<= integer(4);
        k <<= 4;
        assert(a==integer(k));
        a += i;
        k += i;
        assert(a==integer(k));
        a += i;
        k += i;
        assert(a==integer(k));
        a -= i;
        k -= i;
        assert(a==integer(k));
        a -= i;
        k -= i;
        assert(a==integer(k));
        a *= i;
        k *= i;
        assert(a==integer(k));
        a *= i;
        k *= i;
        assert(a==integer(k));
        a /= i+1;
        k /= i+1;
        assert(a==integer(k));
        a /= i+1;
        k /= i+1;
        assert(a==integer(k));
        a %= i+1;
        k %= i+1;
        assert(a==integer(k));
        a %= i+1;
        k %= i+1;
        assert(a==integer(k));
    }
    std::cout<<"Success!\n";
    return 0;
}
