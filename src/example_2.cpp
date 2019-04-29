#include "../include/intf.hpp"

int main()
{
    intf a = pow(2, 4096);
    std::cout<<"a: "<<a<<std::endl;
    intf b = pow(2, 4096);
    std::cout<<"b: "<<b<<std::endl;
    intf c = pow(2, 4096);
    std::cout<<"c: "<<c<<std::endl;
    intf d = a*b;
    std::cout<<"d: "<<d<<std::endl;
    intf e = d/c;
    std::cout<<"e: "<<e<<std::endl;
    return 0;
}
