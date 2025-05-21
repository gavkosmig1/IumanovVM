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
    int rank, size, rc;
    MPI_Status status;

    rc = MPI_Init(&argc, &argv);
    check_for_suc(rc);
    rc = MPI_Comm_size(MPI_COMM_WORLD, &size);
    check_for_suc(rc);
    rc = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    check_for_suc(rc);

    FILE *file;
    char name[8];
    sprintf(name, "v0%d.dat", rank + 1);     // оч крутой прием что мне показали
    file = fopen(name, "r");
    if (file == NULL) {
            printf("Process %d otlinivaet ot raboti\n", rank);
            MPI_Finalize();
            return 0;
    }

    int *vec;
    vec = malloc(size* sizeof(int));
    int *vec_recv;
    vec_recv = malloc(size* sizeof(int));
    for (int i=0; i < size; i++)
    {
        vec[i] = 0;
        vec_recv[i] = 0;
    }
    int i = 0;
    int t = 0;

    while (fscanf(file, "%d", &k) != EOF) {
        if (k == 0)
        {
            t++;
            vec[rank] = t;
            printf("Process %d zakuril vo vremya %d\n[", rank, t);
            for(i = 0; i < size; i++) printf(" %d ", vec[i]);
            printf("]\n");
        } else if (k > 0) {
            t++;
            vec[rank] = t;
            printf("Process %d shepchet processu %d vremya %d\n[", rank, k, t);
            for(i = 0; i < size; i++) printf(" %d ", vec[i]);
            printf("]\n");
            int rc = MPI_Send(vec, size, MPI_INT, k-1, 0, MPI_COMM_WORLD);
            check_for_suc(rc);
        } else {
            t++;
            vec[rank] = t;
            printf("Process %d uslyshal ot processa %d vo vremya %d\n[", rank, abs(k), t);
            for(i = 0; i < size; i++) printf(" %d ", vec[i]);
            printf("]\n");
            int rc = MPI_Recv(vec_recv, size, MPI_INT, abs(k)-1, MPI_ANY_TAG, MPI_COMM_WORLD, NULL);
            check_for_suc(rc);
            for(i = 0; i < size; i++) {
                if (i != rank) vec[i] = max(vec[i], vec_recv[i]);
            }
            printf("Process %d ispravil vremya na\n[", rank);
            for(i = 0; i < size; i++) printf(" %d ", vec[i]);
            printf("]\n");
        }
    }
    free(vec);
    free(vec_recv);
    fclose(file);
    MPI_Finalize();
}
