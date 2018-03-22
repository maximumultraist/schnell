#include "cp.h"
#include "cat.h"

int main (int argc, char *argv[]) {
	char input[1024];

	 do {	// main loop
		int ac = 0;
		char **av;
		av = malloc(3 * sizeof(char*));

		for (int i = 0; i < 2; i++) {
			av[i] = calloc(384, sizeof(char));
		}

		memset(input, 0, 1024 * sizeof(char));
		printf("@: ");
		fgets(input, 50, stdin);
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
			free(av);
		}

	} while (strcmp(input,"exit") != 0);

	exit(0);
}
