# intf
Multiple Precision Integer Arithmetic C++ Library.  

#### Roadmap

| Feature       | Implementation                                   | Next Candidate       |
|:-------------:| ------------------------------------------------:| --------------------:|
| Constructors  | std::string, int, long int, long long int, intf  | <ul><li>- [ ] </li></ul> |
| Containers    | std::vector<<int>>                                 | std::vector<std::bitset<<int>> > |
| +             | standard                                         | <ul><li>- [ ] </li></ul> |
| -             | standard                                         | <ul><li>- [ ] </li></ul> |
| *             | Long multiplication                              | Karatsuba multiplication, Toom–Cook, Schönhage–Strassen, Fürer's algorithm, Harvey and van der Hoeven|
| /             | Approximate Division                             | Newton–Raphson, Goldschmidt, Binomial Goldschmidt, Barrett reduction, Montgomery reduction |
| %             | Approximate Division                             | Newton–Raphson, Goldschmidt, Binomial Goldschmidt, Barrett reduction, Montgomery reduction |
| pow           | standard                                         | Exponentiation by squaring |
| sqrt          | bisection                                        | Babylonian(Heron), Newton-Raphson, Goldschmidt, Bakhshali approximation, Fast inverse square root |
| modexp        | <ul><li>- [ ] </li></ul>                         | Right-to-left binary     |
| modinv        | <ul><li>- [ ] </li></ul>                         | <ul><li>- [ ] </li></ul> |
| abs           | <ul><li>- [x] </li></ul>                         | <ul><li>- [ ] </li></ul> |
| >>            | repetitive approximate division                  | <ul><li>- [ ] </li></ul> |
| <<            | repetitive approximate division                  | <ul><li>- [ ] </li></ul> |
| &             | <ul><li>- [ ] </li></ul>                         | <ul><li>- [ ] </li></ul> |
| ^             | <ul><li>- [ ] </li></ul>                         | <ul><li>- [ ] </li></ul> |
| xor           | <ul><li>- [ ] </li></ul>                         | <ul><li>- [ ] </li></ul> |
| ostream>>     | <ul><li>- [x] </li></ul>                         | <ul><li>- [ ] </li></ul> |
| ostream<<     | <ul><li>- [x] </li></ul>                         | <ul><li>- [ ] </li></ul> |
| gcd           | <ul><li>- [ ] </li></ul>                         | <ul><li>- [ ] </li></ul> |
| gcdeuc        | <ul><li>- [ ] </li></ul>                         | <ul><li>- [ ] </li></ul> |
| lcm           | <ul><li>- [ ] </li></ul>                         | <ul><li>- [ ] </li></ul> |  

#### Next Steps:  
- Code Refactoring
- Templating
- Impmementing Next Feature Candidates
- Implementing Missing Features  

#### Requirements:  
- GCC compiler with C++11 support.
- CMake 3.10.2
- Python 3  

#### Installation:  
```sh
git clone https://github.com/AlyShmahell/intf
```
```sh
cd intf
```
```sh
python3 install.py
```
#### Example:  
```cpp
#include <intf/intf.hpp>

int main()
{
    intf a = 4;
    intf b = 3;
    intf c;
    std::cout<<(a/b)<<std::endl;
    std::cout<<(a%b)<<std::endl;
    std::cout<<(a*b)<<std::endl;
    std::cout<<(a-b)<<std::endl;
    std::cout<<(a+b)<<std::endl;
    std::cout<<pow(a,3)/pow(b,3)<<std::endl;
    std::cout<<pow(a,3)%pow(b,3)<<std::endl;
    std::cout<<pow(a,2)*pow(b,2)<<std::endl;
    std::cout<<pow(a,3)-pow(b,3)<<std::endl;
    std::cout<<pow(a,3)+pow(b,3)<<std::endl;
    std::cout<<(a--)<<std::endl;
    std::cout<<(--a)<<std::endl;
    std::cout<<(a++)<<std::endl;
    std::cout<<(++a)<<std::endl;
    std::cout<<(a<<3)<<std::endl;
    std::cout<<(a>>4)<<std::endl;
    std::cout<<(a*a)<<std::endl;
    std::cout<<(a-a)<<std::endl;
    std::cout<<(a+a)<<std::endl;
    c = sqrt(a);
    std::cout<<pow(c,2)<<std::endl;
    a = a*(a+2);
    a >>= 1;
    std::cout<<a<<std::endl;
    a >>= intf(2);
    std::cout<<a<<std::endl;
    a <<= 3;
    std::cout<<a<<std::endl;
    a <<= intf(4);
    std::cout<<a<<std::endl;
    a += 3;
    std::cout<<a<<std::endl;
    a += b;
    std::cout<<a<<std::endl;
    a -= 3;
    std::cout<<a<<std::endl;
    a -= b;
    std::cout<<a<<std::endl;
    a *= 3;
    std::cout<<a<<std::endl;
    a *= b;
    std::cout<<a<<std::endl;
    a /= 3+1;
    std::cout<<a<<std::endl;
    a /= b+1;
    std::cout<<a<<std::endl;
    a %= 3+1;
    std::cout<<a<<std::endl;
    a %= b+1;
    std::cout<<a<<std::endl;
    return 0;
}
```