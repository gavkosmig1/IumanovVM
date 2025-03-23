#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <math.h>


void check_for_suc(int rc) {
    if (rc != MPI_SUCCESS) {
        MPI_Abort(MPI_COMM_WORLD, rc);
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


    if(rank == 0)
    {
        srandom(rank);
        int T = random() % 51;
        int i = 1;

        while (i != size)
        {
            rc = MPI_Send(&T, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            check_for_suc(rc);
            printf("Server otpravil klientu %d vremya %d\n", i, T);
            ++i;
        }
        i = 1;
        
        int delta;
        int S = 0;
        int *raz;
        raz = malloc(size* sizeof(int));
        MPI_Status status;

        while (i != size)
        {
            rc = MPI_Recv(&delta, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            check_for_suc(rc);
            printf("Server uslyshal raznitsu %d ot klienta %d\n", delta, status.MPI_SOURCE);

            S += delta;
            raz[status.MPI_SOURCE] = delta;
            
            i++;
        }
        i = 1;

        int mean = (int) ceil(((double) S) / size);
        int izm = 0;

        while (i != size)
        {
            izm = mean - raz[i];
            rc = MPI_Send(&izm, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            check_for_suc(rc);
            printf("Prikazano klientu %d izmenit vremya na %d\n", i, izm);
            i++;
        }
        printf("Server izmenil vremya: bylo %d stalo %d\n", T, T + mean);
        T += mean;
        free(raz);
    }
    else {
        srandom(rank);
        int T1 = random() % 51;

        int Tmir = 0;
        rc = MPI_Recv(&Tmir, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, NULL);
        check_for_suc(rc);
        printf("UMT %d: Klient %d uslyshal vremya %d\n", T1, rank, Tmir);

        int Delta = T1 - Tmir;
        rc = MPI_Send(&Delta, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        check_for_suc(rc);
        printf("UMT %d: klient %d otpravil raznitsu %d\n", T1, rank, Delta);

        int Izm = 0;
        rc = MPI_Recv(&Izm, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, NULL);
        check_for_suc(rc);
        T1 += Izm;

        printf("Klient %d ustanovil vremya na %d izmeniv staroe na %d\n", rank, T1, Izm);
    }


    MPI_Finalize();
}
