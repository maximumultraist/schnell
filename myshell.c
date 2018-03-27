#include "cp.h"
#include "cat.h"
#include "ls.h"
#include "grep.h"

void freeargs(char **argv);

int main (void) {
	char input[1024];

	 do {	// main loop
		int ac = 0;
		char *av[MAX_ARGS];

		for (int i = 0; i < MAX_ARGS; i++) {
			av[i] = calloc(NAME_MAX, sizeof(char));
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
			grep(ac, av);
			freeargs(av);
		}

	} while (strcmp(input,"exit") != 0);

	exit(EXIT_SUCCESS);
}

void freeargs(char **argv) {
	for (int i = 0; i < MAX_ARGS; i++)
		free(argv[i]);
}
