/**
 * Citation:
 *     [1] - David Harvey, Joris van Der Hoeven. Integer multiplication in time O(n log n). 
 *           Annals of Mathematics, 2021, ⟨10.4007/annals.2021.193.2.4⟩. ⟨hal-02070778v2⟩
 */
#include <valarray>
#include <algorithm>
#include <random>
#include <complex>
#include <iostream>
#include <climits>

template<class OpType>
void DFT(
    std::valarray< std::complex<OpType> > &coeffs, 
    std::valarray< std::complex<OpType> > &omegas
    ) 
{
    if(coeffs.size() <= 1) return;
    std::valarray< std::complex<OpType> > evens  = coeffs[std::slice(0, coeffs.size()/2, 2)];
    std::valarray< std::complex<OpType> > odds   = coeffs[std::slice(1, coeffs.size()/2, 2)];
    std::valarray< std::complex<OpType> > moegas = omegas[std::slice(0, coeffs.size()/2, 2)];
    DFT(evens, moegas);
    DFT(odds,  moegas);
    for(size_t i = 0; i < coeffs.size()/2; i++) {
        std::complex<OpType> tmp      = omegas[i]*odds[i];
        coeffs[i]                     = evens[i]+tmp;
        coeffs[i+coeffs.size()/2]     = evens[i]-tmp;
    }
}

template<class OpType>
void omega_disk(
    size_t &size, 
    bool clockwise,
    std::valarray< std::complex<OpType> > &empty
    )
{
    int dir = int(clockwise)*2-1;
    for(size_t i = 0; i < size; i++)
        empty[i] = std::polar((OpType)1.0, dir * 2.0 * M_PI * ((OpType)i/(OpType)size));
}

template<class IOType, class OpType>
std::valarray<IOType> harveyhoeven(
    std::valarray<IOType> &multiplicand, 
    std::valarray<IOType> &multiplier
    ) 
{
    size_t size = (size_t)std::pow(
        2,
        std::ceil(
            std::log2(
                std::max(
                    multiplicand.size(), 
                    multiplier.size()
                )
            )
        ) + 1
    );
    const std::complex<OpType> c = 0;
    std::valarray< std::complex<OpType> > lhs(c, size);
    std::valarray< std::complex<OpType> > rhs(c, size);
    std::valarray< std::complex<OpType> > omegas(size);
    std::copy(&multiplicand[0], &multiplicand[0] + multiplicand.size(), &lhs[0]);
    std::copy(&multiplier[0],   &multiplier[0] + multiplier.size(),     &rhs[0]);
    omega_disk(size, false, omegas);
    DFT(lhs, omegas);
    DFT(rhs, omegas);
    for(size_t i = 0; i < size; i++)
        lhs[i] *= rhs[i];
    omega_disk(size, true, omegas);
    DFT(lhs, omegas);
    std::valarray< OpType > chunks(size);
    for(size_t i = 0; i < size; i++) {
        chunks[i] = lhs[i].real()/(OpType)size;
    }
    size -= 1;
    while(size > 0 && std::abs(std::round(chunks[size])) < 4) {
        size--;
    }
    IOType mod = std::pow(10, 4);
    for (size_t idx = size; idx > 0 && idx < ULLONG_MAX; idx--) {
        IOType i        = (IOType)std::round(chunks[idx]);
        chunks[idx-1]  += (OpType)(i / mod);
        chunks[idx]     = (OpType)(i % mod);
    }
    std::valarray<IOType> res(size+1);
    for (size_t idx = 0; idx <= size; idx++) {
        res[idx] = (IOType)std::round(chunks[idx]);
        if (idx != 0)
            res[idx-1] *= std::pow(10, 4 - std::ceil(std::log10(res[idx])));
    }
    return res;
}


int main(){
    std::valarray<std::uint64_t> multiplicand(4);
    std::valarray<std::uint64_t> multiplier(4);
    std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<int> distribution(1000, 9999);
    std::generate(&multiplicand[0], &multiplicand[0] + multiplicand.size(), [&] { return distribution(generator); });
    std::generate(&multiplier[0], &multiplier[0] + multiplier.size(), [&] { return distribution(generator); });
    std::valarray< std::uint64_t > m = harveyhoeven<std::uint64_t, long double>(multiplicand, multiplier);
    for (auto v: multiplicand)
        std::cout<<v<<"";
    std::cout<<" * ";
    for (auto v: multiplier)
        std::cout<<v<<"";
    std::cout<<" = ";
    for (auto v: m)
        std::cout<<v<<"";
    std::cout<<std::endl;
}