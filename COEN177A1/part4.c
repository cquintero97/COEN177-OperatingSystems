// Christian Quintero
// COEN 177l Thur. 2:15pm
// Assignment 1
// part3.c
// 4/20/18
//
// This program uses recursion to create 2 children in each level until the 7th level 
// is reached; At the 7th level it creates 3 children,creating a total of 17 children. 


#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

void makechild(int level);
void make3chldrn();

int main()
{
	int n = 0;
	printf("Original process:%d\n", getpid());
	makechild(n);
	return 0;
}

void makechild(int level)
{
	int pid;

	//At 7th level, calls function to create 3 children
	if (level == 7)
	{
		make3chldrn();
		return;
	}
	
	//creates 1st child of level
	if ((pid = fork()) != 0)
	{
		printf("My pid is:%d . My paret pid is:%d\n", pid, getpid());
		waitpid(pid, NULL, 0);

		//creates 2nd child of level
		if((pid = fork()) != 0)
		{
			printf("My pid is:%d . My paret pid is:%d\n", pid, getpid());
			waitpid(pid, NULL, 0);
		}
	}
	else
		makechild(++level);
	return;
}

//function to create 3 children on 7th level
void make3chldrn()
{
	int pid;
        if ((pid = fork()) != 0)
        {
                printf("My pid is:%d . My paret pid is:%d\n", pid, getpid());
                waitpid(pid, NULL, 0);
                if((pid = fork()) != 0)
                {
                        printf("My pid is:%d . My paret pid is:%d\n", pid, getpid());
                        waitpid(pid, NULL, 0);
                	if ((pid = fork()) != 0)
			{
				printf("My pid is:%d . My paret pid is:%d\n", pid, getpid());
				waitpid(pid, NULL, 0);
			}
		}
        }
	return;
}
