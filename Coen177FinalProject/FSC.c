// Christian Quintero
// COEN 177l
// FSC.c
//
// This code conducts page requests and swaps using second chance algorithm.

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
			return i;
		}
	}
	return -1;
}

void resetRef(int pageTableIndex, int* pageRef)
{
	int i;
	for (i = 0; i < pageTableIndex; i++)
	{
		pageRef[i] = 0;
	}
	return;
}


int main(int argc, char *argv[])
{
        int tableSize = parseArguments(argc, argv);
        int pageRequest, pageTableIndex = 0, numRequests = 0, numMisses = 0;
        int *pageTable = (int *) malloc(sizeof(int)*tableSize);
        int *pageRef = (int*) malloc(sizeof(int)*tableSize);
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
		int pos = isInMemory(pageRequest, pageTable, tableSize);
		if (pos == -1)
		{
			numMisses++;
			if (pageTableIndex < tableSize)
			{	//still have room in page table
				pageTable[pageTableIndex++] = pageRequest;
				resetRef(pageTableIndex, pageRef);
			}
			else
			{	// TODO implement a page replacement algorithm
				
				//fprintf(stderr, "Ran out of memory. Implement a page replacement algorithm\n");
				// Algorithm for Second Chance
				int counter = 0;
				int flag =0;
				for (i=0; i<tableSize;i++)
				{
					
					if (pageRef[i] != 1)
					{
						pageTable[i]=pageTable[i+1];
						pageRef[i] = pageRef[i+1];
						if (flag == 0)
						{
							resetRef(pageTableIndex, pageRef);
							flag = 1;
						}
					}
					else
						counter++;
					
				}
				if (counter == tableSize)
				{
					for (i = 0; i < tableSize; i++)
					{
						pageTable[i] = pageTable[i+1];
					}
					resetRef(pageTableIndex, pageRef);
				}
				
				pageTable[tableSize-1]=pageRequest;
			}
		}//update something in pageTable so that lru and second chance work correctly
        	else
		{
			//printf("%d is already in table, no page faults.\n", pageRequest);
			
			pageRef[pos]=1;
		}
		/*printf("Here is my table:\n");
		for (i=0; i<tableSize; i++)
		{
			printf("%d , %d \n",pageTable[i], pageRef[i]);
		}*/
	}
	printf("Hit rate = %f\n", (numRequests - numMisses)/(double)numRequests);
	free(input);
	free(pageTable);
	return 0;
}
