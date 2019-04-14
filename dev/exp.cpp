#include <iostream>
#include <math.h>
template<typename T>
T exp(T base, T exponential, T modulo)
{
    if (modulo == 1)
        return 0;
    T result = 1;
    base = base % modulo;
    while(exponential > 0)
    {
        if (exponential % 2 == 1)
            result = (result * base) % modulo;
        exponential = exponential / 2; // exponential = exponential >> 1;
        base = (base * base) % modulo;
    }
    return result;
}

int main()
{
    std::cout<<exp(10,3,7);
}
