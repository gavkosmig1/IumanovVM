#include <omp.h>
#include <stdio.h>


int main()
{
    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                printf("section 1, id = %d\n", omp_get_thread_num());
            }
            #pragma omp section
            {
                printf("section 2, id = %d\n", omp_get_thread_num());
            }
            #pragma omp section
            {
                printf("section 3, id = %d\n", omp_get_thread_num());
            }
            #pragma omp section
            {
                printf("section 4, id = %d\n", omp_get_thread_num());
            }
            #pragma omp section
            {
                printf("section 5, id = %d\n", omp_get_thread_num());
            }
            #pragma omp section
            {
                printf("section 6,, id = = %d\n", omp_get_thread_num());
            }
        }
        printf("thread_id: %d\n", omp_get_thread_num());
    }
    return 0;
}
