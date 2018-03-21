#include<dirent.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>



int main(int argc, char **argv) {
	struct dirent **fileNames;
	int i;
	if (argc < 1) {
		exit(EXIT_FAILURE);
	}
	else if (argc == 1) {
		i = scandir(".",&fileNames, NULL, alphasort);
	}
	else {
		i = scandir(argv[1], &fileNames, NULL, alphasort);
	}
	if (i < 0) {
		perror("scandir");
		exit(EXIT_FAILURE);
	}
	else {
		while(i--) {
			printf("%s\n", fileNames[i]->d_name);
			free(fileNames[i]);
		}
		free(fileNames);
	}
	exit(EXIT_SUCCESS);
}