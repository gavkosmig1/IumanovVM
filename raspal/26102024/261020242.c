#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <math.h>

void check_for_suc(int ec)
{
    if (ec != MPI_SUCCESS)
    {
        MPI_Abort(MPI_COMM_WORLD, ec);
    }
}


int main(int argc, char** argv)
{
    int st;
    st = MPI_Init(&argc, &argv);
    check_for_success(st);

    int size, rank;

    st = MPI_Comm_size(MPI_COMM_WORLD, &size);
    check_for_success(st);
    st = MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    srandom(rank+1);
    int N = random()%7 + 1;

    int recvcounts[size];
    int displs[size];
    double buf[N];

    st = MPI_Gather(&N, 1, MPI_INT, recvcounts, 1, MPI_INT, 0, MPI_COMM_WORLD);
    check_for_success(st);

    if (rank == 0) {
            for (int i = 0; i < size; ++i) {
                    printf("%d ", recvcounts[i]);
            }
            printf("\n");
    }

    int dis = 0;
    for (int i = 0; i < size; ++i) {
            displs[i] = dis;
            dis += recvcounts[i];
    }

    double *res = malloc(sizeof(double)*dis);
    if (rank == 0) {
            for (int i = 0; i < size; ++i) {
                    printf("%d ", displs[i]);
            }
            printf("\n");
    }
    for(int i = 0; i < N; ++i) {
            buf[i] = sqrt(rank);
    }

    st = MPI_Gatherv(buf, N, MPI_DOUBLE, res, recvcounts, displs, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    check_for_success(st);

    if (rank == 0) {
            const char* filename = "output.txt";
            FILE* file = fopen(filename, "w");
            if (file == NULL) {
                    printf("Error opening file.\n");
                    MPI_Abort(MPI_COMM_WORLD, -1);
            }
            for (int i = 0; i < dis; ++i) {
                    printf("%f ", res[i]);
            }
            printf("\n");
            int last_pos = 0;
            for (int i = 0; i < size; ++i) {
                    // last_pos += displs[i];
                    for(int j = 0; j < recvcounts[i]; ++j) {
                            fprintf(file, "%f ", res[last_pos]);
                            last_pos++;
                    }
                    fprintf(file, "\n");
            }
            printf("\n");
    }
    st = MPI_Finalize();
    check_for_success(st);
    return 0;
}
