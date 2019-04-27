#include "../include/intf.hpp"

int main()
{
    intf a = 4;
    intf b = 3;
    intf c = "3425";
    intf d;

    std::cout<<"c = \"3425\""<<std::endl;
    std::cout<<"c: ";
    std::cout<<c<<std::endl;

    d = rand(128);
    std::cout<<"d = rand(4096)"<<std::endl;
    std::cout<<"d: ";
    std::cout<<d<<std::endl;

    c = log2(d);
    std::cout<<"c = log2(d)"<<std::endl;
    std::cout<<"c: ";
    std::cout<<c<<std::endl;

    c = log10(d);
    std::cout<<"c = log10(d)"<<std::endl;
    std::cout<<"c: ";
    std::cout<<c<<std::endl;

    c = d/rand(4);
    std::cout<<"c = d/rand(4)"<<std::endl;
    std::cout<<"c: ";
    std::cout<<c<<std::endl;

    intf t1f, t2f;
    int t1, t2, r1, r2;
    for(int i = 0; i < 10; i++)
    {
        a = i;
        for(long long int j = 1; j < 10; j++)
        {
            r1 = rand();
            t1  = -j-r1;
            t1f = -j-r1;
            r2 = rand();
            t2  = i - r2;
            t2f = i - r2;
            std::cout<<"i: "<<i<<", j: "<<j<<std::endl;
            std::cout<<"r1: "<<r1<<", r2: "<<r2<<std::endl;
            std::cout<<"t1  = -j-r1: ";
            std::cout<<t1<<std::endl;
            std::cout<<"t2  = i - r2: ";
            std::cout<<t2<<std::endl;
            std::cout<<"t1f-t2f: ";
            std::cout<<t1f-t2f<<std::endl;
            std::cout<<"t1-t2: ";
            std::cout<<t1-t2<<std::endl;
            t1-=t2;
            std::cout<<"t1-=t2"<<std::endl;
            std::cout<<"t1: ";
            std::cout<<t1<<std::endl;
            t1f-=t2f;
            std::cout<<"t1f-=t2f"<<std::endl;
            std::cout<<"t1f: ";
            std::cout<<t1f<<std::endl;
        }
    }

    std::cout<<"a: "<<a<<", b: "<<b<<std::endl;
    std::cout<<"(a/b): ";
    std::cout<<(a/b)<<std::endl;
    std::cout<<"(a%b): ";
    std::cout<<(a%b)<<std::endl;
    std::cout<<"(a*b): ";
    std::cout<<(a*b)<<std::endl;
    std::cout<<"(a-b): ";
    std::cout<<(a-b)<<std::endl;
    std::cout<<"(a+b): ";
    std::cout<<(a+b)<<std::endl;
    std::cout<<"pow(a,3)/pow(b,3): ";
    std::cout<<pow(a,3)/pow(b,3)<<std::endl;
    std::cout<<"pow(a,3)%pow(b,3): ";
    std::cout<<pow(a,3)%pow(b,3)<<std::endl;
    std::cout<<"pow(a,2)*pow(b,2): ";
    std::cout<<pow(a,2)*pow(b,2)<<std::endl;
    std::cout<<"pow(a,3)-pow(b,3): ";
    std::cout<<pow(a,3)-pow(b,3)<<std::endl;
    std::cout<<"pow(a,3)+pow(b,3): ";
    std::cout<<pow(a,3)+pow(b,3)<<std::endl;
    std::cout<<"(a--): ";
    std::cout<<(a--)<<std::endl;
    std::cout<<"(--a): ";
    std::cout<<(--a)<<std::endl;
    std::cout<<"(a++): ";
    std::cout<<(a++)<<std::endl;
    std::cout<<"(++a): ";
    std::cout<<(++a)<<std::endl;
    std::cout<<"(a<<3): ";
    std::cout<<(a<<3)<<std::endl;
    std::cout<<"(a>>4): ";
    std::cout<<(a>>4)<<std::endl;
    std::cout<<"(a*a): ";
    std::cout<<(a*a)<<std::endl;
    std::cout<<"(a-a): ";
    std::cout<<(a-a)<<std::endl;
    std::cout<<"(a+a): ";
    std::cout<<(a+a)<<std::endl;
    c = sqrt(a);
    std::cout<<"c = sqrt(a): ";
    std::cout<<c<<std::endl;
    std::cout<<"pow(c,2): ";
    std::cout<<pow(c,2)<<std::endl;
    a = a*(a+2);
    std::cout<<"a = a*(a+2): ";
    std::cout<<a<<std::endl;
    a >>= 1;
    std::cout<<" a >>= 1: ";
    std::cout<<a<<std::endl;
    a >>= intf(2);
    std::cout<<"a >>= intf(2): ";
    std::cout<<a<<std::endl;
    a <<= 3;
    std::cout<<"a <<= 3: ";
    std::cout<<a<<std::endl;
    a <<= intf(4);
    std::cout<<"a <<= intf(4): ";
    std::cout<<a<<std::endl;
    a += 3;
    std::cout<<"a += 3: ";
    std::cout<<a<<std::endl;
    a += b;
    std::cout<<"a += b: ";
    std::cout<<a<<std::endl;
    a -= 3;
    std::cout<<"a -= 3: ";
    std::cout<<a<<std::endl;
    a -= b;
    std::cout<<"a -= b: ";
    std::cout<<a<<std::endl;
    a *= 3;
    std::cout<<"a *= 3: ";
    std::cout<<a<<std::endl;
    a *= b;
    std::cout<<"a *= b: ";
    std::cout<<a<<std::endl;
    a /= 3+1;
    std::cout<<"a /= 3+1: ";
    std::cout<<a<<std::endl;
    a /= b+1;
    std::cout<<"a /= b+1: ";
    std::cout<<a<<std::endl;
    a %= 3+1;
    std::cout<<"a %= 3+1: ";
    std::cout<<a<<std::endl;
    a %= b+1;
    std::cout<<"a %= b+1: ";
    std::cout<<a<<std::endl;
    return 0;
}
