#include <stdio.h>
int main()
{
	printf("Sequential part 1\n");
    int a = omp_get_num_procs();
    printf("My proc is %d times cooler than yours", a);
	#pragma omp parallel num_threads(6)
	{
        int id = omp_get_thread_num();
		printf("Hello OMP my name is %d\n", id);
    }
	printf("Sequential part 2\n");
    int b = omp_get_num_threads();
    int id = omp_get_thread_num();
    printf("My name is %d and my family has %d threads", id, b);
	return 0;
}