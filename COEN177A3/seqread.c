// Christian Quintero
// COEN 177l 
// Assignment 3
// 5/18/18
// seqread.c
//
// This program receives a file and saves the size of the file
// as a variable in order to read as many bits in the file as the
// size of the file, but uses a seek function and rand() to read the 
// bits in a random order.

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	int fsize;

	if (argc != 2)
	{
		printf("missing input file\n");
		return 1;
	}	
	
	FILE *fp;
	
	if ((fp = fopen(argv[1],"r"))==NULL)
	{
		printf("Invalid file.\n");
		return errno;
	}
	
	struct stat st;
	stat(argv[1], &st);
	fsize =  st.st_size;
	unsigned long long buffer;
	printf("%d\n", fsize);
	int count=0;
	while (fread(&buffer, 1, 1, fp)==1)
	{
		count++;
	}
	printf("%d\n", count);
	return 0;		
}
