#include <math.h>
#include <stdlib.h>
#include <omp.h>
#include <stdio.h>


double func(double x)
{
    double y = 4 - x*x;
    if (y < 0)
    {
        return 0.0;
    }
    return pow(y, 0.5);
}


double area(double x, double ink)
{
    return (func(x) + func(x+ink)) * (ink/2.0);
}

int main()
{
    int N;
    char *filename = "N.dat";
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("I can't open %s", filename);
        return -1;
    }
    int n = fscanf(fp, "%d", &N);
    if (n < 1) {
        printf("I can't read %s", filename);
        return -1;
    }

    double Pi = 0;
    int cores = omp_get_num_procs();
    #pragma omp parallel num_threads(cores) reduction(+:Pi) shared(N)
    {
        int N_proc = omp_get_num_threads();
        int thread_id = omp_get_thread_num();
        Pi = 0;
        double cur = 0.0;
        double ink = 2.0 / N;
        int part = N / N_proc;
        cur = thread_id * part * ink * 1.0;

        for (int i = 0; i < part; i++) 
        {
            Pi += area(cur, ink);
            cur += ink;
        }

        if (thread_id == N_proc - 1)
        {
            if (N % N_proc != 0)
            {
                int t = N - part * N_proc;
                for (int i = 0; i < t-1; i++)
                {
                    Pi += area(cur, ink);
                    cur += ink;
                }
            }
        }
        printf("seg %d pi %f\n", thread_id, Pi);
    }
    printf("Pi = %f\n", Pi);
    return 0;
}
// gcc -Og -o exefile pi1.c  -fopenmp -std=gnu99 -lm
// gcc 16112.c -o exefile -fopenmp