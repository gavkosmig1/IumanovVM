#include <iostream>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int st;
    st = MPI_Init(&argc, &argv);
    if (st != MPI_SUCCESS) {
        std::cout << "Error starting MPI program. Terminating. \n";
        
        MPI_Abort(MPI_COMM_WORLD, 0);
    }
    std::cout << "Hello gavkosmig";
    MPI_Finalize();
    return 0;
}