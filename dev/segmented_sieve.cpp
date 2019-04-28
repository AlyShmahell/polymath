#include <iostream>
#include <unordered_map>
#include "../include/intf.hpp"
using namespace std;

template<typename int_t>
std::vector<int_t> segmented_sieve(int_t a, int_t b)
{
    a = (a==1)? a+1: a;
    std::unordered_map<int_t, int_t> p;
    int_t i = 2;
    int_t k;
    int_t j;
    for(i; i*i <= b; i++)
    {
        std::cout<<"i: "<<i<<std::endl;
        k = (a/i)*i;
        for(j = k; j <= b; j += i)
            if(j!=i&&j>=a&&j-a<p.size())
            {
                p.insert({j-a, int_t(0)});
            }
    }
    std::vector<int_t> result;
    for(int_t i=0; i < b-a; i++)
        if(p.find(i) != p.end() && p[i]==1)
            result.push_back(a+i);
    return result;
}


template<typename int_t>
int_t gen_prime(int_t low, int_t high)
{
    srand(time(NULL));
    std::vector<int_t> primes = segmented_sieve<int_t>(low, high);
    int divisor = primes.size();
    int k;
    do { k = rand() / divisor; } while (k >= primes.size());
    return primes[k];
}

int main()
{
    std::cout<<"primes: "<<std::endl;
    vector<intf> primes = segmented_sieve<intf>(rand(16), rand(32));
    for(auto v: primes)
        std::cout<<v<<std::endl;
    std::cout<<"prime: "<<std::endl;
    intf prime = gen_prime<intf>(1, 99);
    std::cout<<prime<<std::endl;
}
