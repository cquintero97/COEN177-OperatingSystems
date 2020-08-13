// Christian Quintero
// COEN 177l Thur. 2:15pm
// Assignment 1
// part2.c
// 4/20/18
//
// This program creates a chain of 8 child processes using a for loop.

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
	int i, pid;
	
	//for loop to create 8 child processes chain
	for (i = 0; i < 8; i++)
	{
		if ((pid = fork()) != 0)
		{
			waitpid(pid, NULL, 0);
			break;
		}
		else
			printf("My pid is:%d. My parent pid is:%d\n", getpid(), getppid());
	}
}
