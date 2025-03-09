#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mpi.h>
#include <omp.h>


void check_for_success(int rc) {
        if (rc != MPI_SUCCESS) {
                printf("Errors with mpi program. Terminating\n");
                MPI_Abort(MPI_COMM_WORLD, rc);
        }
}


int main(int argc, char *argv[]){
        int rc;
	int prov;
        // rc = MPI_Init(&argc, &argv);
        rc = MPI_Init_thread(&argc, &argv, MPI_THREAD_SERIALIZED, &prov);
	check_for_success(rc);
	if (prov < MPI_THREAD_SERIALIZED) {
		MPI_Abort(MPI_COMM_WORLD, -1);
	}
        int N_proc, rank;
        rc = MPI_Comm_size(MPI_COMM_WORLD, &N_proc);
        check_for_success(rc);
    	rc = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
 
    	double *u, *unew;// , delta, maxdelta;
    	double eps=1.e-6;
    	double h, tau;
    
    	int N;
    	int i;
    	int count = 0;
    
    	FILE *ff;
    
    	if(argc !=2 ){
		printf("Usage: exefile npoints\n");
		MPI_Abort(MPI_COMM_WORLD, -1);
    	}
    
    	N = atoi(argv[1]);
    	if (N == 0) {
		if (rank == 0) {
			printf("Set N to 1000\n");
		}
		N =1000;
    	} else {
		if (rank == 0) {
			printf("Set N to %d\n", N);
    		}
	}
    
    	if((u = malloc((N+1)*sizeof(double))) == NULL){
		printf("Can't allocate memory for u\n");
		MPI_Abort(MPI_COMM_WORLD, -1);
    	}

    	if((unew = malloc((N+1)*sizeof(double))) == NULL){
		printf("Can't allocate memory for unew\n");
		free(u);
		MPI_Abort(MPI_COMM_WORLD, -1);
    	}
    
    	for(i=1; i<N; i++){
		u[i] = 0;
    	}
    	unew[0] = 1.0;
	u[0] = 1.0;
    	unew[N] = 0;
	u[N] = 0;

	h = 1.0/N;
    	tau = 0.5*(h*h);

	int length = (N-1)/N_proc;

	int jbeg, jend;
	if (rank != N_proc - 1) {
		jbeg = 1 + rank*length;
		jend = (rank+1)*length;
	} else {
		jbeg = 1 + rank*length;
		jend = N-1;
	}
	
	double globalmaxdelta = 0;
	int N_thr_proc = 3; // omp_get_num_procs();
    	double maxdelta = 0.0;
    	double* maxmas = malloc((N_proc)*sizeof(double));
    	for(int i = 0; i < N_thr_proc; ++i) {
        	maxmas[i] = 0.0;
    	}
	
	#pragma omp parallel num_threads(N_thr_proc) shared(count, N, maxmas, u, unew, eps, h, tau, maxdelta, N_thr_proc, globalmaxdelta, rc, rank, N_proc, jbeg, jend)
	{
    		while(1){
                        int thread_id = omp_get_thread_num();

			#pragma omp for
				for (int i = jbeg; i <= jend; ++i) {
					unew[i] = u[i] + (tau/(h*h)) * (u[i-1] - 2*u[i] + u[i+1]);
				}
			maxmas[thread_id] = 0.0;
        		maxdelta = 0.0;
			double delta = 0.0;
			globalmaxdelta = 0.0;
			#pragma omp for
				for (int i = jbeg; i <= jend; ++i) {
					delta = fabs(unew[i] - u[i]);
					if (delta > /*maxdelta*/ maxmas[thread_id]) maxmas[thread_id] = delta; // maxdelta = delta;
				}

			#pragma omp single
                        {
                                count++;
                                for(i = 0; i < N_thr_proc; ++i) {
                                        if (maxmas[i] > maxdelta) {
                                                maxdelta = maxmas[i];
                                        }
                                }
				
				rc = MPI_Reduce(&maxdelta, &globalmaxdelta, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
                        	check_for_success(rc);
                        	rc = MPI_Bcast(&globalmaxdelta, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
                        	check_for_success(rc);

                        }

			/*
			rc = MPI_Reduce(&maxdelta, &globalmaxdelta, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
			check_for_success(rc);
			rc = MPI_Bcast(&globalmaxdelta, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
			check_for_success(rc);
			*/

			if (rank == 0 && count < 100) {
				#pragma omp single
				{
					printf("globalmaxdelta = %d\n", globalmaxdelta);
				}
			}
			if (globalmaxdelta < eps) {
				break;
			}
        		// count++;
        		#pragma omp single
			{
				if (N_proc != 1) {
					if (rank == 0) {
						rc = MPI_Send(&unew[jend], 1, MPI_DOUBLE, rank+1, rank, MPI_COMM_WORLD);
						check_for_success(rc);
						rc = MPI_Recv(&unew[jend+1], 1, MPI_DOUBLE, rank+1, rank+1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
						check_for_success(rc);
					} else if (rank < N_proc - 1) {
						rc = MPI_Send(&unew[jbeg], 1, MPI_DOUBLE, rank-1, rank, MPI_COMM_WORLD);
						check_for_success(rc);
						rc = MPI_Send(&unew[jend], 1, MPI_DOUBLE, rank+1, rank, MPI_COMM_WORLD);
						check_for_success(rc);
						rc = MPI_Recv(&unew[jbeg - 1], 1, MPI_DOUBLE, rank-1, rank-1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
						check_for_success(rc);
						rc = MPI_Recv(&unew[jend+1], 1, MPI_DOUBLE, rank+1, rank+1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
						check_for_success(rc);
					} else {
						rc = MPI_Send(&unew[jbeg], 1, MPI_DOUBLE, rank-1, rank, MPI_COMM_WORLD);
						check_for_success(rc);
						rc = MPI_Recv(&unew[jbeg - 1], 1, MPI_DOUBLE, rank-1, rank-1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
						check_for_success(rc);
					}
				}
			}
			#pragma omp for
				for(i = jbeg-1; i <= jend+1; ++i) {
        	        	        u[i] = unew[i];;
                		}
    		}
	}
   	int* displs = malloc((N_proc)*sizeof(int));
        int* counts = malloc((N_proc)*sizeof(int));
	int item_count  = jend - jbeg + 1;
	double* final_mas  = malloc((N+1)*sizeof(double));

	rc = MPI_Gather(&jbeg, 1, MPI_INT, displs, 1, MPI_INT, 0, MPI_COMM_WORLD);
	check_for_success(rc);
	rc = MPI_Gather(&item_count, 1, MPI_INT, counts, 1, MPI_INT, 0, MPI_COMM_WORLD);
	check_for_success(rc);
	rc = MPI_Gatherv(unew+jbeg, item_count, MPI_DOUBLE, final_mas, counts, displs, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	check_for_success(rc);

	final_mas[0] = 1.0;
	final_mas[N] = 0.0;

	if (rank == 0) {
		printf("%d steps\n", count);
    		if ((ff = fopen("combinedres", "w+")) == NULL){
       			printf("Can't open file\n"); free(u); free(unew); free(final_mas);
       			MPI_Abort(MPI_COMM_WORLD, -1);
    		}
    
    		for(i=0; i<N+1; i++)
       		fprintf(ff, "%f\n", final_mas[i]);
       
    		fclose(ff);
	}
	free(u); free(unew); free(final_mas);
	rc = MPI_Finalize();
	check_for_success(rc);
	return 0;  
}      
