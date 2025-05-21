#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <math.h>
#include <unistd.h>
#include <signal.h>

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
    
    int RANK = 1;
    
    srandom(rank);
    int kill = random();
    if (kill % 2 == 1 && rank != RANK)
    {
        printf("Process %d umer lol\n", rank);
        MPI_Finalize();
        return 0;
    }
    
    int TIMEOUT = 5;
    
    signal (SIGALRM, handler);	
    
    if(rank == RANK)
    {
        int i = 0;
        int msg = 0;
        int flag = 0;
        
        printf("Process %d nachal golosovanie\n", rank);
        for(i = rank + 1; i < size; i++) 
        {
            rc = MPI_Send(&rank, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            printf("Process %d rasskazal o golosovanii %d\n",rank, i);
        }
        
        alarm(TIMEOUT);
        while(sigflag)
        {
            rc = MPI_Iprobe (MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &flag, &status);
            if (flag) {
                if (status.MPI_TAG == 1) { 
                    printf("Process %d uslyshal OK ot %d\n", rank, status.MPI_SOURCE);
                    rc = MPI_Recv(&msg, 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);
                    alarm(0);
                    rc = MPI_Recv(&msg, 1, MPI_INT, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &status);
                    printf("Process %d znaet o lidere %d\n", rank, status.MPI_SOURCE);
                    MPI_Finalize();
                    return 0;
                }
                if (status.MPI_TAG == 0) {
                    printf("Process %d dominiruet nad %d\n", rank, status.MPI_SOURCE);
                    rc = MPI_Send(&msg, 1, MPI_INT, status.MPI_SOURCE, 1, MPI_COMM_WORLD);
                }
            }
        }
        printf("Process %d izbran liderom\n", rank);
        for (i = 0; i < size && rank != RANK; i++) {
            rc = MPI_Send(&rank, 1, MPI_INT, i, 2, MPI_COMM_WORLD); }
        MPI_Finalize();
        return 0;
    }
    else
    {
        int msg = 1;
        int i = 0;
        int flag = 0;
        
        rc = MPI_Recv(&msg, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        if (status.MPI_TAG == 2)
        {
            printf("Process %d znaet o lidere %d\n", rank, status.MPI_SOURCE);
            MPI_Finalize();
            return 0;
        }
        printf("Process %d dominiruet nad %d\n", rank, status.MPI_SOURCE);
        rc = MPI_Send(&msg, 1, MPI_INT, status.MPI_SOURCE, 1, MPI_COMM_WORLD);
        printf("Process %d nachal golosovanie\n", rank);
        for (i = rank + 1; i < size; i++)
        {
            rc = MPI_Send(&rank, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            printf("Process %d rasskazal o golosovanii %d\n",rank, i);	
        }
        alarm(TIMEOUT);
        while(sigflag)
        {
            rc = MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &flag, &status);
            if (flag)
            {
                rc = MPI_Recv(&msg, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                if (status.MPI_TAG == 0)
                {
                    printf("Process %d otvechaet na golosonaie %d\n", rank, status.MPI_SOURCE);						
                    rc = MPI_Send(&msg, 1, MPI_INT, status.MPI_SOURCE, 1, MPI_COMM_WORLD);
                }
                if (status.MPI_TAG == 1)
                {
                    printf("Process %d uslyshal OK ot %d\n", rank, status.MPI_SOURCE);
                    alarm(0);
                }
                if (status.MPI_TAG == 2)
                {
                    printf("Process %d znaet o lidere %d\n", rank, status.MPI_SOURCE);
                    MPI_Finalize();
                    return 0;
                }
            }
        }
        printf("Process %d izbran liderom\n", rank);
        for (i = 0; i < size && rank != RANK; i++) {
            rc = MPI_Send(&rank, 1, MPI_INT, i, 2, MPI_COMM_WORLD); }
        rc = MPI_Finalize();
        return 0;
    }
      
    MPI_Finalize();
    check_for_suc(rc);
    return 0;  
}

// 0 = golosovanie
// 1 = ok
// 2 = winner