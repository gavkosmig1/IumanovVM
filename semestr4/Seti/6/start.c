#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <math.h>

void check_for_suc(int rc) {
    if (rc != MPI_SUCCESS) {
        MPI_Abort(MPI_COMM_WORLD, rc);
    }
}

int max(int a, int b) {
        if (a > b) {
                return a;
        } else {
                return b;
        }
}

int main(int argc, char *argv[])
{
    int rank, size, rc, k;
    MPI_Status status;

    rc = MPI_Init(&argc, &argv);
    check_for_suc(rc);
    rc = MPI_Comm_size(MPI_COMM_WORLD, &size);
    check_for_suc(rc);
    rc = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    check_for_suc(rc);

    FILE *file;
    char name[8];
    sprintf(name, "0%d.dat", rank + 1);     // оч крутой прием что мне показали
    file = fopen(name, "r");
    if (file == NULL) {
            printf("Process %d otlinivaet ot raboti\n", rank);
            MPI_Finalize();
            return 0;
    }

    int t = 0;
    int dest, from, time;

    while (fscanf(file, "%d", &k) != EOF) {
        if (k == 0)
        {
            t++;
            printf("Process %d zakuril vo vremya %d\n", rank, t);
        } else if (k > 0) {
            t++;
            int rc = MPI_Send(&t, 1, MPI_INT, k-1, 0, MPI_COMM_WORLD);
            check_for_suc(rc);
            printf("Process %d shepchet processu %d vremya %d\n", rank, k-1, t);
        } else {
            int t_recv = 0;
            int rc = MPI_Recv(&t_recv, 1, MPI_INT, -k-1, MPI_ANY_TAG, MPI_COMM_WORLD, NULL);
            check_for_suc(rc);
            t = max(t_recv, t) + 1;
            printf("Process %d uslyshal vremya %d ot processa %d\n", rank, t, -k-1);
        }
    }
    fclose(file);
    MPI_Finalize();
}
