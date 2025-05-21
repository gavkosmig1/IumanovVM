#include <stdlib.h>
#include <mpi.h>
#include <stdio.h>
#include <math.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

void check_for_suc(int rc) {
    if (rc != MPI_SUCCESS) {
        MPI_Abort(MPI_COMM_WORLD, rc);
    }
}

int sigflag = 1;

void handler(int nsig)
{
	sigflag = 0;
}

int main(int argc, char* argv[])
{
	int rank, size, rc;
	MPI_Status status;

	rc = MPI_Init(&argc, &argv);
	check_for_suc(rc);
	rc = MPI_Comm_size(MPI_COMM_WORLD, &size);
	check_for_suc(rc);
	rc = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	check_for_suc(rc);

    srandom(rank);
    signal(SIGALRM, handler);
	int i = 0;
	int flag = 0;
    int msg = 0;
    int REPEAT = 3;

    if (rank == 0) {rc = MPI_Send(&msg, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);}
    while (i != REPEAT)
    {
        printf("Process %d zhdet marker\n", rank);
        rc = MPI_Recv(&msg, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
        printf("Process %d poluchil marker\n", rank);

        sleep(rand() % 2 + 1);
        printf("Process %d vyspalsya\n", rank);

        rc = MPI_Send(&msg, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);

        sigflag = 1;
        alarm(rand() % 5 + 1);
        while (sigflag)
        {
            rc = MPI_Iprobe(MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &flag, &status);
            if (flag)
            {
                rc = MPI_Recv(&msg, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
                rc = MPI_Send(&msg, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
            }
        }
        i++;
    }
    if (rank == 0)
    {
        printf("Process %d objavlyaet konec sveta!!!\n");
        rc = MPI_Send(&msg, 1, MPI_INT, (rank + 1) % size, 1, MPI_COMM_WORLD);
    }

    sigflag = 1;
    int Z = 0;
    while (sigflag)
    {
        rc = MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &flag, &status);
        if (flag)
        {
            if (status.MPI_TAG == 0)
            {
                rc = MPI_Recv(&msg, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
                rc = MPI_Send(&msg, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
            }
            if (status.MPI_TAG == 1)
            {
                rc = MPI_Recv(&msg, 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);
                printf("Process %d uslyshal o konce sveta!!\n", rank);
                rc = MPI_Send(&msg, 1, MPI_INT, (rank + 1) % size, 1, MPI_COMM_WORLD);
                printf("Process %d rasskazal o konce sveta!!\n", rank);
                if (Z == 1){break;}
                Z++;
            }
        }
    }
    rc = MPI_Finalize();
    check_for_suc(rc);
    return 0;
}