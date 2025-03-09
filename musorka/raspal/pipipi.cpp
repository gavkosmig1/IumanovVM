#include <iostream>
#include <cmath>
#include <mpi.h>
#include <fstream>

void check_for_suc(int rc) {
    if (rc != MPI_SUCCESS) {
        MPI_Abort(MPI_COMM_WORLD, rc);
    }
}

double func(double x) {
    return std::sqrt(4 - x * x);
}

double area(double x, double segment) {
    return (func(x) + func(x + segment)) * (segment / 2.0);
}

int main(int argc, char **argv) {
    int st = MPI_Init(&argc, &argv);
    check_for_suc(st);

    int rank, size;

    int rk = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    check_for_suc(rk);

    int sz = MPI_Comm_size(MPI_COMM_WORLD, &size);
    check_for_suc(sz);

    int N;
    if (rank == 0) {
        std::ifstream in("N.dat");
        in >> N;
        in.close();
    }
    int bc = MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
    check_for_suc(bc);
    double pi = 0.0;
    double current_pos = 0.0;
    double segment = 2.0 / N;
    int part = N / size;
    current_pos = rank * part * segment * 1.0;
    for(int i = 0; i < part; i++){
        pi += area(current_pos, segment);
        current_pos += segment;
    }
    if (rank == size - 1) {
        if (N % size != 0) {
            int t = N - part *size;
            for (int i = 0; i < t-1; i++) {
                pi += area(current_pos, segment);
                current_pos += segment;
            }
        }
    }

    double res;
    int red = MPI_Reduce(&pi, &res, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    check_for_suc(red);
    if (rank == 0) {
        std::cout << "Pi = " << res << std::endl;
    }

    MPI_Finalize();
    return 0;
}
