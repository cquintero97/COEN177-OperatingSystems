// Christian Quintero
// COEN 177l
// LRU.c
//
// This code conducts page requests and replacements using Least Recently Used algorithm.

#include <stdio.h>
#include <stdlib.h>

struct Node
{
	int pageNum;
	struct Node* next;
	struct Node* prev;
};

struct Node* head;
struct Node* tail;

struct Node* GetNewNode(int pageRequest)
{
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	
	newNode->pageNum = pageRequest;
	newNode->next = NULL;
	newNode->prev = NULL;
	return newNode;
}

void InsertAtTail(int pageRequest)
{
	struct Node* myNode = GetNewNode(pageRequest);
	if (head == NULL)
	{
		head = myNode;
		tail = myNode;
		return;
	}
	tail->next = myNode;
	myNode->next = NULL;
	myNode->prev = tail;
	tail = myNode;
	return;
}

void PopAtHead(void)
{
	struct Node* temp = head;
	head = head->next;
	head->prev = NULL;
	temp->next = NULL;
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

struct Node* isInMemory(int pageRequest, int tableSize)
{
	struct Node* check = head;
	while (check != NULL)
	{
		if (check->pageNum == pageRequest)
		{
			return check;
		}
		check = check->next;
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
	
	head = NULL;
	tail = NULL;
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
		struct Node* nodeSelected = isInMemory(pageRequest, tableSize);
		if (nodeSelected == NULL)
		{
			numMisses++;
			//printf("before if pagetabe<tablesize\n");
			if (pageTableIndex < tableSize)
			{	//still have room in page table
				InsertAtTail(pageRequest);
				pageTableIndex++;
			}
			else
			{	// TODO implement a page replacement algorithm
				
				// Algorithm for LRU
				PopAtHead();
				InsertAtTail(pageRequest);
			}
		}//update something in pageTable so that lru and second chance work correctly
        	else
		{
			if (nodeSelected == head && nodeSelected != tail)
			{
				head = head->next;
				head->prev = NULL;
				nodeSelected->next = NULL;
				nodeSelected->prev = tail;
				tail->next = nodeSelected;
				tail = nodeSelected;
			}
			else if (nodeSelected != head && nodeSelected != tail)
			{
				nodeSelected->prev->next = nodeSelected->next;
				nodeSelected->next->prev = nodeSelected->prev;
				nodeSelected->prev = tail;
				nodeSelected->next = NULL;
				tail->next = nodeSelected;
				tail = nodeSelected;
			}
		}
		struct Node* nodeP = head;
	}
	printf("Hit rate = %f\n", (numRequests - numMisses)/(double)numRequests);
	free(input);

	struct Node* nodeSelected;
	while(head != NULL)
	{
		nodeSelected = head;
		head = head->next;
		free(nodeSelected);
	}
	return 0;
}
