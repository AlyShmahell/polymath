#include <iostream>
using namespace std;
template <typename T>
int expo(T base, T exponent)
{
    T result = 1;
    do
    {
        if (exponent%2 == 1) // if (exponent&1)
        {
            result *= base;
        }
        base *= base;
    }
    while (exponent >>= 1);
    return result;
}

int main()
{
    int b = 10;
    int e = 3;
    cout<<expo(b,e);
}
