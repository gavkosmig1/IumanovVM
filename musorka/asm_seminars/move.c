#include <inttypes.h>

int64_t exchange (int64_t *xp, int64_t y)
{
    int64_t x = *xp;
    *xp = y;
    return x;
}