#include <inttypes.h>

uint64_t mult2(uint64_t, uint64_t);

void multstore(uint64_t x, uint64_t y, uint64_t* dest)
{
    uint64_t t = mult2(x, y);
    *dest = t;
}
