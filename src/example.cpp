#include "../include/intf.hpp"

int main()
{
    intf a = 4;
    intf b = 3;
    intf c;
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
