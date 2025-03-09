#include <stdio.h>
#include <omp.h>
int main(){
     static int  x0 = 5;
#pragma  omp threadprivate(x0)
#pragma omp parallel 
    { 
          x0 = omp_get_thread_num();
          printf(“Parpart 1 %d  %d\n”, omp_get_thread_num(), x0);
    }
#pragma omp parallel
    { 
          x0 += 1;
          printf(“Parpart 2 %d  %d\n”, omp_get_thread_num(), x0);
    }
    printf(“Seqpart 2 %d  %d\n”, omp_get_thread_num(), x0); 
    return 0;
}
