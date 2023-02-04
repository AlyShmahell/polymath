#include <cstdint>
#include <iostream>

class XorShift64 {
  public:
    XorShift64(uint64_t seed) : state(seed) {}

    uint64_t next() {
        uint64_t x = state;
        x ^= x >> 12;
        x ^= x << 25;
        x ^= x >> 27;
        state = x;
        return x * 0x2545F4914F6CDD1D;
    }

  private:
    uint64_t state;
};

int main()
{
    XorShift64 xorshift(2423);
    for (int i = 0; i < 10; i++)
        std::cout<<xorshift.next()<<" ";
}