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
    if (kill % 2 == 0 && rank != RANK)
    {
        printf("Process %d umer lol\n", rank);
        MPI_Finalize();
        return 0;
    }
    
    int* list;	
    list = (int*)malloc((size) * sizeof(int));
    for (int i = 0; i < size; i++) {list[i] = 0;}

    int TIMEOUT = 2;
    int winner;
    
    signal (SIGALRM, handler);	
    
    if(rank == RANK)
    {
        int i = 0;
        int flag = 0;
        list[rank] = 1;
        int k;

        printf("Process %d nachal golosovanie\n", rank);
        for (i = (rank + 1) % size; i !=rank; i = (i+1) % size) 
        {
            rc = MPI_Send(&rank, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            printf("Process %d rasskazal o golosovanii %d\n", rank, i);

            sigflag = 1;
            alarm(TIMEOUT);
            while(sigflag)
            {
                rc = MPI_Iprobe (i, 1, MPI_COMM_WORLD, &flag, &status);
                if (flag) {
                    rc = MPI_Recv(list, size, MPI_INT, i, 1, MPI_COMM_WORLD, &status);
		            printf("Process %d peredaet estafetu %d\n", rank, i);
		            alarm(0);
		            break;
                }
            }
            if (flag) break;
            printf("Process %d nichego ne uslyshal ot %d\n", rank, i);
        }

	    rc = MPI_Recv(list, size, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
	    printf("Process %d objavlyaet o zavershenii golosovaniya!!!\n", rank);
    
	    rc = MPI_Send(list, size, MPI_INT, status.MPI_SOURCE, 1, MPI_COMM_WORLD);

	    if (list[rank] == 1) 
	    {
            // зумер изобрёл max
	        for (k = 0; k < size; k++)
                if (list[k] == 1)
                    winner = i;
                    printf("%d", winner);
				
	        printf("Process %d schitaet liderom %d\n", rank, winner);
	        rc = MPI_Send(&winner, 1, MPI_INT, i, 2, MPI_COMM_WORLD);

	    }
	    rc = MPI_Recv(&winner, 1, MPI_INT, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &status);

        printf("Process %d izbran liderom\n", rank);
        MPI_Finalize();
        free(list);
        return 0;
    }
    else
    {
        int i = 0;
        int flag = 0;
        
        rc = MPI_Recv(list, size, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);	
        printf("Process %d poluchil list i govorit ok processu %d\n", rank, status.MPI_SOURCE);

        rc = MPI_Send(list, size, MPI_INT, status.MPI_SOURCE, 1, MPI_COMM_WORLD);
        for (i = (rank + 1) % size; i != size; i = (i + 1) % size)
        {
            rc = MPI_Send(list, size, MPI_INT, i, 0, MPI_COMM_WORLD);
            printf("Process %d rasskazal o golosovanii %d\n",rank, i);

            sigflag = 1;
            alarm(TIMEOUT);
            while(sigflag)
            {
                rc = MPI_Iprobe(i, 1, MPI_COMM_WORLD, &flag, &status);
                if (flag)
                {
                    rc = MPI_Recv(list, size, MPI_INT, i, 1, MPI_COMM_WORLD, &status);
                    printf("Process %d peredaet estafetu %d\n", rank, i);
                    alarm(0);
                }
            }
            if (flag) break;
            printf("Process %d nichego ne uslyshal ot %d\n", rank, i);
        }

        rc = MPI_Recv(&winner, 1, MPI_INT, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &status);
        rc = MPI_Send(&winner, 1, MPI_INT, i, 2, MPI_COMM_WORLD);
	    
        printf("Process %d schitaet liderom %d\n", rank, winner);
        MPI_Finalize();
        free(list);
        return 0;
    }
      
    MPI_Finalize();
    check_for_suc(rc);
    return 0;  
}

// 0 = golosovanie
// 1 = ok
// 2 = winner