#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <sched.h>

int main(int argc, char **argv)
{
	int error = MPI_Init(&argc, &argv);

	int iProc;	
	MPI_Comm_rank(MPI_COMM_WORLD, &iProc);

	int nProcs;
	MPI_Comm_size(MPI_COMM_WORLD, &nProcs);


        int nodeNameLen;
	char nodeName[MPI_MAX_PROCESSOR_NAME];
	MPI_Get_processor_name(nodeName, &nodeNameLen);


	int coreID = sched_getcpu();

       printf("Hello MPI from process %d/%d on core %d of node %s.\n", iProc, nProcs, coreID, nodeName);


	MPI_Finalize();
}

