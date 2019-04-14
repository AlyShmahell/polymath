#include <iostream>
using namespace std;

template <typename T>
T sqrt(T n)
{
    T x = n;
    T y = 1;
    T error = 1;
    while (x - y > error)
    {
        x = (x + y) / 2;
        y = n / x;
    }
    return x;
}

int main()
{
    int n = 250000;
    cout << "number: " << n << ", sqrt: " << sqrt(n);
}

