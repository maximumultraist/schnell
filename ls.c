#include "ls.h"

int ls(int argc, char **argv) {
	struct dirent **fileNames;
	int i;
	if (argc < 0) {
		exit(EXIT_FAILURE);
	} else if (argc == 0) {
		i = scandir(".",&fileNames, NULL, alphasort);
	} else {
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
	return 0;
}
