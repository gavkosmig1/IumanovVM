#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <math.h>

void check_for_success(int rc) {
        if (rc != MPI_SUCCESS) {
                printf("Errors with mpi program. Terminating\n");
                MPI_Abort(MPI_COMM_WORLD, rc);
        }
}


int main(int argc, char** argv) {
        int rc;
        rc = MPI_Init(&argc, &argv);
        check_for_success(rc);
        int N_proc, rank;
        rc = MPI_Comm_size(MPI_COMM_WORLD, &N_proc);
        check_for_success(rc);
        rc = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        srandom(rank+1);
        int recvcounts[N_proc];
        int displs[N_proc];
        int length = random()%7 + 1;
        double local_mas[length];
        rc = MPI_Gather(&length, 1, MPI_INT, recvcounts, 1, MPI_INT, 0, MPI_COMM_WORLD);
        check_for_success(rc);
        if (rank == 0) {
                for (int i = 0; i < N_proc; ++i) {
                        printf("%d ", recvcounts[i]);
                }
                printf("\n");
        }
        int dis = 0;
        for (int i = 0; i < N_proc; ++i) {
                displs[i] = dis;
                dis += recvcounts[i];
        }
        double *final_mas = malloc(sizeof(double)*dis);
        if (rank == 0) {
                for (int i = 0; i < N_proc; ++i) {
                        printf("%d ", displs[i]);
                }
                printf("\n");
        }
        for(int i = 0; i < length; ++i) {
                local_mas[i] = sqrt(rank);
        }
        }
        rc = MPI_Gatherv(local_mas, length, MPI_DOUBLE, final_mas, recvcounts, displs, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        check_for_success(rc);
        if (rank == 0) {
                const char* filename = "output.txt";
                FILE* file = fopen(filename, "w");
                if (file == NULL) {
                        printf("Error opening file.\n");
                        MPI_Abort(MPI_COMM_WORLD, -1);
                }
                for (int i = 0; i < dis; ++i) {
                        printf("%f ", final_mas[i]);
                }
                printf("\n");
                int last_pos = 0;
                for (int i = 0; i < N_proc; ++i) {
                        // last_pos += displs[i];
                        for(int j = 0; j < recvcounts[i]; ++j) {
                                fprintf(file, "%f ", final_mas[last_pos]);
                                last_pos++;
                        }
                        fprintf(file, "\n");
                }
                printf("\n");
        }
        rc = MPI_Finalize();
        check_for_success(rc);
        return 0;
}
