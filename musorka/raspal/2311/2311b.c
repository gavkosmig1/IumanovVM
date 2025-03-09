#include <stdio.h>
#include <omp.h>

int main()
{
int meat = 5;

#pragma omp parallel num_threads(4)
{
    while (meat > 0)
    {
        
    }
}
}
