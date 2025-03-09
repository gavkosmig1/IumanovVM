#include <stdio.h>
#include <omp.h>

int main()
{
    #pragma omp parallel num_threads(4)
    { 
        #pragma omp single
        {
            printf("Single 1, id = %d\n", omp_get_thread_num());
        }
        printf("id = %d\n", omp_get_thread_num());
        #pragma omp single
        {
            printf("Single 2, id = %d\n", omp_get_thread_num());
        }
    }
    return 0;
}
