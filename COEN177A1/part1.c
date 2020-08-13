// Christian Quintero
// COEN 177l Thur. 2:15pm
// Assignment 1
// part1.c
// 4/20/18
//
// This program receives a file as an arguement and executes file 
// whenever the user enters anything other than "exit".

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char command[1024];
	char *input = NULL;

	//infinite loop to demand user keyboard input
	while (1)
	{
		//exits loop if user enters "exit"
		printf("To exit, type: exit ");
		scanf("%s", command);
		if (strcmp(command, "exit" ) == 0)
			return 1;

	
		if (fork() == 0)
		{
			//child code
			execve(command, NULL, 0);
			break;
		}	
		else
		{
			//parent code
			int status;
			waitpid(-1, &status, 0);
		}
	}
	return 0;
}
