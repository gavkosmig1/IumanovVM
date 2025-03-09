#include <iostream>
#include <inttypes.h>

extern "C" void multstore(uint64_t, uint64_t, uint64_t*);

int main()
{
    uint64_t d;
    multstore(2, 3, &d);
    std::cout << "2 * 3 --> " << d << std::endl;
}

extern "C" uint64_t mult2(uint64_t a, uint64_t b)
{
    uint64_t s = a * b;
    return s;
}