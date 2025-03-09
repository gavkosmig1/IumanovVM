#include <stdio.h>
#include <omp.h>

int main()
{
int count = 0;
#pragma omp parallel
{
    int j;
    for (j=0; j < 1000000; j++)
    {
        #pragma omp critical
        count++;
    }
}
printf("count = %d\n", count);
}
