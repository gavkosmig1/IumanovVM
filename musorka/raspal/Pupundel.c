#include <mpi.h>
#include <iostream>

void check_for_suc(int ec)
{
    if (ec != MPI_SUCCESS)
    {
    MPI_Abort(MPI_COMM_WORLD, ec);
    }
}

void sender_msg(int &rank, int &next_rank, int &data)
{
    std::cout << "My name is " << rank << " and I want to say " << data << " to my friend named " << next_rank << std::endl;
        
}

void reciever_msg(int &rank, int &buffer)
{
    std::cout << "My name is " << rank << " and I just heard the number " << buffer << std::endl;
}

int main(int argc, char** argv) {
    check_for_suc(MPI_Init(&argc, &argv));

    int rank = -1, size = -1;

    int rk = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    check_for_suc(rk);
    int sz = MPI_Comm_size(MPI_COMM_WORLD, &size);
    check_for_suc(sz);

    int buffer;
    int next_rank = (rank + 1) % size;
    int secret_code = 9;

    if (rank == 0)
    {
        int message1 = MPI_Send(&secret_code, 1, MPI_INT, next_rank, 0, MPI_COMM_WORLD);
        check_for_suc(message1);
        sender_msg(rank, next_rank, secret_code);

    }
    if (rank != 0)
    {
        int message_got = MPI_Recv(&buffer, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        check_for_suc(b);
        reciever_msg(rank, buffer);
        buffer += rank;

        int c = MPI_Send(&buffer, 1, MPI_INT, next_rank, 0, MPI_COMM_WORLD);
        check_for_suc(c);
        sender_msg(rank, next_rank, buffer);
        }   // По идее у меня на последнем процессе не руинится, а значит условий больше не надо

    if (rank == 0){
        int d = MPI_Recv(&buffer, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        check_for_suc(d);
        std::cout << "My name is agent 0 and I just heard " << buffer << " . Terminating the Earth protocol started";
    }

    MPI_Finalize();
    return 0;
}