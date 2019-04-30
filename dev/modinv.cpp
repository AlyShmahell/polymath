#include <iostream>
#include <ctime>
using namespace std;

template<typename int_t>
struct eea_result
{
    int_t a;
    int_t m;
    int_t x;
    int_t y;
    int_t _gcd;
    eea_result(int_t a_t, int_t m_t, int_t x_t, int_t y_t, int_t gcd_t):
        a(a_t), m(m_t), x(x_t), y(y_t), _gcd(gcd_t)
    {
        if(_gcd!=1)
            throw std::runtime_error("this is not a valid modinv");
        if ((a*x)%m != _gcd)
            throw std::runtime_error("this is not a valid modinv");
    }
    friend std::ostream& operator<<(std::ostream& out, const eea_result& other)
    {
        out<<other.a
           <<"*"
           <<other.x
           <<" + "
           <<other.m
           <<"*"
           <<other.y
           <<" = "
           <<other._gcd
           <<std::endl;
        out<<other.a
           <<"*"
           <<other.x
           <<" = "
           <<other._gcd
           <<" mod "
           <<other.m
           <<std::endl;
        return out;
    }
};

template<typename int_t>
eea_result<int_t> eea(int_t a, int_t m)
{
    int_t _gcd_curr = m;
    int_t _gcd_prev = a;
    int_t x_curr = 0;
    int_t x_prev = 1;
    int_t quotient;
    int_t temp;
    while(_gcd_curr != 0)
    {
        quotient = _gcd_prev / _gcd_curr;
        //
        temp   = _gcd_curr;
        _gcd_curr = _gcd_prev - quotient * temp;
        _gcd_prev = temp;
        //
        temp   = x_curr;
        x_curr = x_prev - quotient * temp;
        x_prev = temp;
    }
    int_t y;
    if(m != 0)
    {
        y = (_gcd_prev - x_prev * a) / m;
    }
    else
        y = 0;
    eea_result<int_t> result(a,m,x_prev,y,(a*x_prev)%m);
    return result;
}

template<class F, typename... Args>
void measure_time(F func, Args... args)
{
    clock_t start;
    clock_t finish;
    double elapsed_secs;
    start = clock();
    func(args...);
    finish = clock();
    elapsed_secs = double(finish - start)
                   / CLOCKS_PER_SEC;
    std::cout<< "Elapsed Time: "
             << elapsed_secs
             << std::endl
             << "CPU Cycles: "
             << double(finish - start)
             << std::endl;
}

int main()
{
    eea_result<int> eea_r = eea(15, 11);
    cout<<eea_r;
}
