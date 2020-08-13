#include <stdio.h>
#include <stdlib.h>

void popAtHand(void);

// Struct for nodes
struct Node
{
	int pageNum; //page requested
	int refNum; // ref number for second chance
	struct Node* next;
	struct Node* prev;
};

struct Node* hand; //hand pointer for clock algorithm

struct Node* GetNewNode(int pageRequest)
{
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	
	newNode->pageNum = pageRequest;
	newNode->refNum = 0;
	newNode->next = NULL;
	newNode->prev = NULL;
	return newNode;
}

void InsertAtHand(int pageRequest, int pageTableIndex, int tableSize)
{
	struct Node* myNode = GetNewNode(pageRequest);
	// condition for first node in table
	if (pageTableIndex == 0)
	{
		hand = myNode;
		hand->next = hand;
		hand->prev = hand;
		return;
	}
	
	// add node after hand and move had
	if (pageTableIndex < tableSize)
	{
		myNode->prev = hand;
		myNode->next = hand->next;
		myNode->next->prev = myNode;
		hand->next = myNode;
		hand = myNode->next;
		return;
	}
	while (1)
	{
		if (hand->refNum == 1)
		{
			hand->refNum = 0;
			hand = hand->next;
			
		}
		else
		{
			if (tableSize == 1)
			{
				myNode->next = myNode;
				myNode->prev = myNode;
				popAtHand();
				hand = myNode;
				return;
			}
			else
			{
				myNode->prev = hand->prev;
				myNode->next = hand->next;
				myNode->prev->next = myNode;
				myNode->next->prev = myNode;
				popAtHand();
				hand = myNode->next;
				return;
			}
		}
	}
}

void popAtHand()
{
	struct Node* temp = hand;
	hand = hand->next;
	temp->next = NULL;
	temp->prev = NULL;
	free(temp);
	return;
}

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

struct Node* isInMemory(int pageRequest, int tableSize, int pageTableIndex)
{
	int t = 0;
	struct Node* check = hand;
	//printf("in isinmem before while\n");
	while (t != pageTableIndex)
	{
		if (check->pageNum == pageRequest)
		{
			return check;
		}
		check = check->next;
		t++;
	}
	return NULL;
}


int main(int argc, char *argv[])
{
        int tableSize = parseArguments(argc, argv);
        int pageRequest, pageTableIndex = 0, numRequests = 0, numMisses = 0;
        char *input = NULL;
	size_t inputAllocated = 0;
        ssize_t bytesRead;
	int i;
	

	hand = NULL;
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
	
		struct Node* nodeSelected = isInMemory(pageRequest, tableSize, pageTableIndex);
	
		if (nodeSelected == NULL)
		{
			numMisses++;

			if (pageTableIndex < tableSize)
			{	//still have room in page table
				InsertAtHand(pageRequest, pageTableIndex, tableSize);
				pageTableIndex++;
			}
			else
			{	
				// Algorithm for Clock
				InsertAtHand(pageRequest, pageTableIndex, tableSize);
				
			}
		}//update something in pageTable so that lru and second chance work correctly
        	else
		{
			nodeSelected->refNum = 1;
			hand = hand->next;
		}
	
	}
	printf("Hit rate = %f\n", (numRequests - numMisses)/(double)numRequests);
	free (input);
	struct Node* nodeSelected;
	return 0;
}
