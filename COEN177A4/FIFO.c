// Christian Quintero
// COEN 177l 
// FIFO.c
//
// This code conducts page requests and replacements using First-In-First-Out algorithm.


#include <stdio.h>
#include <stdlib.h>


int parseArguments(int argc, char*argv[])
{
	int tableSize;
	if(argc == 2 && (tableSize = atoi(argv[1])))
	{
		return tableSize;
	}
	fprintf(stderr, "Wrong arguments. Pass tableSize as an argument\n");
	exit(-1);
	
}

int isInMemory(int pageRequest, int *pageTable, int tableSize)
{
	int i;
	for (i = 0; i < tableSize; i++)
	{
		if(pageRequest == pageTable[i])
		{
			return 1;
		}
	}
	return 0;
}


int main(int argc, char *argv[])
{
        int tableSize = parseArguments(argc, argv);
        int pageRequest, pageTableIndex = 0, numRequests = 0, numMisses = 0;
        int *pageTable = (int *) malloc(sizeof(int)*tableSize);
        char *input = NULL;
        size_t inputAllocated = 0;
        ssize_t bytesRead;
	int i;
	//int numHits = numRequests - numMisses;
	//float hitRate = numHits/numRequests;
        
	while((bytesRead = getline(&input, &inputAllocated, stdin)) != -1)
        {
		pageRequest = atoi(input);
		if (pageRequest == 0)
		{
			continue;
		}
		numRequests++;
		if (!isInMemory(pageRequest, pageTable, tableSize))
		{
			//printf("Page %d caused a page fault\n", pageRequest);
			numMisses++;
			if (pageTableIndex < tableSize)
			{	//still have room in page table
				pageTable[pageTableIndex++] = pageRequest;
			}
			else
			{	// TODO implement a page replacement algorithm
				
				//fprintf(stderr, "Ran out of memory. Implement a page replacement algorithm\n");
				// Algorithm for FIFO
				for (i=0; i<tableSize;i++)
				{
					pageTable[i]=pageTable[i+1];
				}
				pageTable[tableSize-1]=pageRequest;
				//printf("Here is my table:\n");
				//for (i=0;i<tableSize;i++)
				//{
				//	printf("%d  ",pageTable[i]);
				//}
			}
		}//update something in pageTable so that lru and second chance work correctly
        	else
		{
			//printf("%d is already in table, no page faults.\n", pageRequest);
		}
	}
	printf("Hit rate = %f\n", (numRequests - numMisses)/(double)numRequests);
	free(input);
	free(pageTable);
	return 0;
}
