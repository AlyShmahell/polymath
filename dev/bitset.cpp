#include <iostream>
#include <bitset>
int main()
{
    std::bitset<7> bit = std::bitset<7>(100);
    std::cout<<bit<<std::endl;
    bit = bit>>3;
    std::cout<<bit<<std::endl;
    std::string str  = bit.to_string();
    int decimal = std::bitset<8>(str).to_ulong();
    std::cout<<decimal<<std::endl;
    return 0;
}
