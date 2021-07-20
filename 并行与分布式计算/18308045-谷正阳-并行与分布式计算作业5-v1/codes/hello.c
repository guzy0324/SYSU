#include <stdio.h>
#include <mpi.h>
#define SIZE 1000000
#define TIMES 1000
int arr[SIZE];
int main (int argc, char *argv[])
{
	int rank, num_of_procs;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &num_of_procs);
	MPI_Comm_rank (MPI_COMM_WORLD, &rank);
	MPI_Barrier(MPI_COMM_WORLD);
	double start, end;
	double process;
	for (size_t i = 0; i < TIMES; i++)
	{
		if (rank == 0)
		{
			start = MPI_Wtime();
			MPI_Send(arr, 0, MPI_INT, 1, 0, MPI_COMM_WORLD);
		}
		if (rank == 1)
		{
			MPI_Recv(arr, 0, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
			MPI_Send(arr, 0, MPI_INT, 0, 0, MPI_COMM_WORLD);
		}
		if(rank == 0)
		{
			MPI_Recv(arr, 0, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
			end = MPI_Wtime();
			process += (end - start) / 2;
		}
		MPI_Barrier(MPI_COMM_WORLD);
	}
	if (rank == 0)
	{
		process /= TIMES;
	}
	MPI_Barrier(MPI_COMM_WORLD);
	if (rank == 0)
	{
		start = MPI_Wtime();
		MPI_Send(arr, SIZE, MPI_INT, 1, 0, MPI_COMM_WORLD);
	}
	if (rank == 1)
	{
		MPI_Recv(arr, SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		MPI_Send(arr, SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	if(rank == 0)
	{
		MPI_Recv(arr, SIZE, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
		end = MPI_Wtime();
		printf("Latency: %lf s\n", (end - start) / 2 - process);
		printf("Bandwidth: %lf Bps\n", SIZE * sizeof(int) / ((end - start) / 2 - process));
	}
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize ();
}
