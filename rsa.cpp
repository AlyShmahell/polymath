#include <iostream>
#include <vector>
#include "rsa.hpp"
#include "integer.hpp"

int main()
{
    RSA rsa(512);
    std::vector<integer> plain = {723};
    std::vector<integer> cipher;
    std::cout<<rsa;
    std::cout << "plain: ";
    for(int i = 0; i < plain.size(); i++)
    {
        std::cout << plain[i];
    }
    std::cout << std::endl;
    std::cout << "cipher: ";
    for(int i = 0; i < plain.size(); i++)
    {

        cipher.push_back(rsa.encrypt(plain[i]));
        std::cout << cipher[i];
    }
    std::cout << std::endl;
    std::cout << "decrypted: ";
    for(int i = 0; i < cipher.size(); i++)
    {
        std::cout << rsa.decrypt(cipher[i]);
    }
    std::cout << std::endl;
}
