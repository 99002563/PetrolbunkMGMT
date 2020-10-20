#include <petrolbunk.h>

void write_pipe(int writefd,int value)
{
	if(write(writefd,&value,sizeof(int)) != sizeof(int)) {
		printf("pipe write error");
		exit(0);
	}
}


void read_pipe(int readfd,int *value,int *status)
{
	int n;
	if( (n =  read(readfd,value,sizeof(int))) == -1) {
		printf ("pipe read error");
		exit(0);
	}
	*status = (char)n;
}