#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mpi.h>


void check_for_suc(int st)
{
    if (st != MPI_SUCCESS) {
        printf("Error in check for suc\n");
        MPI_Abort(MPI_COMM_WORLD, st);}
}


int main(int argc, char *argv[])
{
    int st, lev;
    st = MPI_Init_thread(&argc, &argv, MPI_THREAD_SERIALIZED, &lev);
    check_for_suc(st);
	if (lev < MPI_THREAD_SERIALIZED) {MPI_Abort(MPI_COMM_WORLD, -1);}

    int size, rank;

    st = MPI_Comm_size(MPI_COMM_WORLD, &size);
    check_for_suc(st);
    st = MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double *u, *unew;
    double eps = 1.e-6;
    double h, tau;

    int N;
    int i;
    int count = 0;

    FILE *ff; // output file

    if (argc != 2)
    {
        printf("Usage: exefile npoints\n");
        MPI_Abort(MPI_COMM_WORLD, -1);
    }

    N = atoi(argv[1]);
    if (N == 0) {
        printf("Set N to 1000\n");
        N =1000;
    } else {
        printf("Set N to %d\n", N);
    }

    // alloc mem
    if((u = malloc((N+1)*sizeof(double))) == NULL)
    {
        printf("Can't allocate memory for u\n");
        MPI_Abort(MPI_COMM_WORLD, -1);
    }

    if((unew = malloc((N+1)*sizeof(double))) == NULL)
    {
        printf("Can't allocate memory for unew\n");
        free(u);
        MPI_Abort(MPI_COMM_WORLD, -1);
    }

    // begin & bound values
    for (i=1; i<N; i++) {u[i] = 0;}
    
    // edge values
    unew[0] = u[0] = 1.0;
    unew[N] = u[N] = 0;

	h = 1.0 / N;
    tau = 0.5 * (h*h);

	int length = (N-1)/size;

	int beg, end;
	if (rank != (size - 1))
    {
		beg = rank*length + 1;
		end = rank*length + length;
	} else
    {
		beg = 1 + rank*length;
		end = N - 1;
	}

    double globalmaxdelta = 0.0;
	int N_proc = 3; // omp_get_num_procs();
    double maxdelta = 0.0;
    double* maxmas = malloc((size)*sizeof(double));
    for (int i = 0; i < N_proc; ++i) {maxmas[i] = 0.0;}

    #pragma omp parallel num_threads(N_proc) shared(count, N, maxmas, u, unew, eps, h, tau, maxdelta, N_proc, globalmaxdelta, st, rank, size, beg, end)
    while (1)
    {
        int thread_id = omp_get_thread_num();
        
        #pragma omp for
        for (int i = beg; i <= end; ++i)
        {
            unew[i] = u[i] + (tau / (h*h)) * (u[i-1] - 2 * u[i] + u[i+1]);
        }

        maxmas[thread_id] = 0.0;
        maxdelta = 0.0;
        globalmaxdelta = 0.0;
        double delta = 0.0;

        #pragma omp for
        for (int i = beg; i <= end; ++i)
        {
            delta = fabs(unew[i] - u[i]);
            if (delta > maxmas[thread_id]) {maxmas[thread_id] = delta;}
        }
        
        #pragma omp single
        {
            count++;
            for (i = 0; i < N_proc; ++i)
            if (maxmas[i] > maxdelta) {maxdelta = maxmas[i];}
            st = MPI_Reduce(&maxdelta, &globalmaxdelta, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
            check_for_suc(st);
            st = MPI_Bcast(&globalmaxdelta, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
            check_for_suc(st);
        }

        if (globalmaxdelta < eps) {break;}

        #pragma omp single
        if (size != 1)
        {
            if (rank == 0)
            {
                st = MPI_Send(&unew[end], 1, MPI_DOUBLE, rank+1, rank, MPI_COMM_WORLD);
                check_for_suc(st);

                st = MPI_Recv(&unew[end + 1], 1, MPI_DOUBLE, rank+1, rank+1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                check_for_suc(st);
            }
            else if (rank < size - 1)
            {
                st = MPI_Send(&unew[beg], 1, MPI_DOUBLE, rank-1, rank, MPI_COMM_WORLD);
                check_for_suc(st);
                st = MPI_Send(&unew[end], 1, MPI_DOUBLE, rank+1, rank, MPI_COMM_WORLD);
                check_for_suc(st);

                st = MPI_Recv(&unew[beg - 1], 1, MPI_DOUBLE, rank-1, rank-1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                check_for_suc(st);
                st = MPI_Recv(&unew[end + 1], 1, MPI_DOUBLE, rank+1, rank+1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                check_for_suc(st);
            }
            else
            {
                st = MPI_Send(&unew[beg], 1, MPI_DOUBLE, rank-1, rank, MPI_COMM_WORLD);
                check_for_suc(st);
                st = MPI_Recv(&unew[beg - 1], 1, MPI_DOUBLE, rank-1, rank-1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                check_for_suc(st);
            }
        }
        #pragma omp for
        for (i = beg - 1; i <= end + 1; ++i) {u[i] = unew[i];}
    }

    int* recvcounts = malloc((size) * sizeof(int));
   	int* displs = malloc((size) * sizeof(int));
    double* result  = malloc((N + 1) * sizeof(double));
	int No  = end - beg + 1;


	st = MPI_Gather(&beg, 1, MPI_INT, displs, 1, MPI_INT, 0, MPI_COMM_WORLD);
	check_for_suc(st);
	st = MPI_Gather(&No, 1, MPI_INT, recvcounts, 1, MPI_INT, 0, MPI_COMM_WORLD);
	check_for_suc(st);
	st = MPI_Gatherv(unew + beg, No, MPI_DOUBLE, result, recvcounts, displs, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	check_for_suc(st);

	result[0] = 1.0;
	result[N] = 0.0;

	if (rank == 0)
    {
		printf("%d steps\n", count);
    		if ((ff = fopen("parres", "w+")) == NULL){
       			printf("Can't open file\n");
                free(result);
                free(u);
                free(unew);
       			MPI_Abort(MPI_COMM_WORLD, -1);
    		}
    
    		for (i=0; i < N+1; i++) fprintf(ff, "%f\n", result[i]);
       
    		fclose(ff);
	}

    free(result);
	free(u);
    free(unew);


	st = MPI_Finalize();
	check_for_suc(st);
	return 0;  
}      
