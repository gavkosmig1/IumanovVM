#include <stdlib.h>
#include <cstdio>
#include <mpi.h>
#include <cmath>
#include <iostream>

void check_for_suc(int rc) {
    if (rc != MPI_SUCCESS) {
        MPI_Abort(MPI_COMM_WORLD, rc);
    }
}

int main(int argc, char *argv[])
{
	int tag = 35817;
    int rank, size, rc;
    MPI_Status status;
    
    rc = MPI_Init(&argc, &argv);
    check_for_suc(rc);
    rc = MPI_Comm_size(MPI_COMM_WORLD, &size);
    check_for_suc(rc);
    rc = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    check_for_suc(rc);
    
    srandom(rank);

    if(rank == 0)
	{
		MPI_Status status;
		int t_utc = (random() % 21);
		int num;
        int i = 0;
		while (i != size - 1)
		{
			MPI_Recv(&num, 1, MPI_INT, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, NULL);

			num += random() % 21;
			int d = random() % 4;
			t_utc += d;

			int data[2] = {t_utc, d};
			MPI_Send(&data, 2, MPI_INT, status.MPI_SOURCE, tag, MPI_COMM_WORLD);

			std::cout << "server otpravil rangu " << i << ": t_utc = " << t_utc << "; d = " << d << std::endl;
            i++;
		}
    }	
    else
	{
	int t_0 = (random() % 21);

	MPI_Send(&t_0, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);

	int data[2];
	MPI_Recv(&data, 2, MPI_INT, 0, tag, MPI_COMM_WORLD, NULL);

	int d = data[1];
	int t_utc = data[0];
	int t_1 = t_0 + random() % 6 + 5;
	int t_new = int(ceil(double((t_1 - t_0 - d) / 2.0)));
    t_new += t_utc;

	std::cout << "Klient " << rank << " govorit: t_0 = " << t_0 << "; t_1 = " << t_1 << "; t_utc = " << t_utc << "; d = " << d << "; t_new = " << t_new << ";\n";
    }

    MPI_Finalize();
}
