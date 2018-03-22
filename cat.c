#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("\nInvalid argument count");
		exit(1);
	}
	int fdold, count;
	char buffer[2048];
	fdold=open(argv[1], O_RDONLY);
	if(fdold == -1) {
		printf("File read error");
		exit(1);
	}	
	while ((count=read(fdold, buffer, sizeof(buffer)))>0) {
		printf("%s", buffer);
	}
	exit(0);
}

