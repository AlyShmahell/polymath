#include "../include/intf.hpp"

int main()
{
    intf a = 4;
    intf b = 3;
    intf c;

    intf t1f, t2f;
    int t1, t2, r1, r2;
    for(int i = 0; i < 10; i++)
    {
        a = i;
        for(int j = 1; j < 10; j++)
        {
            r1 = rand();
            t1  = -j-r1;
            t1f = -j-r1;
            r2 = rand();
            t2  = i - r2;
            t2f = i - r2;
            std::cout<<r1<<", "<<r2<<std::endl;
            std::cout<<t1f-t2f<<", "<<t1-t2<<std::endl;
            t1-=t2;
            t1f-=t2f;
            std::cout<<t1f<<", "<<t1<<std::endl;
        }
    }


    std::cout<<(a/b)<<std::endl;
    std::cout<<(a%b)<<std::endl;
    std::cout<<(a*b)<<std::endl;
    std::cout<<(a-b)<<std::endl;
    std::cout<<(a+b)<<std::endl;
    std::cout<<pow(a,3)/pow(b,3)<<std::endl;
    std::cout<<pow(a,3)%pow(b,3)<<std::endl;
    std::cout<<pow(a,2)*pow(b,2)<<std::endl;
    std::cout<<pow(a,3)-pow(b,3)<<std::endl;
    std::cout<<pow(a,3)+pow(b,3)<<std::endl;
    std::cout<<(a--)<<std::endl;
    std::cout<<(--a)<<std::endl;
    std::cout<<(a++)<<std::endl;
    std::cout<<(++a)<<std::endl;
    std::cout<<(a<<3)<<std::endl;
    std::cout<<(a>>4)<<std::endl;
    std::cout<<(a*a)<<std::endl;
    std::cout<<(a-a)<<std::endl;
    std::cout<<(a+a)<<std::endl;
    c = sqrt(a);
    std::cout<<pow(c,2)<<std::endl;
    a = a*(a+2);
    a >>= 1;
    std::cout<<a<<std::endl;
    a >>= intf(2);
    std::cout<<a<<std::endl;
    a <<= 3;
    std::cout<<a<<std::endl;
    a <<= intf(4);
    std::cout<<a<<std::endl;
    a += 3;
    std::cout<<a<<std::endl;
    a += b;
    std::cout<<a<<std::endl;
    a -= 3;
    std::cout<<a<<std::endl;
    a -= b;
    std::cout<<a<<std::endl;
    a *= 3;
    std::cout<<a<<std::endl;
    a *= b;
    std::cout<<a<<std::endl;
    a /= 3+1;
    std::cout<<a<<std::endl;
    a /= b+1;
    std::cout<<a<<std::endl;
    a %= 3+1;
    std::cout<<a<<std::endl;
    a %= b+1;
    std::cout<<a<<std::endl;
    return 0;
}
