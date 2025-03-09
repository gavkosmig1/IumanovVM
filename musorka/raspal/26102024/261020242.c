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
    check_for_suc(st);

    int size, rank;

    st = MPI_Comm_size(MPI_COMM_WORLD, &size);
    check_for_suc(st);
    st = MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    srandom(rank+1);
    int N = random()%7 + 1;

    int recvcounts[size];
    int displs[size];
    double buf[N];

    st = MPI_Gather(&N, 1, MPI_INT, recvcounts, 1, MPI_INT, 0, MPI_COMM_WORLD);
    check_for_suc(st);

    if (rank == 0)
    {
        for (int i = 0; i < size; ++i) {printf("%d ", recvcounts[i]);}
        printf("\n");
    }

    int displ = 0;
    for (int i = 0; i < size; ++i)
    {
        displs[i] = displ;
        displ += recvcounts[i];
    }

    if (rank == 0)
    {
        for (int i = 0; i < size; ++i) {printf("%d ", displs[i]);}
        printf("\n");
    }

    for (int i = 0; i < N; ++i) {buf[i] = sqrt(rank);}

    double *res = malloc(sizeof(double)*displ); // Потому что не знаю, какой длинны масив
    

    st = MPI_Gatherv(buf, N, MPI_DOUBLE, res, recvcounts, displs, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    check_for_suc(st);

    if (rank == 0)
    {
        char* filename = "result.txt";
        FILE *fp = fopen(filename, "w");
        if (fp == NULL)
        {
            printf("Can't open the file %s", filename);
            MPI_Abort( MPI_COMM_WORLD , 1);
        }

        for (int i = 0; i < displ; ++i) {printf("%f ", res[i]);}
        printf("\n");

        int last_pos = 0;
        for (int i = 0; i < size; ++i)
        {
            for(int j = 0; j < recvcounts[i]; ++j)
            {
                fprintf(fp, "%f ", res[last_pos]);
                last_pos++;
            }
            fprintf(fp, "\n");
        }
        printf("\n");
    }
    st = MPI_Finalize();
    check_for_suc(st);
    return 0;
}
