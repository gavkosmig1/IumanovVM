#include <omp.h>
#include <stdio.h>


int main() {
    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                printf("section1, thread_id: %d\n", omp_get_thread_num());
            }
            #pragma omp section
            {
                printf("section2, thread_id: %d\n", omp_get_thread_num());
            }
            #pragma omp section
            {
                printf("section3, thread_id: %d\n", omp_get_thread_num());
            }
            #pragma omp section
            {
                printf("section4, thread_id: %d\n", omp_get_thread_num());
            }
            #pragma omp section
            {
                printf("section5, thread_id: %d\n", omp_get_thread_num());
            }
            #pragma omp section
            {
                printf("section6, thread_id: %d\n", omp_get_thread_num());
            }
        }
        printf("thread_id: %d\n", omp_get_thread_num());
    }
    return 0;
}
