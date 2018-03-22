#include "cp.h"
#include "cat.h"
#include "ls.h"

void freeargs(char **argv);

int main (int argc, char *argv[]) {
	char input[1024];

	 do {	// main loop
		int ac = 0;
		char **av;
		av = malloc(4 * sizeof(char*));

		for (int i = 0; i < 4; i++) {
			av[i] = calloc(384, sizeof(char));
		}

		memset(input, 0, 1024 * sizeof(char));
		printf("@: ");
		fgets(input, 1024, stdin);
		input[strcspn(input, "\n")] = 0; // strip newline character from input

		char *temp = strtok(input, " ");
		strcpy(*av, temp);
		while (temp != NULL) {
			temp = strtok(NULL, " ");
			if (temp == NULL)
				break;
			ac++;
			sprintf(*(av + ac), "%s", temp);
		}

		if (strcmp(*av,"cat") == 0) {
			cat(ac, av);
			freeargs(av);
		} else if (strcmp(*av,"ls") == 0) {
			ls(ac, av);
			freeargs(av);
		} else if (strcmp(*av,"cp") == 0) {
			cp(ac, av);
			freeargs(av);
		} else if (strcmp(*av,"grep") == 0) {

		}

	} while (strcmp(input,"exit") != 0);

	exit(0);
}

void freeargs(char **argv) {
	free(argv[0]);
	free(argv[1]);
	free(argv[2]);
	free(argv[4]);
	free(argv);
}
