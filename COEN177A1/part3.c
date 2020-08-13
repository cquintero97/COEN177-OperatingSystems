// Christian Quintero
// COEN 177l Thur. 2:15pm
// Assignment 1
// part3.c
// 4/20/18
// 
// This program uses recursion to create children until the 6th level is reached, 
// creating a total of 12 children with one parent each level having 2 children
// (except last level of course).

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

void makechild(int level);

int main()
{
	int n = 0;
	printf("Original process:%d\n", getpid());
	makechild(n);
	return 0;
}

//recursive function to create children
void makechild(int level)
{
	int pid;
	if (level == 6)
		return;
	
	//creating first child of level
	if ((pid = fork()) != 0)
	{
		printf("My pid is:%d . My paret pid is:%d\n", pid, getpid());
		waitpid(pid, NULL, 0);
		
		//creating second child of level
		if((pid = fork()) != 0)
		{
			printf("My pid is:%d . My paret pid is:%d\n", pid, getpid());
			//waitpid(pid, NULL, 0);
		}
	}
	else
		makechild(++level);
	return;
}
