#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
//#include <sched.h>

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

//	int coreID = sched_getcpu();

 //       printf("Hello MPI from process %d/%d on core %d of node %s.\n", iProc, nProcs, coreID, nodeName);


        int MAX_ELEMENTS = 1000000;

        int buffIn[MAX_ELEMENTS];
        int buffOut[MAX_ELEMENTS];

	for(int i = 0; i < MAX_ELEMENTS; i++)
		buffIn[i] = i;

        for(int n = 1; n < MAX_ELEMENTS; n *= 2)
        {
		int nIter;
		if(10000 < 10*MAX_ELEMENTS/n)
			nIter = 10000;
		else
			nIter = 10*MAX_ELEMENTS/n;


		double wtime = MPI_Wtime();
		for(int i = 0; i < nIter; i++)
		{
			MPI_Status status;
			MPI_Sendrecv(buffOut, n, MPI_DOUBLE, (iProc+1)%nProcs, 0, buffIn, n, MPI_DOUBLE, (iProc+nProcs-1)%nProcs, 0, MPI_COMM_WORLD, &status);

		}
		wtime = MPI_Wtime() - wtime;
		if(iProc == 0)
		{
                        printf("%lu bytes\n", n*sizeof(double));
			printf("wtime %f\n", wtime);
		}

        }


	MPI_Finalize();
}

