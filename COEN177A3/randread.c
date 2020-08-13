// Christian Quintero
// COEN 177l 
// Assignment 3
// 5/18/18
// randread.c
//
// This program receives a file and saves the size of the file
// as a variable in order to read as many bits in the file as the
// size of the file, but uses a seek function and rand() to read the 
// bits in a random order.

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	unsigned long long fsize;

	if (argc != 2)
	{
		printf("missing input file\n");
		return errno;
	}	
	
	FILE *fp;
	
	if ((fp = fopen(argv[1],"r"))==NULL)
	{
		printf("Invalid file.\n");
		return -1;
	}
	
	struct stat st;
	stat(argv[1], &st);
	// keep track of size of file
	fsize =  st.st_size;
	unsigned long long buffer;
	printf("%d\n", fsize);
	unsigned long long count=0;
	int inc = rand();
	while (count<fsize)
	{
		int inc = rand();
		// if fp goes beyond the end of the file size
		if (fseek(fp, inc, SEEK_CUR) == -1)
		{
			// set fp back to beginning of file
			fseek(fp,0, SEEK_CUR);
			// increment fp by radom size
			fseek(fp, inc, SEEK_CUR);
		}

		fread(&buffer, 1, 1, fp);	
		count++;
	}
	printf("%d\n", count);
	fclose(fp);
	return 0;		
}
