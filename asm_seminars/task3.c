#include <inttypes.h>

typedef int src_t;
typedef char dest_t;

void copy(src_t *sp, dest_t *dp)
{
    *dp = (dest_t)*sp;
}