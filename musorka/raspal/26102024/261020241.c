#include <stdio.h>
#include <mpi.h>

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


    int N = 0;
    int recvcounts[size];
    int displs[size];
    for(int i = 0; i < size; ++i)
    {
        recvcounts[i] = i + 1;
        displs[i] = N * 2;
        N += i + 1;
    }

    N = N * 2 - size;

    int res[N];
    for (int j = 0; j < N; ++j) {res[j] = 0;}

    int buf[rank+1];
    for (int k = 0; k < rank+1; ++k) {buf[k] = rank + 1;}
    
    st = MPI_Gatherv(buf, rank+1, MPI_INT, res, recvcounts, displs, MPI_INT, 0, MPI_COMM_WORLD);
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
        for (int z = 0; z < N; ++z)
        {
            fprintf(fp, "%d ", res[z]);
        }
    }

    st = MPI_Finalize();
    check_for_suc(st);
    return 0;
}
