#include <random>
#include <time.h>
#include <unordered_map>
#include "integer.hpp"
#include "mpa.hpp"
#ifndef RSA_HPP_
#define RSA_HPP_

struct Key
{
    std::string  name;
    integer      exp;
    integer      mod;
    friend std::ostream& operator<<(std::ostream& out, Key& self)
    {
        out << "name: " << self.name
            << std::endl
            << "exp: " << self.exp
            << std::endl
            << "mod: " << self.mod
            << std::endl
            << "***"
            << std::endl;
        return out;
    }
};

class RSA
{
private:
    Key priv;
public:
    Key pub;
    RSA(integer k)
    {
        mpa::primality<integer> check(8);
        integer p = mpa::prime(k/2, check);
        integer q = mpa::prime(k/2, check);
        integer e = mpa::prime(32, check);
        while(gcd(e, (p-1)*(q-1)) != 1)
        {
            e = mpa::prime(32, check);
        }
        integer n  = p*q;
        integer d  = modinv(e, (p-1)*(q-1));
        pub  = {"pub", e, n};
        priv = {"priv", d, n};
    }
    friend std::ostream& operator<<(std::ostream& out, RSA& self)
    {
        out<<self.pub<<self.priv;
        return out;
    }
    integer encrypt(integer plain)
    {
        return modexp(plain, pub.exp, pub.mod);
    }
    integer decrypt(integer cipher)
    {
        //std::cout<<"d: "<<cipher<<", "<<priv.exp<<", "<< pub.mod<<std::endl;
        return modexp(cipher, priv.exp, pub.mod);
    }
};


#endif
