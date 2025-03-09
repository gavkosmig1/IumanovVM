
#include <cstdlib>
#include <mpi.h>
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

void check_for_suc(int ec)
{
    if (ec != MPI_SUCCESS)
    {
        MPI_Abort(MPI_COMM_WORLD, ec);
    }
}


double f(double x)
{
    double value = std::sqrt(4.0 - x * x);
    return value;
}


int main(int argc, char **argv)
{   // Чтение файла с интернета (докапываться запрещено)
    // std::ifstream inputFile("NateHiggers.dat");
    // if (!inputFile.is_open()) {
    //     std::cerr << "Where the file is??" << std::endl;
    //     return 1;
    // }

    // int N = 0;
    // std::string line;

    // while (getline(inputFile, line)) {
    //     N = std::atoi(line.c_str());
    // }

    // inputFile.close();

    int st = MPI_Init(&argc, &argv);
    check_for_suc(st);

    int size, rank;

    int sz = MPI_Comm_size(MPI_COMM_WORLD, &size);
    check_for_suc(sz);
    int rk = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    check_for_suc(rk);

    int N;
    if (rank == 0)
    {
        std::ifstream in("N.dat");
        in >> N;
        in.close();
    }

    int bc = MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
    check_for_suc(bc);

    double res = 0.0;
    double cur = 0.0;
    double ink = 2.0 / N;
    int part = N / size;
    cur = rank * part * ink * 1.0;

    for (int i = 0; i < part; i++)
    {
        res += (f(cur) + f(cur + ink)) * ink / 2.0;
        cur += ink;
    }

    if (rank == size - 1)
    {
        if (N % size != 0)
        {
            int a = N - part * size;
            for (int i = 0; i < a-1; i++)
            {
                res += (f(cur) + f(cur + ink)) * ink / 2.0;
                cur += ink;
            }
        }
    }

    double itog;
    int rc = MPI_Reduce(&res, &itog, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    check_for_suc(rc);
    if (rank == 0)
    {
        std::cout << "I think the PIE is equal to " << itog << std::endl;
    }

    MPI_Finalize();
    return 0;
}
