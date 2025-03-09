#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

int main(int argc, char *argv[]){

    double *u, *unew; // , delta, maxdelta;
    double eps=1.e-6;
    double h, tau;

    int N;
    int i;
    int count = 0;

    FILE *ff;

    if(argc !=2 ){
        printf("Usage: exefile npoints\n");
        exit(-1);
    }

    N = atoi(argv[1]);
    if (N == 0) {
        printf("Set N to 1000\n");
        N =1000;
    } else {
        printf("Set N to %d\n", N);
    }

    if((u = malloc((N+1)*sizeof(double))) == NULL){
        printf("Can't allocate memory for u\n");
        exit(-1);
    }

    if((unew = malloc((N+1)*sizeof(double))) == NULL){
        printf("Can't allocate memory for unew\n");
        free(u);
        exit(-1);
    }

    // begin & bound values

    for(i=1; i<N; i++){
        u[i] = 0;
    }

    unew[0] = u[0] = 1.0;
    unew[N] = u[N] = 0;

    h = 1.0/N;
    tau = 0.5*(h*h);

    int N_proc = omp_get_num_procs();
    double maxdelta = 0.0;
    double* maxmas = malloc((N_proc)*sizeof(double));
    for(int i = 0; i < N_proc; ++i) {
        maxmas[i] = 0.0;
    }
        #pragma omp parallel num_threads(N_proc) shared(count, N, maxmas, u, unew, eps, h, tau, maxdelta, N_proc)
        {
            while(1){
                int thread_id = omp_get_thread_num();

                #pragma omp for
                    for (int i=1; i<N; i++) {unew[i] = u[i]+(tau/(h*h))*(u[i-1]-2*u[i]+u[i+1]);}

                // double maxdelta = 0.0;
                maxmas[thread_id] = 0.0;
                maxdelta = 0.0;
                double delta = 0.0;
                #pragma omp for
                    for (i=1; i<N; i++){
                        delta = fabs(unew[i]-u[i]);
                        if (delta >  maxmas[omp_get_thread_num()]) maxmas[omp_get_thread_num()] = delta;
                    }

                #pragma omp single
                {
                    count++;
                    for (int i = 0; i < N_proc; ++i) {
                        if (maxmas[i] > maxdelta) maxdelta = maxmas[i];
                    }
                }

                if (maxdelta < eps) break;

                #pragma omp for
                    for (int i = 1; i < N; i++) {u[i] = unew[i];;}
            }
        }

    printf("%d steps\n",count);
    if ((ff = fopen("paral", "w+")) == NULL){
       printf("Can't open file\n"); free(u); free(unew);
       exit(-1);
    }

    for(i=0; i<N+1; i++)
    fprintf(ff, "%f\n", unew[i]);

    fclose(ff); free(u); free(unew);
    free(maxmas);
    return 0;
}
