#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mpi.h>


void check_for_suc(int st)
{
    if (st != MPI_SUCCESS) {MPI_Abort(MPI_COMM_WORLD, st);}
}


int main(int argc, char *argv[])
{
    int st;
    st = MPI_Init(&argc, &argv);
    check_for_suc(st);

    int size, rank;

    st = MPI_Comm_size(MPI_COMM_WORLD, &size);
    check_for_suc(st);
    st = MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double *u, *unew, delta, maxdelta;
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

    N = atoi(argv[1]); // save N
    if (N == 0)
    {
        printf("Set N to 1000\n");
        N = 1000;
    }
    else 
    {
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

    double globalmaxdelta;
    while (1)
    {
        for (int i = beg; i <= end; ++i)
        {
            unew[i] = u[i] + (tau / (h*h)) * (u[i-1] - 2 * u[i] + u[i+1]);
        }

        maxdelta = 0.0;
        globalmaxdelta = 0.0;

        for (int i = beg; i <= end; ++i)
        {
            delta = fabs(unew[i] - u[i]);
            if (delta > maxdelta) maxdelta = delta;
        }
        
        st = MPI_Reduce(&maxdelta, &globalmaxdelta, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
        check_for_suc(st);
        st = MPI_Bcast(&globalmaxdelta, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        check_for_suc(st);

        if (globalmaxdelta < eps) {break;}

        count++;

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
        for (i = beg - 1; i <= end + 1; ++i) {u[i] = unew[i];}
    }

    int* recvcounts = malloc((size) * sizeof(int));
   	int* displs = malloc((size) * sizeof(int));
    double* result  = malloc((N + 1) * sizeof(double));
	int N  = end - beg + 1;


	st = MPI_Gather(&beg, 1, MPI_INT, displs, 1, MPI_INT, 0, MPI_COMM_WORLD);
	check_for_suc(st);
	st = MPI_Gather(&N, 1, MPI_INT, recvcounts, 1, MPI_INT, 0, MPI_COMM_WORLD);
	check_for_suc(st);
	st = MPI_Gatherv(unew + beg, N, MPI_DOUBLE, result, recvcounts, displs, MPI_DOUBLE, 0, MPI_COMM_WORLD);
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
